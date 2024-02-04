import { Path } from '@effect/platform-gjs';
import { Effect } from 'effect';

export class URL {}

export class URLSearchParams {}

export const parse = (path: URL) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { fromFileUrl } = yield* _(Path.Path);
      return fromFileUrl(path);
    }).pipe(Effect.provide(Path.layer)),
  );

export const fileURLToPath = (path: URL) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { fromFileUrl } = yield* _(Path.Path);
      return fromFileUrl(path);
    }).pipe(Effect.provide(Path.layer)),
  );

export const pathToFileURL = (path: string) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { toFileUrl } = yield* _(Path.Path);
      return toFileUrl(path);
    }).pipe(Effect.provide(Path.layer)),
  );

export default {
  parse: (path: URL) =>
    Effect.runSync(
      Effect.gen(function* (_) {
        const { fromFileUrl } = yield* _(Path.Path);
        return fromFileUrl(path);
      }).pipe(Effect.provide(Path.layer)),
    ),
  fileURLToPath: (path: URL) =>
    Effect.runSync(
      Effect.gen(function* (_) {
        const { fromFileUrl } = yield* _(Path.Path);
        return fromFileUrl(path);
      }).pipe(Effect.provide(Path.layer)),
    ),
};
