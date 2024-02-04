import { Path } from '@effect/platform-gjs';
import { Effect } from 'effect';

export const resolve = (...paths: readonly string[]) =>
  Effect.map(Path.Path, ({ resolve }) => resolve(...paths)).pipe(Effect.provide(Path.layer), Effect.runSync);

export const join = (...paths: readonly string[]) =>
  Effect.map(Path.Path, ({ join }) => join(...paths)).pipe(Effect.provide(Path.layer), Effect.runSync);

export const normalize = (path: string) =>
  Effect.map(Path.Path, ({ normalize }) => normalize(path)).pipe(Effect.provide(Path.layer), Effect.runSync);

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

export default { resolve, join, normalize };
