# Ollama Model Management

## Pre-flight Check for OpenMemory

Before using OpenMemory (openmemory_store, openmemory_query, etc.), verify the required Ollama model exists.

**Required Model:**
- Name: nomic-embed-text
- Dimensions: 768
- Size: ~274MB
- Purpose: Embeddings for OpenMemory (replaces synthetic embeddings)

## Daily Check Workflow

**Before first OpenMemory use in a session:**

1. Query memory for today's check status (STATE query - exempt from Ollama check):
   ```
   openmemory_query: "ollama model check 2026-03-08"
   tags: ["global", "ollama-check"]
   ```

2. If check already done today → proceed silently with OpenMemory

3. If check NOT done today:
   - Prompt user: "Checking Ollama model status (daily check)..."
   - Run: `ollama list | grep "^nomic-embed-text"`
   - If missing: `ollama pull nomic-embed-text`
   - Report result to user
   - Store check completion in memory:
     ```
     openmemory_store:
       content: "Ollama model check completed on YYYY-MM-DD. Model status: [up-to-date/pulled/updated]"
       tags: ["global", "ollama-check", "YYYY-MM-DD"]
       type: "factual"
     ```

4. If model was pulled/updated:
   - Prompt user: "Ollama model updated. Please restart Kiro to activate: quit this session and restart kiro-cli"

## When to Check

- Once per day, at first OpenMemory use in any session
- If OpenMemory returns embedding-related errors (override daily limit)
- User explicitly asks about Ollama models

## Troubleshooting

**Model not pulling:**
- Verify Ollama is running: `systemctl --user status ollama`
- Check connectivity: `curl http://localhost:11434/api/version`

**OpenMemory still using synthetic:**
- Restart Kiro after pulling model
- Verify OM_EMBEDDINGS="ollama" in config
