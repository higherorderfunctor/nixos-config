# Web Search (Kagi) and Page Fetching

## Kagi

Use the `kagi` MCP for searching the web and summarizing web pages.

### When to Use

- Look up current documentation not covered by Context7
- Find best practices and known issues
- Verify assumptions about third-party tools
- Get up-to-date information beyond training data
- Search for error messages and debugging help

### Cost-Conscious

Kagi API calls cost money.

- Check Context7 first for library questions
- Check memory before searching
- Prefer targeted queries over broad ones
- Store useful results in memory so the same search isn't repeated

### IP Protection

Always generalize queries. See 00-ip-protection.md.

## Fetch

Use the `fetch` MCP to retrieve full web page content as markdown.

### When to Use

- Kagi search found a promising URL — fetch the full page
- Reading a known documentation page in full
- Reading Camara Project wiki pages (<https://wiki.camaraproject.org>)
- Reading changelog or release notes at a known URL

### When NOT to Use Fetch

- When Context7 already has the library docs
- For internal/proprietary URLs (use workspace-specific tools instead)
- Repeatedly for the same page — store the result in memory

## Kagi Summarizer

Kagi provides a built-in summarizer tool that can process URLs directly.
This is often faster than fetching a full page.

- Use Kagi summarize for: getting the key points from a known URL
- Use Fetch instead when: you need the FULL unabridged page content
  (e.g., complete API reference, full changelog, raw configuration examples)

## Search → Read Workflow

1. Kagi search → find relevant URLs
2. For a quick summary → Kagi summarize the URL directly
3. For full content → Fetch the page as markdown
4. Extract the useful information
5. Store the distilled finding in memory
