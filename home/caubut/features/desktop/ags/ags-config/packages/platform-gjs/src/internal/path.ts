import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import { BadArgument } from '@effect/platform/Error';
import { Path } from '@effect/platform/Path';
import * as Effect from 'effect/Effect';
import * as Layer from 'effect/Layer';

const basename = (path: string) => GLib.path_get_basename(path);

const dirname = (path: string) => GLib.path_get_dirname(path);

const extname = (path: string) => {
  const base = basename(path);
  const index = base.lastIndexOf('.');
  return index > 0 ? base.substring(index) : '';
};

const format = (pathObject: string) => {
    // If the pathObject has a `dir`, use it; otherwise, use `root` for the directory part
    let dir = pathObject.dir || pathObject.root || '';

    // If the pathObject has a `base`, use it; otherwise, combine `name` and `ext`
    let base = pathObject.base || (pathObject.name || '') + (pathObject.ext || '');

    // Ensure we don't double the separators if `dir` already ends with one
    if (dir && !dir.endsWith('/')) {
        dir += '/';
    }

    return join(dir, base);
}

export const fromFileUrl = (url: URL): Effect.Effect<never, BadArgument, string> =>
  Effect.try({
    try: () => Gio.File.new_for_uri(url),
    catch: (error) =>
      BadArgument({
        module: 'Path',
        method: 'fromFileUrl',
        message: `${error}`,
      }),
  });
const isAbsolute = (path: string) => GLib.path_is_absolute(path);

const join = (...paths: readonly string[]) => GLib.build_filenamev([...paths]);

const normalize = (path: string) => Gio.File.new_for_uri(path).get_path();

const root = (path: string) => Gio.File.new_for_uri(path).get_path()?.lastIndexOf(GLib.path_skip_root(path));

export const parse = (path: string) => ({
  root: root(path),
  dir: dirname(path),
  base: basename(path),
  ext: extname(path),
  name: basename(path),
});

const relative = (from: string, to: string) => Gio.File.new_for_uri(from).get_relative_path(Gio.File.new_for_uri(to));

const resolve = (...pathSegments: readonly string[]) =>
   normalize(pathSegments.length === 0 ? GLib.get_current_dir() : join(...pathSegments) )

const toFileUrl = (path: string): Effect.Effect<never, BadArgument, URL> =>
  Effect.try({
    try: () => Gio.File.new_for_path(path).get_uri(),
    catch: (error) =>
      BadArgument({
        module: 'Path',
        method: 'toFileUrl',
        message: `${error}`,
      }),
  });

const toNamespacedPath = (path: string) => path;

/** @internal */
export const layer = Layer.succeed(
  Path,
  Path.of({
    sep: string,
    basename,
    dirname,
    extname,
    format,
    fromFileUrl,
    isAbsolute,
    join,
    normalize,
    parse,
    relative,
    resolve,
    toFileUrl,
    toNamespacedPath,
  }),
);

/** @internal */
export const layerPosix = layer;

/** @internal */
export const layerWin32 = layer;
