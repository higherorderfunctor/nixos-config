# Dungeon Crawler Test Harness — Design Document

## Purpose

Procedural Myst-style dungeon crawler that validates the full kiro-cortex pipeline at scale:
OPA domain scoping → pgvector RAG retrieval → LangGraph block orchestration → HITL interrupt/resume.

The dungeon IS the load test. Room facts are instructions in pgvector. The AI player navigates
rooms, inspects objects, picks up items, solves puzzles — each action is a LangGraph block that
queries OPA-scoped instructions via RAG. A deterministic solver proves solvability and verifies
the AI's playthrough.

This is the first workflow built by meta-workflow, test-driving the workflow builder itself.

## Why a Dungeon Crawler

The dungeon is structurally isomorphic to the real target workflow (repo/code analysis):

| Dungeon Concept | Code Analysis Equivalent |
|-----------------|--------------------------|
| Room | Module/file/component under analysis |
| Entering room (surface facts) | Initial RAG retrieval for a code area |
| Inspecting object (deeper facts) | Drilling into specific APIs, patterns, dependencies |
| Picking up item | Acquiring context (type signature, convention, config value) |
| Item tooltip | Enrichment — doc snippets, usage patterns hinting at application |
| Using item to solve puzzle | Applying retrieved knowledge to make an analysis decision |
| Red herring objects | Irrelevant but plausible RAG results |
| Locked door requiring items | Analysis step requiring specific prior context |
| Non-linear room traversal | Non-linear investigation paths through a codebase |
| Game state (inventory + rooms) | Accumulated context in LangGraph block state |

If the system can play the dungeon, it can do code analysis. And the dungeon is fully verifiable.

## Game Design

### Core Principles

- No combat, no enemies, no time pressure — pure exploration and puzzle solving (Myst-style)
- Every dungeon is procedurally generated from a seed — no stored test data
- All puzzles deterministically solvable and verifiable by a script
- DCC (Dungeon Crawler Carl) narrator provides diagnostic commentary with personality

### Fact Discovery Tiers

| Tier | Trigger | Example | RAG Analog |
|------|---------|---------|------------|
| 1 — Surface | Enter room | Room description, visible objects, doors | Top-level RAG retrieval |
| 2 — Inspect | Examine object | Read book, look behind painting | Targeted follow-up query |
| 3 — Interact | Use item on object | Strike flint → reveals hidden text | Applying context to derive new facts |
| 4 — Emergent | State-dependent | Only visible if candle lit AND book open | Multi-context synthesis |

### Puzzle Types

**Single-room:** combination/sequence, key-and-lock, environmental (light fire to see UV ink),
decoding (cipher + key), object placement.

**Multi-room (backtracking):** distributed clues across 3-4 rooms, cause-and-effect chains
(lever in A → drains water in B → reveals key), item assembly from separate rooms,
progressive revelation (solving A recontextualizes a fact in B).

### Item System

| Category | Behavior | Example |
|----------|----------|---------|
| Key items | Used once, consumed | Iron key, puzzle piece |
| Tools | Reusable across rooms | Flint and steel, magnifying glass |
| Components | Combined with others | Lens + frame = spyglass |
| Clue items | Provide facts on inspect | Journal page, map fragment |
| Red herrings | Pickupable but useless | Decorative gem, old shoe |

**Interactions:** inspect (read tooltip), combine (2 items → new item, max 1 step),
use on (apply to room object), contextual tooltips (description changes based on game state).

**Items that do nothing** are critical for testing — sitting in a chair, pulling decorative rope,
reading irrelevant books. The system must encounter these without wasting excessive cycles.

**Items that help indirectly** — lighting a candle reveals facts, moving a rug shows inscription,
opening a window changes airflow affecting a flame elsewhere.

## Architecture

### Dungeon Generation Pipeline

```
Seed + Config
  → Topology Generator (rooms, connections, locked doors)
  → Puzzle Generator (item→lock dependency DAG, solvable by construction)
  → Fact Generator (per-room facts at multiple tiers)
  → Noise Generator (flavor text, red herrings, lore)
  → Text Renderer (structured facts → plain English via varied templates)
  → Validator/Solver (proves solvability, emits optimal solution path)
```

**Solvability by construction:** Build the solution DAG first, then scatter components.
Keys are always placed in rooms reachable before their lock. Topological ordering of the
DAG IS the solution. Can't accidentally create an unsolvable dungeon.

**Text template variety:** Multiple paraphrase templates per fact type. Tests RAG's ability
to retrieve semantically similar but lexically different instructions.

### LangGraph Blocks

```
NAVIGATE  — move to adjacent room, retrieve tier 1 facts
  → ASSESS
ASSESS    — AI decides next action based on facts + inventory + history
  → INSPECT | PICKUP | COMBINE | USE_ITEM | NAVIGATE
INSPECT   — examine object, retrieve tier 2 facts
  → ASSESS (loop)
PICKUP    — take item, retrieve tooltip
  → ASSESS (loop)
COMBINE   — merge inventory items into new item
  → ASSESS (loop)
USE_ITEM  — apply item to room object, retrieve tier 3 facts, update world state
  → ASSESS (loop)
VERIFY    — terminal: compare AI's solution against deterministic solver
```

The ASSESS → action → ASSESS loop is the core testing loop. Every cycle hits OPA, then RAG,
then decision-making.

### OPA Integration

- Domain: `dungeon`
- Room-scoped fact access: OPA gates which room's facts are visible based on game state
- Tier-based access: tier 1 facts available on entry, tier 2 requires inspect action,
  tier 3 requires use_item action
- Agent role: `dungeon-runner`

### Scaling Strategy

| Tier | Rooms | Total Facts | Purpose |
|------|-------|-------------|---------|
| Smoke | 5 | ~500 | Fast feedback, CI |
| Integration | 15 | ~5,000 | OPA + RAG interaction |
| Load | 50 | ~50,000 | Performance + retrieval precision |
| Stress | 100 | ~100,000+ | Scale limits, noise resilience |

**Noise ratio** is the key scaling knob. At 100K facts with 0.8 noise, only 20K are relevant.
RAG must find the right 20-50 per block iteration out of 100K.

| Fact Type | % of Total | Purpose |
|-----------|------------|---------|
| Puzzle-critical | ~2-5% | Must be retrieved correctly |
| Room flavor | ~15-20% | Context, tests relevance filtering |
| Item tooltips + red herrings | ~10-15% | Tests false lead resistance |
| Cross-room lore + world-building | ~60-70% | Pure noise, tests RAG precision |

### Verification

Deterministic solver does BFS/DFS through the puzzle DAG, outputs optimal action sequence.
Verifier replays AI's actions and produces diagnostic report:

- Solved? Steps taken vs optimal (efficiency ratio)
- Per-query RAG precision/recall
- Critical facts missed (which room, which tier)
- Red herrings chased
- Rooms revisited unnecessarily (memory/state issue)
- Dead-end actions (invalid combinations, impossible interactions)
- Where the chain broke: RAG issue, OPA policy issue, or reasoning failure

### Action Classification

Every AI action is tagged for metrics:

| Classification | Description |
|----------------|-------------|
| Critical | Required to solve the dungeon |
| Enabling | Reveals critical facts (light candle to see) |
| Exploratory | Inspects irrelevant things — acceptable overhead |
| Redundant | Re-inspects already-known things — memory issue |
| Dead-end | Invalid combinations, impossible actions — reasoning issue |

## DCC Narrator (Diagnostic Logging with Personality)

The System narrator provides structured logging disguised as dark humor commentary.
Every action gets narrated with severity level and diagnostic info:

- Normal actions: white narration with diagnostic metadata
- Puzzle progress: green, shows clue count and puzzle ID
- Redundant/stuck: yellow warning, shows revisit count and hints
- Failures: red, shows what was missed and where

**Achievements** are named test assertions:
- "Speedrunner" — solved room first try (perfect retrieval)
- "Laser Focus" — zero red herrings engaged (precision ≥ 0.95)
- "Actually Remembers Things" — cross-room clue used without revisit (memory MCP works)
- "Emotional Support Goldfish" — revisited half the dungeon (memory failure)
- "Try Everything On Everything" — 20+ dead-end actions (reasoning failure)

## Visualization (Phase 6.8, optional)

WebSocket event bus + web UI:
- Dungeon map (graph visualization, current room highlighted, color-coded by state)
- System narrator feed (scrolling, color-coded by severity)
- Live metrics (efficiency, RAG precision/recall, memory recall, dead ends)
- Inventory panel
- Puzzle tracker (progress bars, clue counts)
- Achievement board
- RAG inspector tab (per-query results with relevance tagging)
- Timeline tab (scrubber for action replay)
- Floor summary (Vitest-style pass/fail grid)

Dual-mode: web dashboard for interactive use, rich terminal for CI.

## Performance Insights → RAG Optimization

Dungeon metrics map directly to RAG system insights:

| Dungeon Metric | RAG Insight |
|----------------|-------------|
| Steps/optimal (efficiency) | Overall retrieval + reasoning quality |
| Rooms revisited | Context not retained — memory/state issue |
| Critical facts missed on entry | Tier 1 RAG recall too low |
| Correct item, wrong target | Related but wrong context returned |
| Excessive inspects before solving | RAG window too small |
| Red herrings chased | RAG precision issue — noise ranks too high |
| Tooltip not leveraged after pickup | Enrichment retrieved but not connected |

**Noise tolerance curve:** Run same seed at 1K, 10K, 100K, 1M facts. Plot solve efficiency
vs fact count. The shape tells you where RAG breaks down — directly transferable to
"how many docs can I load before code analysis degrades?"

## Session Resumability

- LangGraph PG checkpointer handles graph state across interrupt/resume
- Thread ID is the session handle — passed back to Claude for resume
- OpenMemory tracks human-readable session context (what we're doing, where we left off)
- Any kiro session can resume a dungeon run by providing the thread_id

## What This Tests

| System Component | How Dungeon Tests It |
|------------------|---------------------|
| OPA domain scoping | Room facts gated by domain + game state |
| pgvector RAG retrieval | 20-50 relevant facts out of 100K per block |
| Cosine distance cutoff | Noise filtering at scale |
| LangGraph blocks | ASSESS→action loops, conditional routing |
| LangGraph checkpointing | Interrupt/resume across sessions |
| Instruction loader | 100K+ YAML facts loaded into pgvector |
| Block executor | OPA→embed→search→inject per block |
| Segment model | Claude orchestrates between deterministic segments |
| OpenMemory | Cross-room clue recall |
| Sequential thinking | ASSESS block reasoning |
