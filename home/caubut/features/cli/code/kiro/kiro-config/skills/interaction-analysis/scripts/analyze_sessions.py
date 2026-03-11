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

CORRECTIONS (answer yes):
- User says "no, do X instead" or "that's wrong"
- User asks "why did you do X?" (implying X was wrong)
- User repeats a request (implying first attempt failed)
- User provides additional context AFTER a failed attempt
- User expresses frustration with assistant behavior

NOT CORRECTIONS (answer no):
- User providing initial context or requirements
- User answering assistant's question
- User saying they already did something
- User confirming understanding ("ok", "yes", "got it")
- User exploring options or brainstorming
- User asking clarifying questions before work starts

User message: "{message}"

Answer only: yes or no"""

SUFFICIENCY_PROMPT = """You are analyzing a correction from a user to an AI assistant.

Context so far (most recent last):
{messages}

Question: Do you have enough information to understand:
1. What the assistant did wrong?
2. Why the assistant did it?
3. What the user wants instead?

Answer ONLY with one word: SUFFICIENT or NEED_MORE"""

SUMMARY_PROMPT = """Analyze this correction from a user to an AI assistant.

Conversation context (most recent last):
{messages}

Provide a summary using these exact markers:

ERROR: What did the assistant do wrong?
CAUSE: Why did the assistant do it (what was misunderstood)?
CORRECTION: What did the user say to do instead?
PATTERN: Is this a recurring issue? Related to what?
CONTEXT: Any other relevant details?

Use the markers exactly as shown above."""

# Progress tracking - DRY implementation
class ProgressTracker:
    """Reusable progress tracker for different stages."""
    def __init__(self):
        self.start_time = None
        self.last_update = 0
    
    def show(self, task_name, current, total):
        """Show progress for a specific task."""
        now = time.time()
        # Throttle updates to every 0.5 seconds
        if now - self.last_update < 0.5:
            return
        self.last_update = now
        
        if self.start_time is None:
            self.start_time = now
        
        if total > 0:
            pct = (current / total) * 100
            elapsed = now - self.start_time
            
            # Calculate ETA (skip for first few samples)
            if current > 3:
                rate = current / elapsed
                remaining = (total - current) / rate if rate > 0 else 0
                eta_str = f" | ETA: {int(remaining)}s" if remaining < 60 else f" | ETA: {int(remaining/60)}m"
            else:
                eta_str = ""
            
            sys.stderr.write(f"\r{task_name}: {current}/{total} ({pct:.1f}%){eta_str}    ")
            sys.stderr.flush()
    
    def finish(self, task_name):
        """Mark task as complete and move to new line."""
        sys.stderr.write(f"\r{task_name}: Complete\n")
        sys.stderr.flush()
        self.start_time = None  # Reset for next stage

# Global progress tracker
progress = ProgressTracker()

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

def get_transcript_for_session(session_id):
    """Get full transcript for a specific session."""
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    
    cursor.execute("""
        SELECT value FROM conversations_v2
        WHERE conversation_id = ?
        LIMIT 1
    """, (session_id,))
    
    row = cursor.fetchone()
    conn.close()
    
    if row:
        value = json.loads(row[0])
        return value.get("transcript", [])
    return []

async def check_context_sufficiency(client, messages):
    """Ask Ollama if context is sufficient to understand the correction."""
    try:
        # Format messages for display
        formatted = "\n".join([f"[{i}] {msg[:200]}" for i, msg in enumerate(messages)])
        
        prompt = SUFFICIENCY_PROMPT.format(messages=formatted)
        response = await client.generate(
            model=OLLAMA_MODEL,
            prompt=prompt,
            options={"temperature": 0, "num_ctx": 8192}  # Increased context window for 10-message contexts
        )
        
        return "SUFFICIENT" in response['response'].upper()
        
    except Exception:
        # On error, assume we need more context
        return False

async def gather_adaptive_context(client, session_id, message_index, max_messages=10):
    """Gather context adaptively - add messages until Ollama says sufficient."""
    transcript = get_transcript_for_session(session_id)
    
    if not transcript or message_index >= len(transcript):
        return []
    
    # Start with just the correction message
    context = [transcript[message_index]]
    
    # Iteratively add previous messages
    for i in range(1, max_messages):
        prev_index = message_index - i
        if prev_index < 0:
            break
        
        # Check if current context is sufficient
        is_sufficient = await check_context_sufficiency(client, context)
        if is_sufficient:
            break
        
        # Add previous message to beginning of context
        context.insert(0, transcript[prev_index])
    
    return context

async def generate_summary(client, messages):
    """Generate marker-based summary of the correction."""
    try:
        # Format messages for display
        formatted = "\n".join([f"[{i}] {msg[:500]}" for i, msg in enumerate(messages)])
        
        prompt = SUMMARY_PROMPT.format(messages=formatted)
        response = await client.generate(
            model=OLLAMA_MODEL,
            prompt=prompt,
            options={"temperature": 0, "num_ctx": 8192}  # Increased context window for 10-message contexts
        )
        
        return response['response'].strip()
        
    except Exception as e:
        return f"ERROR: Failed to generate summary\nCAUSE: {str(e)}\nCORRECTION: Unknown\nPATTERN: Unknown\nCONTEXT: Summary generation failed"

async def classify_message(client, message):
    """Ask Ollama if a message is a correction (yes/no) using async."""
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
        
        return "yes" in response['response'].lower()
        
    except Exception:
        return False

async def analyze_session(client, session_id, workspace, transcript, session_num, total_sessions, classification_counter):
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
        
        # Update classification progress
        classification_counter['current'] += len(user_messages)
        progress.show("Classifying messages", classification_counter['current'], classification_counter['total'])
        
        # Collect corrections
        correction_indices = [(i, user_msg) for (i, user_msg), is_correction in zip(user_messages, results) if is_correction]
        
        if not correction_indices:
            return None
        
        # Process each correction: gather context and summarize
        for idx, (i, user_msg) in enumerate(correction_indices, 1):
            # Gather adaptive context
            context = await gather_adaptive_context(client, session_id, i)
            
            # Generate summary
            summary = await generate_summary(client, context)
            
            corrections.append({
                "message_index": i,
                "user_message": user_msg,
                "context_messages": len(context),
                "summary": summary
            })
        
        return {
            "session_id": session_id,
            "workspace": workspace,
            "corrections": corrections
        }
        
    except Exception as e:
        return None

async def main_async(since_timestamp=None):
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
    print(f"Found {len(sessions)} sessions\n", file=sys.stderr)
    
    if not sessions:
        print("No sessions to analyze", file=sys.stderr)
        output = {
            "analyzed_at": datetime.now().isoformat(),
            "cutoff_date": cutoff_date.isoformat(),
            "total_sessions": 0,
            "sessions_with_patterns": 0,
            "results": []
        }
        print(json.dumps(output, indent=2))
        return
    
    # Count total messages for classification
    total_messages = sum(
        sum(1 for msg in transcript if msg.startswith("> ") and len(msg.strip()) >= 3)
        for _, _, transcript in sessions
    )
    
    # Shared counter for classification progress
    classification_counter = {'current': 0, 'total': total_messages}
    
    # Analyze all sessions concurrently with async
    client = AsyncClient(host=OLLAMA_URL)
    tasks = [
        analyze_session(client, sid, ws, transcript, idx+1, len(sessions), classification_counter)
        for idx, (sid, ws, transcript) in enumerate(sessions)
    ]
    
    # Process sessions as they complete
    results = []
    for coro in asyncio.as_completed(tasks):
        result = await coro
        if result and result["corrections"]:
            results.append(result)
    
    # Finish classification progress
    progress.finish("Classifying messages")
    
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
