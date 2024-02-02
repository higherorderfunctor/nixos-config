import { Path } from '@effect/platform-gjs';
import { Effect } from 'effect';

export const resolve = (paths: string[]) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { resolve } = yield* _(Path.Path);
      return resolve(...paths);
    }).pipe(Effect.provide(Path.layer)),
  );

export const join = (paths: string[]) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { join } = yield* _(Path.Path);
      return join(...paths);
    }).pipe(Effect.provide(Path.layer)),
  );

export const normalize = (path: string) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { normalize } = yield* _(Path.Path);
      return normalize(path);
    }).pipe(Effect.provide(Path.layer)),
  );

export const win32 = {};
export const posix = {};
export const extname = {};
export const dirname = {};
export const sep = {};
export const relative = {};
export const isAbsolute = {};
export const basename = {};

export default {
  resolve,
  join,
  normalize,
  win32,
  posix,
};
