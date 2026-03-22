# Context7

Context7 fetches up-to-date, version-specific library documentation
and code examples directly from source.

## When to Use

- Default tool for library/API questions not covered by a
  domain-specific server (see below)
- Looking up current API signatures, function parameters, return types
- Finding version-specific usage examples
- Checking if a library feature exists in a specific version
- Understanding breaking changes between versions

## When to Use a Domain-Specific Server Instead

Some libraries and platforms have dedicated MCP servers with deeper
coverage than Context7. Check these first:

- **Effect-TS** → use `effect-docs` (covers core + ecosystem packages)
- **NixOS/Home Manager** → use `nixos` (130K+ packages, 23K+ options)
- **AWS services/CDK** → use `aws-knowledge` (docs + best practices)

Use Context7 for libraries NOT covered by a domain-specific server.

## When NOT to Use

- Non-library questions (architecture, best practices, general concepts)
- Internal/unpublished package documentation (IP risk — see 00-ip-protection.md)
- Questions about project-specific configuration or conventions (use memory)

## Cost Advantage

Context7 is free and fast. Always check Context7 before falling back
to Kagi for library questions. This saves Kagi API costs and often
provides more accurate, version-specific answers.

## IP Protection

Context7 sends library names to its backend. This is safe for PUBLIC
libraries (e.g., "effect", "aws-cdk-lib", "vue", "express"). Never
send internal or unpublished package names to Context7.
