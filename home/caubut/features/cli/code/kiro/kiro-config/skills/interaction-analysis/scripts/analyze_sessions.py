#!/usr/bin/env python3
"""
Interaction Analysis - Parallel Session Analyzer
Analyzes Kiro chat sessions for correction patterns using Ollama.
"""

import argparse
import asyncio
import json
import sqlite3
from datetime import datetime, timedelta
from pathlib import Path
import sys
import time
import os

try:
    from ollama import AsyncClient
except ImportError:
    print("Error: ollama package not found. Run: home-manager switch", file=sys.stderr)
    sys.exit(1)

# Configuration
DB_PATH = Path.home() / ".local/share/kiro-cli/data.sqlite3"
OLLAMA_MODEL = "llama3.2:3b"
OLLAMA_URL = "http://localhost:11434"
CLASSIFICATION_PROMPT = """Is this user message a correction or expression of frustration with the AI assistant?

User message: "{message}"

Answer only: yes or no"""

# Progress tracking
total_prompts_analyzed = 0
total_prompts = 0
start_time = None
last_update = 0

def update_progress():
    """Update progress display - throttled to avoid flooding."""
    global total_prompts_analyzed, total_prompts, start_time, last_update
    
    now = time.time()
    # Only update every 0.5 seconds to avoid flooding
    if now - last_update < 0.5:
        return
    last_update = now
    
    # Calculate progress
    if total_prompts > 0:
        pct = (total_prompts_analyzed / total_prompts) * 100
        elapsed = now - start_time
        
        # Calculate ETA with simple moving average (ignore first 10 samples for warmup)
        if total_prompts_analyzed > 10:
            rate = total_prompts_analyzed / elapsed
            remaining = (total_prompts - total_prompts_analyzed) / rate if rate > 0 else 0
        else:
            remaining = 0
        
        # Format elapsed time
        elapsed_mins = int(elapsed / 60)
        elapsed_secs = int(elapsed % 60)
        elapsed_str = f"{elapsed_mins}m {elapsed_secs}s" if elapsed_mins > 0 else f"{elapsed_secs}s"
        
        # Format ETA
        if remaining < 60:
            eta_str = f"{int(remaining)}s"
        elif remaining < 3600:
            eta_str = f"{int(remaining/60)}m {int(remaining%60)}s"
        else:
            eta_str = f"{int(remaining/3600)}h {int((remaining%3600)/60)}m"
        
        sys.stderr.write(f"\rProgress: {total_prompts_analyzed}/{total_prompts} ({pct:.1f}%) | Elapsed: {elapsed_str} | ETA: {eta_str}")
        sys.stderr.flush()

def init_progress_display():
    """Initialize progress display."""
    global start_time
    start_time = time.time()

def check_ollama_model():
    """Check if Ollama model exists, pull if needed."""
    import subprocess
    result = subprocess.run(
        ["ollama", "list"],
        capture_output=True,
        text=True
    )
    
    if OLLAMA_MODEL not in result.stdout:
        print(f"Pulling {OLLAMA_MODEL}...", file=sys.stderr)
        subprocess.run(["ollama", "pull", OLLAMA_MODEL], check=True)
    else:
        print(f"✓ {OLLAMA_MODEL} available", file=sys.stderr)

def get_sessions_since(cutoff_date):
    """Query SQLite for sessions since cutoff date."""
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    
    cutoff_ms = int(cutoff_date.timestamp() * 1000)
    
    cursor.execute("""
        SELECT conversation_id, key, value
        FROM conversations_v2
        WHERE updated_at > ?
        ORDER BY updated_at DESC
    """, (cutoff_ms,))
    
    sessions = []
    for row in cursor.fetchall():
        conv_id, workspace, value_json = row
        value = json.loads(value_json)
        transcript = value.get("transcript", [])
        sessions.append((conv_id, workspace, transcript))
    
    conn.close()
    return sessions

async def classify_message(client, message):
    """Ask Ollama if a message is a correction (yes/no) using async."""
    global total_prompts_analyzed
    
    try:
        # Skip explicit reflect: markers (handled separately in OpenMemory)
        if message.strip().lower().startswith("reflect:"):
            return False
        
        prompt = CLASSIFICATION_PROMPT.format(message=message[:500])
        response = await client.generate(
            model=OLLAMA_MODEL,
            prompt=prompt,
            options={"temperature": 0}  # Deterministic for classification
        )
        
        result = "yes" in response['response'].lower()
        
        # Update progress after each classification
        total_prompts_analyzed += 1
        update_progress()
        
        return result
        
    except Exception:
        total_prompts_analyzed += 1
        update_progress()
        return False

async def analyze_session(client, session_id, workspace, transcript, session_num, total_sessions):
    """Analyze a single session - find correction messages."""
    try:
        corrections = []
        
        # Extract user messages with indices
        user_messages = [(i, msg[2:]) for i, msg in enumerate(transcript) if msg.startswith("> ") and len(msg.strip()) >= 3]
        
        if not user_messages:
            return None
        
        # Create all classification tasks
        tasks = [classify_message(client, user_msg) for i, user_msg in user_messages]
        
        # Wait for all classifications for this session
        results = await asyncio.gather(*tasks)
        
        # Process results
        for (i, user_msg), is_correction in zip(user_messages, results):
            if is_correction:
                corrections.append({
                    "message_index": i,
                    "user_message": user_msg
                })
        
        if not corrections:
            return None
        
        return {
            "session_id": session_id,
            "workspace": workspace,
            "corrections": corrections
        }
        
    except Exception as e:
        return None

async def main_async(since_timestamp=None):
    global total_prompts
    
    # Check Ollama model
    check_ollama_model()
    
    # Get cutoff date
    if since_timestamp:
        cutoff_date = datetime.fromisoformat(since_timestamp)
        print(f"Analyzing sessions since {cutoff_date.strftime('%Y-%m-%d %H:%M:%S')}", file=sys.stderr)
    else:
        cutoff_date = datetime.now() - timedelta(days=7)
        print(f"Analyzing sessions since {cutoff_date.strftime('%Y-%m-%d')} (7 days ago, first run)", file=sys.stderr)
    
    # Get sessions
    sessions = get_sessions_since(cutoff_date)
    print(f"Found {len(sessions)} sessions", file=sys.stderr)
    
    # Count total prompts
    for _, _, transcript in sessions:
        total_prompts += sum(1 for msg in transcript if msg.startswith("> ") and len(msg.strip()) > 5)
    
    print(f"Total prompts to analyze: {total_prompts}\n", file=sys.stderr)
    
    # Initialize progress display
    init_progress_display()
    
    # Analyze all sessions concurrently with async
    client = AsyncClient(host=OLLAMA_URL)
    tasks = [
        analyze_session(client, sid, ws, transcript, idx+1, len(sessions))
        for idx, (sid, ws, transcript) in enumerate(sessions)
    ]
    
    # Process sessions as they complete
    results = []
    for coro in asyncio.as_completed(tasks):
        result = await coro
        if result and result["corrections"]:
            results.append(result)
    
    # Final newline after progress display
    sys.stderr.write("\n\n")
    
    # Output results (stdout only)
    output = {
        "analyzed_at": datetime.now().isoformat(),
        "cutoff_date": cutoff_date.isoformat(),
        "total_sessions": len(sessions),
        "sessions_with_patterns": len(results),
        "results": results
    }
    
    print(json.dumps(output, indent=2))

def main():
    parser = argparse.ArgumentParser(description="Analyze Kiro sessions for correction patterns")
    parser.add_argument(
        "--since",
        type=str,
        help="ISO 8601 timestamp to analyze sessions since (e.g., 2026-03-09T17:00:00). If not provided, analyzes last 7 days."
    )
    args = parser.parse_args()
    
    asyncio.run(main_async(since_timestamp=args.since))

if __name__ == "__main__":
    main()
