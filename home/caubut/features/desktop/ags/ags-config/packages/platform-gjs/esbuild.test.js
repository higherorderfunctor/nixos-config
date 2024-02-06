import * as esbuild from 'esbuild';
import * as fs from 'node:fs';
import * as path from 'node:path';

const polyfills = [
  'assert',
  'async_hooks',
  'buffer',
  'child_process',
  'console',
  'crypto',
  'dns',
  'events',
  'fs',
  'fs/promises',
  'http',
  'https',
  'module',
  'net',
  'os',
  'path',
  'perf_hooks',
  'process',
  'querystring',
  'readline',
  'stream',
  'timers/promises',
  'tls',
  'tty',
  'url',
  'util',
  'v8',
  'vm',
  'worker_threads',
  'zlib',
];

/** @type {import('esbuild').Plugin} */
const injectGjsPolyfill = {
  name: 'inject-dirname',
  setup: (build) => {
    // polyfills.forEach((polyfill) => {
    //   build.onResolve({ filter: new RegExp(`^(node:)?${polyfill}$`) }, async () => ({
    //     path: path.resolve(`./test/polyfills/${polyfill}.ts`),
    //   }));
    // });
    // build.onResolve({ filter: /^@effect\/platform-gjs\/.*$/ }, async (args) => ({
    //   path:
    //     args.path === '@effect/platform-gjs'
    //       ? path.resolve('./src/index.ts')
    //       : path.resolve(args.path.replace('@effect/platform-gjs', './src')),
    // }));
    build.onLoad({ filter: /.*\.(js|ts)x?$/ }, async (args) => {
      let contents = await fs.promises.readFile(args.path, 'utf8');
      if (contents.includes('__dirname') && !contents.includes('const __dirname')) {
        contents = `const __dirname = "${path.dirname(args.path)}"\n${contents}`;
      }
      if (
        contents.includes('AbortController') &&
        !contents.includes('import AbortController from "abort-controller/dist/abort-controller.mjs"')
      ) {
        contents = `import AbortController from "abort-controller/dist/abort-controller.mjs";\n${contents}`;
      }
      return { contents, loader: 'ts' };
    });
  },
};

await esbuild.build({
  entryPoints: ['unit.config.ts'],
  bundle: true,
  format: 'esm',
  treeShaking: true,
  minify: true,
  minifySyntax: true,
  outfile: 'dist/test/test.gjs.js',
  external: ['gi://*', 'system'],
  tsconfig: 'tsconfig.test.json',
  sourcemap: true,
  inject: ['test/process.env.shim.ts'],
  resolveExtensions: ['.tsx', '.ts', '.jsx', '.js', '.json'],
  plugins: [injectGjsPolyfill],
});
