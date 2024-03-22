import type { Console } from "effect"
import { Context, Effect } from "effect"

/** @internal */
export const TypeId: Console.TypeId = Symbol.for("effect/Console") as Console.TypeId

/** @internal */
export const consoleTag: Context.Tag<Console.Console, Console.Console> = Context.GenericTag<Console.Console>(
  "effect/Console"
)

/** @internal */
export const defaultConsole: Console.Console = {
  [TypeId]: TypeId,
  assert(condition, ...args) {
    return Effect.sync(() => {
      console.assert(condition, ...args)
    })
  },
  clear: Effect.sync(() => {
    console.clear()
  }),
  count(label) {
    return Effect.sync(() => {
      console.count(label)
    })
  },
  countReset(label) {
    return Effect.sync(() => {
      console.countReset(label)
    })
  },
  debug(...args) {
    return Effect.sync(() => {
      console.debug(...args)
    })
  },
  dir(item, options) {
    return Effect.sync(() => {
      console.dir(item, options)
    })
  },
  dirxml(...args) {
    return Effect.sync(() => {
      console.dirxml(...args)
    })
  },
  error(...args) {
    return Effect.sync(() => {
      console.error(...args)
    })
  },
  group(options) {
    return options?.collapsed ?
      Effect.sync(() => console.groupCollapsed(options?.label)) :
      Effect.sync(() => console.group(options?.label))
  },
  groupEnd: Effect.sync(() => {
    console.groupEnd()
  }),
  info(...args) {
    return Effect.sync(() => {
      console.info(...args)
    })
  },
  log(...args) {
    return Effect.sync(() => {
      print(...args)
    })
  },
  table(tabularData, properties) {
    return Effect.sync(() => {
      console.table(tabularData, properties)
    })
  },
  time(label) {
    return Effect.sync(() => console.time(label))
  },
  timeEnd(label) {
    return Effect.sync(() => console.timeEnd(label))
  },
  timeLog(label, ...args) {
    return Effect.sync(() => {
      console.timeLog(label, ...args)
    })
  },
  trace(...args) {
    return Effect.sync(() => {
      console.trace(...args)
    })
  },
  warn(...args) {
    return Effect.sync(() => {
      console.warn(...args)
    })
  },
  unsafe: console
}
