import { FileSystem, Path } from '@effect/platform';
import { BunContext } from '@effect/platform-bun';
import { Array, Data, Effect, flow, Inspectable, Predicate, Option, pipe } from 'effect';
import ts from 'typescript';

export const DIR = './vendor/types/@girs';

class TypescriptError extends Data.TaggedError('TypescriptError')<{
  cause: unknown;
}> {}

const collectModules = (node: ts.Node): Option.Option<readonly string[]> =>
  pipe(
    ts.forEachChild(node, (child) => {
      if (ts.isModuleDeclaration(child)) {
        const module = child.name.text;
        if (module.startsWith('gi://')) {
          return Option.map(collectModules(child), (modules) => [module, ...modules]);
        }
        return Option.none();
      }
      // NOTE: returning only first the first one, which is what we want
      return collectModules(child);
    }),
    v => Option.liftPredicate(v, (asdf) => Predicate.isUndefined(asdf), (asdf) => Option.none()),
    v=>v,
    // Option.fromIterable,
  );

// const extractModules = (file: string) =>
//   Effect.Do.pipe(
//     Effect.bind('path', () => Path.Path),
//     Effect.bind('fs', () => FileSystem.FileSystem),
//     // TODO: catch
//     Effect.bind('contents', ({ fs, path }) => fs.readFileString(path.resolve(DIR, file))),
//     Effect.bind('source', ({ contents }) =>
//       Effect.try({
//         catch: (e) => new TypescriptError({ cause: e }),
//         try: () => ts.createSourceFile(file, contents, ts.ScriptTarget.Latest, true),
//       }),
//     ),
//     Effect.map(({ source }) => ({ file, modules: collectModules(source) })),
//   );
// 
// // Example usage
// Effect.runPromise(
//   Effect.Do.pipe(
//     Effect.bind('fs', () => FileSystem.FileSystem),
//     Effect.bind('files', ({ fs }) => fs.readDirectory(DIR)),
//     Effect.bind('dts', ({ files }) => Effect.succeed(Array.filter(files, (file) => file.endsWith('.d.ts')))),
//     Effect.flatMap(({ dts }) => Effect.all(Array.map(dts, (file) => extractModules(file)))),
//     Effect.tap(flow((obj) => Inspectable.stringifyCircular(obj, 2), Effect.logFatal)),
//     (v) => v,
//     // extractModules('./vendor/types/@girs/astalapps-0.1.d.ts');
//     Effect.provide(BunContext.layer),
//     (v) => v,
//   ),
// );
