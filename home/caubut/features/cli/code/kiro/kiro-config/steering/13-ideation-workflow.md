# Ideation Workflow

The Ideation agent enables open-ended exploration and research before committing to execution. This workflow preserves the human-in-the-loop quality gate while structuring the ideation phase.

## Detection Rules for ALL Agents

When users ask questions that suggest ideation needs, prompt them to switch:

**Trigger phrases:**
- "What are my options?"
- "Help me research..."
- "I don't know what approach to take"
- "What's the best way to..."
- "Should I use X or Y?"
- "I'm not sure how to..."
- Open-ended exploration requests

**Suggested prompt:**
"This seems like an ideation task (research/exploration/options analysis). Consider switching to Ideation agent with `Ctrl+Shift+I` for better results."

**When NOT to suggest:**
- User has clear execution instructions
- Simple, well-defined tasks
- User is already in Ideation agent

## Agent Selection

**Ideation Agent** (`Ctrl+Shift+I`)
- Open-ended exploration and brainstorming
- Research approaches and best practices
- Evaluate trade-offs between options
- Generate structured prompts for execution
- Read-only (no file modifications)

**Planner Agent** (`Shift+Tab`)
- Structured task breakdown
- Requirements gathering with guided questions
- Implementation planning
- Automatic handoff to execution

**Default Agent**
- Direct execution
- File modifications and command execution
- Use when approach is already clear

## When to Use Which Agent

**Ideation** (`Ctrl+Shift+I`):
- "I don't know what approach to take"
- "What are my options?"
- Research and exploration
- Read-only (no file modifications)

**Planner** (`Shift+Tab`):
- "I know what to build, need breakdown"
- Structured task planning
- Requirements gathering

**Default**:
- "Just do this specific thing"
- Clear execution instructions
- Direct file modifications

**If user asks open-ended question → suggest Ideation**

## Workflow Pattern

1. **Ideation** (`Ctrl+Shift+I`) → Explore, research, generate prompt
2. **Review** → Human quality gate (you decide if ready)
3. **Planning** (`Shift+Tab`) → Structured breakdown (if needed)
4. **Execution** → Implement the plan

## Context Handoff Between Agents

When switching agents, preserve:
- Current task objective
- Decisions made so far
- Files modified/created
- Next steps planned

**Handoff format:**
```
Context: [what we're doing]
Progress: [what's complete]
Next: [what needs doing]
Files: [list of relevant files]
```

## Model Selection

Ideation agent defaults to `auto` model for optimal credit usage. When complex reasoning is detected, it will suggest switching to more capable models:

- `claude-sonnet-4` (1.30x) - Hybrid reasoning/coding
- `claude-opus-4.5` (2.20x) - Maximum reasoning capability

Switch manually with `/model <model-name>` when suggested.

## Memory Integration

Ideation agent follows memory lifecycle patterns (09-memory-lifecycle.md):

- Stores successful patterns with appropriate tags
- Detects "config mode" when working in nixos-config
- Surfaces batched suggestions for steering updates
- Prompts to codify reinforced patterns (3+ confirmations)

## Handoff Format

Ideation agent outputs structured prompts:

```
**Context:** What we're trying to achieve
**Approach:** The chosen strategy
**Constraints:** Important limitations
**Success Criteria:** How to know it worked

---
**Ready-to-use prompt:**
[Copy-paste-ready version]
```

## When to Switch FROM Ideation

Ideation agent should suggest switching when:
- Research is complete and approach is clear → Default agent
- Need structured task breakdown → Planner agent (`Shift+Tab`)
- Simple execution needed → Default agent

## When to Use Each Agent

| Scenario | Agent | Why |
|----------|-------|-----|
| "I don't know what I don't know" | Ideation | Open-ended research |
| "Help me think through options" | Ideation | Trade-off analysis |
| "I know what to build" | Planner | Structured breakdown |
| "Just do this specific thing" | Default | Direct execution |
| "Research this pattern" | Ideation | Best practice discovery |
