import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import { FileSystem } from '@effect/platform-gjs';
import { Effect } from 'effect';

export const readFileSync = () => {
  throw new Error('Not implemeneted');
};

export const promises = () => {
  throw new Error('promises: Not implemeneted');
};

export const existsSync = (path: string) => {
  const file = Gio.File.new_for_path(path);
  print('!!', path);
  return file.query_exists(null);
};

export const statSync = () => {
  throw new Error('Not implemeneted');
};

export const realpathSync = () => {
  throw new Error('Not implemeneted');
};

export const createReadStream = () => {
  throw new Error('Not implemeneted');
};

export const createWriteStream = () => {
  throw new Error('Not implemeneted');
};

export const readdirSync = () => {
  throw new Error('Not implemeneted');
};

export const readFile = (path: string) =>
  Effect.runSync(
    Effect.gen(function* (_) {
      const { readFile } = yield* _(FileSystem.FileSystem);
      return readFile(path);
    }).pipe(Effect.provide(FileSystem.layer)),
  );

export const Stats = () => {
  throw new Error('Not implemeneted');
};

export default { require };
