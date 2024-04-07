import type { Console } from 'effect';
import { Context, Effect } from 'effect';

/** @internal */
export const TypeId: Console.TypeId = Symbol.for('effect/Console') as Console.TypeId;

/** @internal */
export const consoleTag: Context.Tag<Console.Console, Console.Console> =
  Context.GenericTag<Console.Console>('effect/Console');

/** @internal */
export const defaultConsole: Console.Console = {
  [TypeId]: TypeId,
  assert: (condition, ...args) =>
    Effect.sync(() => {
      console.assert(condition, ...args);
    }),
  clear: Effect.sync(() => {
    console.clear();
  }),
  count: (label) =>
    Effect.sync(() => {
      console.count(label);
    }),
  countReset: (label) =>
    Effect.sync(() => {
      console.countReset(label);
    }),
  debug: (...args) =>
    Effect.sync(() => {
      console.debug(...args);
    }),
  dir: (item, options) =>
    Effect.sync(() => {
      console.dir(item, options);
    }),
  dirxml: (...args) =>
    Effect.sync(() => {
      console.dirxml(...args);
    }),
  error: (...args) =>
    Effect.sync(() => {
      console.error(...args);
    }),
  group: (options) =>
    options?.collapsed
      ? Effect.sync(() => {
          console.groupCollapsed(options.label);
        })
      : Effect.sync(() => {
          console.group(options?.label);
        }),
  groupEnd: Effect.sync(() => {
    console.groupEnd();
  }),
  info: (...args) =>
    Effect.sync(() => {
      console.info(...args);
    }),
  log: (...args) =>
    Effect.sync(() => {
      print(...args);
    }),
  table: (tabularData, properties) =>
    Effect.sync(() => {
      console.table(tabularData, properties);
    }),
  time: (label) =>
    Effect.sync(() => {
      console.time(label);
    }),
  timeEnd: (label) =>
    Effect.sync(() => {
      console.timeEnd(label);
    }),
  timeLog: (label, ...args) =>
    Effect.sync(() => {
      console.timeLog(label, ...args);
    }),
  trace: (...args) =>
    Effect.sync(() => {
      console.trace(...args);
    }),
  warn: (...args) =>
    Effect.sync(() => {
      console.warn(...args);
    }),
  unsafe: console,
};
