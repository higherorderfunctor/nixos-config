import * as esbuild from 'esbuild';
// const injectGjsPolyfill = {
//   name: 'inject-dirname',
//   setup: (build) => {
//     build.onLoad({ filter: /.*\.(js|ts)x?$/ }, async (args) => {
//       console.log(args);
//       const contents = await fs.promises.readFile(args.path, 'utf8');
//       let modifiedContents = contents; // .replace(/__dirname/g, `'${path.dirname(args.path)}'`);
//       if (
//         modifiedContents.includes('AbortController') &&
//         !modifiedContents.includes('import AbortController from "abort-controller/dist/abort-controller.mjs"')
//       ) {
//         modifiedContents = `import AbortController from "abort-controller/dist/abort-controller.mjs";\n${modifiedContents}`;
//       }
//       return { contents: modifiedContents, loader: 'ts' };
//     });
//   },
// };

await esbuild.build({
  entryPoints: ['vitest.config.ts'],
  bundle: true,
  format: 'esm',
  treeShaking: true,
  minify: true,
  minifySyntax: true,
  outfile: 'dist/test/test.gjs.js',
  external: [
    'gi://*',
    'system',
    'console',
    //
    'lightningcss',
    //
    '@effect/*',
    'node:*',
    'buffer',
    'child_process',
    'crypto',
    'events',
    'fs',
    'http',
    'https',
    'module',
    'net',
    '@edge-runtime/vm',
    'readline',
    'async_hooks',
    'jsdom',
    'happy-dom',
    'os',
    'path',
    '@vitest/ui',
    'process',
    '@vitest/browser',
    'perf_hooks',
    'querystring',
    'stream',
    'tls',
    'tty',
    'url',
    'util',
    'worker_threads',
    'zlib',
  ],
  tsconfig: 'tsconfig.test.json',
  sourcemap: true,
  inject: ['test/process.env.shim.ts'],
  resolveExtensions: ['.tsx', '.ts', '.jsx', '.js', '.json'],
  // plugins: [injectGjsPolyfill],
});
