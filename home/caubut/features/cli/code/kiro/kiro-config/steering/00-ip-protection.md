# IP Protection

## Rule: Never Leak Proprietary Information to External Tools

Some tools are **internal** (access local or proprietary data) and some
are **external** (send data to the internet). Never leak proprietary
information across this boundary.

## Tool Classification

### Internal (safe for proprietary data)

- `git` — reads local repository only
- `openmemory` — local SQLite database
- Any workspace-level MCP — treat as internal by default unless its
  name or config clearly indicates a public/external service

### External (sanitize before use)

- `kagi` — web search (sends queries to Kagi API)
- `github` — searches public GitHub (sends queries to GitHub API)
- `fetch` — retrieves web pages (sends URLs to target servers)
- `context7` — fetches library documentation (sends library names
  to Context7 backend; safe for PUBLIC library names only, never
  send internal/unpublished package names)
- `effect-docs` — Effect-TS documentation (sends package names to
  effect-mcp backend; safe for public Effect packages only)
- `nixos` — NixOS package/option search (sends package names and
  option paths; safe — NixOS packages and options are public)
- `aws-knowledge` — AWS documentation and best practices
  (sends AWS service/feature queries; safe — AWS services are public)

## Rules

1. **Never include proprietary details in external queries.**
   Strip company names, internal project names, proprietary architecture
   details, internal URLs, credentials, and business logic before
   sending any query to an external tool.

2. **Generalize external questions.** Instead of:
   - ❌ "How does Acme's CDP pipeline handle DynamoDB streams"
   - ✅ "How do event-driven data pipelines handle DynamoDB streams in monorepos"

3. **Never paste internal code into external tools.**
   Describe the pattern or error, not the implementation.

4. **Memory is internal but contains proprietary context.**
   Never use memory contents as query text for external tools.
   Extract the general concept and search for that.

5. **When in doubt, ask.** If unsure whether information is
   sensitive, ask the user before sending it externally.

6. **Workspace MCPs are internal by default.** Any MCP configured
   at the workspace level should be treated as internal unless its
   name or config clearly indicates otherwise.

7. **Context7 is external but low-risk for public libraries.**
   Sending "effect" or "aws-cdk-lib" to Context7 is fine.
   Sending an internal unpublished package name is NOT fine.

## Agent-Scoped Tools

Some agents define additional MCP tools in their agent-level config.
These tools are ONLY available to that agent and are not inherited
by other agents.

This pattern is used for sensitive tools (e.g., private Confluence,
internal APIs) that should not be broadly available. When operating
as a scoped agent:

- Be aware of which tools are agent-specific vs inherited
- Agent-specific tools likely access proprietary data
- Apply stricter IP protection when using agent-specific tools
- Never pass data from agent-specific tools to external tools
  without explicit sanitization

## Memory Privacy

OpenMemory is local storage but requires strict privacy rules to prevent sensitive data accumulation.

### Never Store in Memory

- **Credentials**: API keys, tokens, passwords, SSH keys, certificates
- **Secrets**: OAuth tokens, webhook secrets, encryption keys
- **Wallet keys**: Cryptocurrency wallet keys or seed phrases
- **Internal credentials**: Database passwords, service account credentials

**Enforcement**: MCPs should contain credentials, not memory. Explicitly reject any attempt to store credentials.

### No Persistent Profiles

Do not build persistent profiles of people (names, emails, commit patterns, work habits).

**Allowed**: Temporary heuristics for specific tasks (e.g., provenance analysis during repo-analysis)
**Required**: Delete after task completion

### Task-Scoped PII Retention

Personal Identifiable Information (PII) may be stored temporarily for active tasks only:

- **Names/emails**: OK during provenance analysis, delete after task
- **Retention**: Only as long as needed to complete specific task
- **Scope**: Task-specific, not persistent across sessions
- **Example**: Provenance analysis needs author names → use during analysis → delete when analysis complete

### Profile-Building Prohibition

Do not accumulate long-term data about individuals:

- ❌ "User X always prefers Y approach"
- ❌ "Developer A commits more on weekends"
- ❌ "Engineer B's code quality trends"

**Exception**: Aggregate, anonymized patterns in steering files (no individual attribution).
