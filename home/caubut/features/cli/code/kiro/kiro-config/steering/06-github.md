# GitHub

Use the `github` MCP to search and read **public repositories only**.

## When to Use

- Find how other projects use a specific library or API
- Read source code of dependencies to understand behavior
- Search issues for known bugs, workarounds, and discussions
- Read documentation files (README, CONTRIBUTING, CHANGELOG)
- Find example implementations of patterns
- Read test files for canonical usage patterns

## Effective Search Patterns

- `"from effect import" language:typescript` — usage examples
- `repo:owner/name path:src` — read specific source files
- Search issues with `is:issue label:bug` for known problems
- Look at test files — they often show the intended API usage

## Version Awareness

When searching GitHub for library usage:

- Check the repo's dependency files for version info
- Be aware that code examples may target older API versions
- Cross-reference with the library's CHANGELOG or releases
- Include version numbers in memory tags for dependency-specific facts

## IP Protection

Never search GitHub using proprietary code snippets or internal
identifiers. Generalize to the pattern or error message.
See 00-ip-protection.md.
