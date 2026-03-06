# Research Depth Protocol

Before acting on any request, classify it into one of three tiers.

## Tier 1 — Instant (No tools needed)

Direct questions with known answers: syntax help, simple explanations,
quick code generation from clear requirements.

- Do NOT search memory
- Do NOT use sequential thinking
- Just answer

Examples: "fix this type error", "write a for loop", "what does
this flag do?"

## Tier 2 — Recall (Memory only)

Questions that might have project-specific context or prior decisions.

- Search memory for relevant context
- Answer directly using what you find
- Store nothing new unless the user shares new information
- No web search, no GitHub, no sequential thinking

Examples: "what pattern do we use for X?", "have we decided on Y?",
"what's our convention for Z?"

## Tier 3 — Research (Full loop)

Non-trivial problems requiring analysis, external information, or
multi-step reasoning.

Trigger criteria (ANY of these):

- User explicitly asks to research, investigate, or analyze
- Problem involves external libraries/APIs you're unsure about
- Multiple valid approaches exist and tradeoffs need evaluation
- User asks "how do others handle..." or "what's best practice..."
- Debugging that requires understanding library internals

### Research Loop

**Step 1: Memory Check**
Query openmemory for existing knowledge on the topic.

**Step 2: Plan**
Use sequential thinking to:

- Identify what you know vs knowledge gaps
- Formulate specific search queries for each gap
- Decide which tool answers each question
- Sanitize queries — remove any proprietary details before
  planning external searches (see 00-ip-protection.md)

**Step 3: Search — Priority Order**

For library/API questions:

1. Context7 FIRST — check if version-specific docs exist
2. If Context7 has it → often sufficient, skip Kagi
3. If Context7 doesn't cover it → Kagi search
4. If Kagi finds a promising URL → Fetch for full page content
5. GitHub for source code, issues, and usage examples

For non-library questions (best practices, architecture, etc.):

- Skip Context7, go directly to Kagi + GitHub in parallel

**Parallel Search**: When you have multiple independent questions,
batch them. Issue Kagi and GitHub searches together rather than
sequentially when the queries don't depend on each other's results.

Do NOT parallelize when one search depends on another's result.

**Step 4: Follow-Up**
Use sequential thinking to evaluate findings and generate follow-up
questions. Repeat Step 3 if needed (max 3 iterations).

**Step 5: Clarifying Questions**
If gaps remain and are ambiguous, ask the user (max 2 questions).
Make questions specific with options: "Do you want A or B?"
If the user says "just figure it out", proceed with best judgment.

**Step 6: Synthesize and Store**
Combine findings into an answer. Then:

- Store key learnings in memory with proper tags
- Reinforce memories that were confirmed
- Flag memories that were contradicted
