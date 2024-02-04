import { Path } from '@effect/platform-gjs';
import { Effect } from 'effect';

export const resolve = (paths: string[]) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { resolve } = yield* _(Path.Path);
      return resolve(...paths);
    }).pipe(Effect.provide(Path.layer)),
  );

export const join = (paths: readonly string[]) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { join } = yield* _(Path.Path);
      print(paths.length, '@@');
      print(paths);
      return join(paths);
    }).pipe(Effect.provide(Path.layer)),
  );

export const normalize = (path: string) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { normalize } = yield* _(Path.Path);
      return normalize(path);
    }).pipe(Effect.provide(Path.layer)),
  );

export const win32 = () => {
  throw new Error('Not implemented');
};

export const posix = () => {
  throw new Error('Not implemented');
};

export const extname = () => {
  throw new Error('Not implemented');
};

export const dirname = () => {
  throw new Error('Not implemented');
};

export const sep = () => {
  throw new Error('Not implemented');
};

export const relative = () => {
  throw new Error('Not implemented');
};

export const isAbsolute = () => {
  throw new Error('Not implemented');
};

export const basename = () => {
  throw new Error('Not implemented');
};
