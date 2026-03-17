// Grid-based ASCII diagram renderer. No deps, no auto-layout.
// Usage: bun run scripts/render-diagram.ts
//
// Mode paths (from ARCHITECTURE.md):
//   BUILD:        route → interview ↔ research → decompose ↔ optimize → author → wire → promote → END
//   UPDATE:       route → interview ↔ research → decompose ↔ optimize → author → wire → promote → END
//   REFINE:       route → interview → author → END
//   AUDIT:        route → gap-analyze → optimize → interview → decompose → author → wire → promote → END
//   PROGRAMMATIC: route → decompose ↔ optimize → author → wire → promote → END (FAIL if invalid input)

const BOX_W = 14
const COL_GAP = 6
const ROW_GAP = 2
const BOX_H = 3

interface Node { id: string; label?: string; row: number; col: number }

const nodes: Node[] = [
  { id: "START",       row: 0, col: 1 },
  { id: "route",       row: 1, col: 1 },
  { id: "interview",   row: 2, col: 0 },
  { id: "gap-analyze", row: 2, col: 1 },
  { id: "decompose-p", label: "decompose", row: 2, col: 2 },
  { id: "research",    row: 3, col: 0 },
  { id: "optimize-a",  label: "optimize",  row: 3, col: 1 },
  { id: "optimize-p",  label: "optimize",  row: 3, col: 2 },
  { id: "decompose",   row: 4, col: 0 },
  { id: "interview-a", label: "interview", row: 4, col: 1 },
  { id: "optimize",    row: 5, col: 0 },
  { id: "decompose-a", label: "decompose", row: 5, col: 1 },
  { id: "author",      row: 6, col: 0 },
  { id: "wire",        row: 7, col: 0 },
  { id: "promote",     row: 8, col: 0 },
  { id: "END",         row: 9, col: 0 },
]

const colX = (col: number) => col * (BOX_W + COL_GAP)
const rowY = (row: number) => row * (BOX_H + ROW_GAP)
const midX = (col: number) => colX(col) + Math.floor(BOX_W / 2)
const botY = (row: number) => rowY(row) + 2
const topY = (row: number) => rowY(row)

class Grid {
  buf: string[][] = []
  put(x: number, y: number, ch: string) {
    if (x < 0 || y < 0) return
    while (this.buf.length <= y) this.buf.push([])
    const row = this.buf[y]
    while (row.length <= x) row.push(" ")
    row[x] = ch
  }
  putStr(x: number, y: number, s: string) {
    for (let i = 0; i < s.length; i++) this.put(x + i, y, s[i])
  }
  drawBox(x: number, y: number, label: string) {
    const pad = Math.max(0, Math.floor((BOX_W - label.length) / 2))
    this.putStr(x, y,     "┌" + "─".repeat(BOX_W) + "┐")
    this.putStr(x, y + 1, "│" + " ".repeat(pad) + label + " ".repeat(BOX_W - pad - label.length) + "│")
    this.putStr(x, y + 2, "└" + "─".repeat(BOX_W) + "┘")
  }
  toString(): string {
    return this.buf.map(r => r.join("").trimEnd()).join("\n") + "\n"
  }
}

const g = new Grid()
for (const n of nodes) g.drawBox(colX(n.col), rowY(n.row), n.label ?? n.id)

function nd(id: string) { return nodes.find(n => n.id === id)! }

function vDown(fromId: string, toId: string) {
  const x = midX(nd(fromId).col)
  for (let y = botY(nd(fromId).row) + 1; y < topY(nd(toId).row); y++) g.put(x, y, "│")
  g.put(x, topY(nd(toId).row), "▼")
}

// --- START → route ---
vDown("START", "route")

// --- Route branching ---
const rx = midX(1)
const y1 = botY(1) + 1

// Left: build/update/refine → interview
const ix = midX(0)
for (let x = ix + 1; x < rx; x++) g.put(x, y1, "─")
g.put(ix, y1, "┌")
for (let y = y1 + 1; y < topY(2); y++) g.put(ix, y, "│")
g.put(ix, topY(2), "▼")

// Right: programmatic → decompose-p
const px = midX(2)
for (let x = rx + 1; x < px; x++) g.put(x, y1, "─")
g.put(px, y1, "┐")
for (let y = y1 + 1; y < topY(2); y++) g.put(px, y, "│")
g.put(px, topY(2), "▼")

// Center: audit → gap-analyze (straight down)
for (let y = botY(1) + 1; y < topY(2); y++) g.put(rx, y, "│")
g.put(rx, topY(2), "▼")

// Junction + labels (drawn last to not get overwritten)
g.put(rx, y1, "┼")
g.putStr(ix + 2, y1, "build/update")
g.putStr(rx + 2, y1, "programmatic")
// audit label on the vertical gap
g.putStr(rx - 6, y1 + 1, "audit")
// refine label — annotate on the left branch
g.putStr(ix + 2, y1 + 1, "refine")

// --- Build path ---
vDown("interview", "research")
vDown("research", "decompose")
vDown("decompose", "optimize")
vDown("optimize", "author")
vDown("author", "wire")
vDown("wire", "promote")
vDown("promote", "END")

// --- Audit path ---
vDown("gap-analyze", "optimize-a")
vDown("optimize-a", "interview-a")
vDown("interview-a", "decompose-a")

// --- Programmatic path ---
vDown("decompose-p", "optimize-p")

// --- Convergence: both audit + programmatic merge into author ---
// Single horizontal line at botY(5)+1 spanning from col 2 to col 0
{
  const turnY = botY(5) + 1
  const tx = midX(0)
  const ax = midX(1) // audit
  const px = midX(2) // programmatic
  // horizontal from col 0 to col 2
  for (let x = tx + 1; x < px; x++) g.put(x, turnY, "─")
  g.put(px, turnY, "┘")
  g.put(ax, turnY, "┴") // audit joins from above
  g.put(tx, turnY, "├") // build path continues down
  // programmatic vertical from optimize-p down to turnY
  for (let y = botY(3) + 1; y < turnY; y++) g.put(px, y, "│")
}

process.stdout.write(g.toString())
