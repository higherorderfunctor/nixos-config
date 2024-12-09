#!/usr/bin/env bun
// WARN: see https://github.com/rollup/plugins/issues/1662
/* eslint-disable @typescript-eslint/naming-convention */
import { Command, HelpDoc, Options as CliOptions } from '@effect/cli';
import { FileSystem, Path } from '@effect/platform';
import { BunContext, BunRuntime } from '@effect/platform-bun';
import { AnsiDoc } from '@effect/printer-ansi';
import _commonjs, { type RollupCommonJSOptions } from '@rollup/plugin-commonjs';
import _json, { type RollupJsonOptions } from '@rollup/plugin-json';
import { nodeResolve } from '@rollup/plugin-node-resolve';
import _terser, { type Options } from '@rollup/plugin-terser';
import _typescript, { type RollupTypescriptOptions } from '@rollup/plugin-typescript';
import type { Types } from 'effect';
import { Array, Cause, Console, Data, Effect, flow, Inspectable, Option, Order, pipe, String, Struct } from 'effect';
import type { OutputOptions, Plugin, RollupOptions, RollupOutput } from 'rollup';
import { defineConfig, rollup } from 'rollup';
import ts from 'typescript';
import _scss, { CSSPluginOptions } from "rollup-plugin-scss";
import _tsconfigPaths, { PluginOptions } from "rollup-plugin-tsconfig-paths"

import packageJson from '../package.json' with { type: 'json' };
/* eslint-enable @typescript-eslint/naming-convention */

const commonjs = _commonjs as unknown as (options?: RollupCommonJSOptions) => Plugin;
const json = _json as unknown as (options?: RollupJsonOptions) => Plugin;
const scss = _scss as unknown as (options?: CSSPluginOptions) => Plugin;
const terser = _terser as unknown as (options?: Options) => Plugin;
const tsconfigPaths = _tsconfigPaths as unknown as (options: PluginOptions) => Plugin;
const typescript = _typescript as unknown as (options: RollupTypescriptOptions) => Plugin;

const ALLOWED_EXTERNAL = [
  'fs', // built-in
] as string[];

/**
 * Generic error for all build errors using a `HelpDoc` for prettier messages.
 */
class BuildError extends Data.TaggedError('BuildError')<{
  error: HelpDoc.HelpDoc;
}> {}

namespace BuildError {
  /**
   * Lift errors with `HelpDoc`.
   */
  export const buildError = (message: string) => new BuildError({ error: HelpDoc.p(message) });

  /**
   * Lift tsserver diagnostics into a `BuildError`.
   */
  export const diagnostic = (diagnostic: ts.Diagnostic | ts.Diagnostic[]) =>
    BuildError.buildError(Inspectable.stringifyCircular(diagnostic, 2));
}

/** Typing helper to strip index signatures from a type. */
type StripIndexSignature<T> = {
  [K in keyof T as string extends K ? never : number extends K ? never : K]: T[K];
};

/**
 * Alias to the tsserver `ParsedCommandLine` type.
 */
type Tsconfig = Types.Simplify<
  { options: Tsconfig.CompilerOptions.WithMetadata } & Omit<ts.ParsedCommandLine, 'options'>
>;

namespace Tsconfig {
  /**
   * Alias to the tsserver `CompilerOptions` type.
   */
  export type CompilerOptions = Types.Simplify<
    {
      jsx: ts.server.protocol.JsxEmit;
      module: ts.server.protocol.ModuleKind;
      moduleResolution: ts.server.protocol.ModuleResolutionKind;
      newLine: ts.server.protocol.NewLineKind;
      target: ts.server.protocol.ScriptTarget;
    } & StripIndexSignature<ts.server.protocol.CompilerOptions>
  >;

  /**
   * Accurate return type for `ts.parseJsonConfigFileContent`.
   */
  export type WithMetadata = { options: Tsconfig.CompilerOptions.WithMetadata } & Tsconfig;

  export namespace CompilerOptions {
    export namespace Metadata {
      /**
       * Union of metadata keys added by tsserver.
       */
      export const KEYS = ['configFilePath'] as const;
      export type KEYS = Readonly<(typeof KEYS)[number]>;

      /**
       * Strips metadata that causes errors with rollup.
       */
      export const stripCompilerOptionsMetadata = (options: Tsconfig.CompilerOptions.WithMetadata) =>
        Struct.omit(...KEYS)(options);
    }

    /**
     * Struct for extra metadata in the compiler options from tsserver.
     */
    export type Metadata = Record<Metadata.KEYS, unknown>;

    /**
     * `CompilerOptions` with metadata added by tsserver.
     */
    export type WithMetadata = Metadata & Tsconfig.CompilerOptions;
  }

  /**
   * Typeguard for `CompilerOptions` from tsserver.
   *
   * @remarks
   *
   * This is not type safe.
   */
  export const is = (tsconfig: ts.ParsedCommandLine | Tsconfig.WithMetadata): tsconfig is Tsconfig.WithMetadata => true;

  /**
   * Hard-cast for `CompilerOptions` from tsserver.
   *
   * @remarks
   *
   * This is not type safe.
   */
  export const tsconfig: (
    tsconfig: ts.ParsedCommandLine | Tsconfig.WithMetadata,
  ) => Effect.Effect<Tsconfig.WithMetadata, BuildError> = Effect.liftPredicate(Tsconfig.is, () =>
    BuildError.buildError('Should never get here'),
  );

  /**
   * Extract the project path for subsequent build calls.
   */
  const getProjectPath: (options: { tsconfig: string }) => Effect.Effect<string, never, Path.Path> = ({ tsconfig }) =>
    Path.Path.pipe(Effect.map((path) => path.dirname(tsconfig)));

  /**
   * Find the tsconfig file from a tsconfig.
   *
   * @privateRemarks
   *
   * This is redundant with the passed in `--tsconfig` but it helps limit the
   * possible files by ones typescript will parse.
   */
  // NOTE: tsserver uses undefined to signal the file cannot be found
  const getConfigPath: (options: {
    projectPath: string;
    tsconfig: string;
  }) => Effect.Effect<string, BuildError, Path.Path> = ({ projectPath, tsconfig }) =>
    Path.Path.pipe(
      Effect.flatMap((path) =>
        Option.fromNullable(ts.findConfigFile(projectPath, ts.sys.fileExists.bind(ts.sys), path.basename(tsconfig))),
      ),
      Effect.mapError(() => BuildError.buildError(`Cannot find file ${tsconfig}`)),
      Effect.flatMap(
        Effect.liftPredicate(
          (foundTsconfig) => tsconfig === foundTsconfig,
          (foundTsconfig) =>
            BuildError.buildError(
              Array.join('\n')([
                'Found tsconfig does not match --tsconfig',
                `  Found: ${foundTsconfig}`,
                `  Expected: ${tsconfig}`,
              ]),
            ),
        ),
      ),
    );

  /**
   * Read a tsconfig file.
   */
  const readConfigFile: (options: { configPath: string }) => Effect.Effect<unknown, BuildError> = ({ configPath }) =>
    Effect.liftPredicate(
      ts.readConfigFile(configPath, ts.sys.readFile.bind(ts.sys)) as
        | { config: unknown; error?: undefined }
        | { config?: undefined; error: ts.Diagnostic | ts.Diagnostic[] },
      (configFile) => configFile.config !== undefined,
      // NOTE: The predicate verifies the error is not undefined.
      // eslint-disable-next-line @typescript-eslint/no-non-null-assertion
      (configFile) => BuildError.diagnostic(configFile.error!),
    ).pipe(Effect.map(Struct.get('config')));

  const parseConfigFile: (options: {
    configFile: unknown;
    configPath: string;
    projectPath: string;
  }) => Effect.Effect<Tsconfig.WithMetadata, BuildError> = ({ configFile, configPath, projectPath }) =>
    Effect.liftPredicate(
      ts.parseJsonConfigFileContent(configFile, ts.sys, projectPath, {}, configPath),
      ({ errors }) => Array.isEmptyArray(errors),
      ({ errors }) => BuildError.diagnostic(errors),
    ).pipe(Effect.flatMap(Tsconfig.tsconfig));

  /**
   * Use tsserver to parse a tsconfig.
   *
   * @remarks
   *
   * Rollup doesn't support all modern typescript features like multiple
   * `extends` or `${configDir}` templates.  Using tsserver to parse the
   * tsconfig builds a single object which works around the issue.
   */
  export const parse: (options: { tsconfig: string }) => Effect.Effect<Tsconfig.WithMetadata, BuildError, Path.Path> = (
    options,
  ) =>
    Effect.Do.pipe(
      Effect.bind('tsconfig', () => Effect.succeed(options.tsconfig)),
      Effect.bind('projectPath', getProjectPath),
      Effect.bind('configPath', getConfigPath),
      Effect.bind('configFile', readConfigFile),
      Effect.bind('parsedTsconfig', parseConfigFile),
      Effect.map(Struct.get('parsedTsconfig')),
    );
}

export namespace RollupConfig {
  /** Allow json files imports. */
  const jsonPlugin = () => json();

  /** Convert commonjs to esm. */
  const commonjsPlugin = () =>
    commonjs({
      // enable source maps
      sourceMap: true,
      // wrap dynamic require calls in a commonjs when in a commonjs dependency
      // cycle hoist all other dynamic require calls to top level imports print
      // which modules have been wrapped
      strictRequires: 'debug',
      // convert "mixed" esm/commonjs modules
      // *cough* @opentelemetry/otlp-exporter-base *cough*
      transformMixedEsModules: true,
    });

  /** Use node resolution for packages in node_modules. */
  const nodeResolvePlugin = () =>
    nodeResolve({
      // don't look for implementations for fs, path, etc
      // defaults to true but setting suppresses the warning
      preferBuiltins: true,
      // TODO:
extensions: [".tsx", ".ts", ".jsx", ".js", ".json"]
    });

  /** Enable scss imports. */
  const scssPlugin = () =>    scss({
    //  TODO:
      output: "./dist/bundle/style.css",
      failOnError: true,
    });

  /** Enable path aliases. */
  const tsconfigPathsPlugin = (tsconfig: string) => tsconfigPaths({
      // path to the tsconfig
tsConfigPath : tsconfig,
  });

  /** Enables transpilation. */
  const typescriptPlugin = (tsconfig: string, options: Tsconfig.CompilerOptions) =>
    typescript({
      // compiler options from tsserver minus metadata
      ...options,
      // .d.ts files normally go in `./dist/dts`, but rollup requires it to be in
      // the output directory
      declarationDir: options.outDir,
      // stop emitting files on first error
      noEmitOnError: true,
      // write to .rollup.cache for incremental transpilation
      outputToFilesystem: true,
      // enable source maps
      sourceMap: true,
      // path to the tsconfig
      tsconfig,
      // typescript version to use for transpilation
      typescript: ts,
    });

  /** Enables advanced minification. */
  const terserPlugin = () =>
    terser({
      // enable es6
      module: true,
      // enable source maps
      sourceMap: true,
      // TODO: verify if source maps are working
      // keep class names for errors in the logger
      // keep_classnames: true,
    });

  /** Generates the output config. */
  const outputConfig = (output: string) =>
    ({
      // output file
      file: output,
      // output esm
      format: 'esm',
      // bundle into a single file
      inlineDynamicImports: true,
      // typescript behavior for default exports
      interop: 'auto',
      // root object
      name: 'ASDAS',
      // enable source map
      sourcemap: true,
    }) as const;

  const BASE_CONFIG = {
    // specifies the global object which is `globalThis` for bun
    context: 'globalThis',
    // mark gjs dependencies as external
    external: [/^gi:\/\//],
    // enables treeshaking
    treeshake: {
      // assume imports are side-effect free
      moduleSideEffects: false,
      // remove as much dead code as possible
      preset: 'smallest',
    },
  } as const;

  const pluginsConfig = (tsconfig: string, options: Tsconfig.CompilerOptions) => [
    tsconfigPathsPlugin(tsconfig),
    typescriptPlugin(tsconfig, options),
    jsonPlugin(),
    commonjsPlugin(),
    nodeResolvePlugin(),
    scssPlugin(),
    terserPlugin(),
  ];

  /**
   * Generate a rollup config with necessary plugins.
   */
  export const rollupConfig: (options: {
    compilerOptions: Tsconfig.CompilerOptions;
    input: string;
    output: string;
    tsconfig: string;
  }) => Effect.Effect<RollupOptions, BuildError> = ({ compilerOptions, input, output, tsconfig }) =>
    Effect.try({
      catch: (error) => BuildError.buildError((error as Error).message),
      try: () =>
        defineConfig({
          ...BASE_CONFIG,
          // entrypoint file
          input,
          // output config
          output: outputConfig(output),
          // adds plugins
          plugins: pluginsConfig(tsconfig, compilerOptions),
        }),
    });
}

/**
 * Generate the rollup bundle.
 */
const bundle: (options: { rollupConfig: RollupOptions }) => Effect.Effect<RollupOutput, BuildError> = ({
  rollupConfig,
}) =>
  Effect.tryPromise({
    // report any errors and fail the build
    catch: (error) => BuildError.buildError((error as Error).message),
    // build then write the bundle
    try: () => rollup(rollupConfig).then((bundle) => bundle.write(rollupConfig.output as OutputOptions)),
  });

/**
 * Guard against `import('module')` and `require('module')` calls that were not
 * inlined.
 */
const detectUnhandledDynamicImports: (options: {
  output: string;
}) => Effect.Effect<void, BuildError, FileSystem.FileSystem> = ({ output }) =>
  FileSystem.FileSystem.pipe(
    // extract all dynamic imports
    Effect.flatMap((fs) =>
      fs.readFileString(output).pipe(
        Effect.mapBoth({
          onFailure: flow(Inspectable.stringifyCircular, BuildError.buildError),
          onSuccess: flow(
            String.matchAll(/(?:import|require)\("([^"]+)"\)/g),
            Array.fromIterable,
            Array.map((match) => match[1]), // capture group access
            Array.sort(Order.string),
            Array.dedupeAdjacent,
            Array.difference(ALLOWED_EXTERNAL),
          ),
        }),
      ),
    ),
    Effect.flatMap(
      Effect.liftPredicate(
        (results) => Array.isEmptyArray(results),
        (results) => BuildError.buildError(`Unresolved dependencies: ${results.join(', ')}`),
      ),
    ),
  );

/**
 * Define the `--tsconfig` option.
 */
const tsconfig = CliOptions.file('tsconfig').pipe(
  CliOptions.mapEffect((tsconfig) => Path.Path.pipe(Effect.map((path) => path.resolve(tsconfig)))),
);

/**
 * Define the `--bundle` option.
 */
const bundleName = CliOptions.text('bundle');

/**
 * App entry point.
 */
const command = Command.make('rollup-build', { tsconfig, bundleName }, ({ tsconfig, bundleName }) =>
  Effect.Do.pipe(
    Effect.bind('path', () => Path.Path),
    Effect.bind('tsconfig', () => Effect.succeed(tsconfig)),
    Effect.bind('parsedTsconfig', Tsconfig.parse),
    Effect.bind('outDir', ({ parsedTsconfig }) => Effect.succeed(parsedTsconfig.options.outDir ?? 'dist/bundle')),
    Effect.bind('input', ({ parsedTsconfig }) =>
      Effect.succeed(`${parsedTsconfig.options.rootDir ?? 'src'}/index.ts`),
    ),
    Effect.bind('output', ({ outDir }) => Effect.succeed(`${outDir}/${bundleName}.js`)),
    Effect.bind('compilerOptions', ({ parsedTsconfig }) => Effect.succeed(parsedTsconfig.options)),
    Effect.bind('rollupConfig', RollupConfig.rollupConfig),
    Effect.tap(bundle),
    Effect.tap(detectUnhandledDynamicImports),
    // render errors
    Effect.catchAllDefect(flow(Cause.die, Cause.pretty, BuildError.buildError, Effect.fail)),
    Effect.tapError((error) =>
      pipe(HelpDoc.toAnsiDoc(error.error), AnsiDoc.render({ style: 'pretty' }), Console.error),
    ),
  ),
);

/**
 * Set app metadata.
 */
const cli = Command.run(command, {
  name: 'Astal Rollup Build Tool',
  version: packageJson.version,
});

/**
 * Run the app.
 */
cli(process.argv).pipe(
  Effect.provide(BunContext.layer),
  BunRuntime.runMain({
    // use our own printer
    disableErrorReporting: true,
  }),
);
