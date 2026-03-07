# Research Depth Protocol

## Default Behavior

This protocol classifies requests into tiers to determine HOW MUCH research to do, not WHETHER to use tools.

**Proactive tool usage applies regardless of tier:**
- Query memory at session start for workspace context
- Store findings as you work (don't wait to be asked)
- Use domain doc servers when you detect the framework
- Use git for repository identity and provenance analysis

See 11-tool-usage.md for detailed tool defaults.

**Tier classification determines research depth:**
- Tier 1: Answer immediately, no tools
- Tier 2: Check memory only
- Tier 3: Full research loop (memory + external sources + analysis)

---

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

1. Check domain-specific doc servers FIRST:
   - Effect-TS questions → `effect-docs`
   - NixOS/Home Manager/nix-darwin/Nixvim → `nixos`
   - AWS services, CDK, CloudFormation → `aws-knowledge`
   - Other libraries → `context7`
2. If the domain server has it → often sufficient, skip Kagi
3. If not covered → Kagi search
4. If Kagi finds a promising URL → Fetch or Kagi summarize
5. GitHub for source code, issues, and usage examples

For non-library questions (best practices, architecture, etc.):

- Skip domain servers, go directly to Kagi + GitHub in parallel

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

### Workspace-Extended Research

Some workspaces define additional steering for specialized research
tasks (e.g., repo analysis, migration tracking, domain-specific
investigation protocols).

When performing Tier 3 research, check if workspace steering files
provide additional guidance for the current task type. If they do,
incorporate those rules into the research loop. Personal steering
defines the framework; workspace steering specializes it.
