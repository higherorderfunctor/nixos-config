import * as esbuild from 'esbuild';
import * as fs from 'node:fs';
import * as path from 'node:path';

/** @type {import('esbuild').Plugin} */
const injectGjsPolyfill = {
  name: 'inject-dirname',
  setup: (build) => {
    build.onResolve({ filter: /^(node:)?buffer$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/buffer.ts'),
    }));
    build.onResolve({ filter: /^(node:)?console$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/console.ts'),
    }));
    build.onResolve({ filter: /^(node:)?worker_threads$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/worker_threads.ts'),
    }));
    build.onResolve({ filter: /^(node:)?timers\/promises$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/timers/promises.ts'),
    }));
    build.onResolve({ filter: /^(node:)?async_hooks$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/async_hooks.ts'),
    }));
    build.onResolve({ filter: /^(node:)?vm$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/vm.ts'),
    }));
    build.onResolve({ filter: /^(node:)?querystring$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/querystring.ts'),
    }));
    build.onResolve({ filter: /^(node:)?tls$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/tls.ts'),
    }));
    build.onResolve({ filter: /^(node:)?zlib$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/zlib.ts'),
    }));
    build.onResolve({ filter: /^(node:)?readline$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/readline.ts'),
    }));
    build.onResolve({ filter: /^(node:)?fs$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/fs.ts'),
    }));
    build.onResolve({ filter: /^(node:)?v8$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/v8.ts'),
    }));
    build.onResolve({ filter: /^(node:)?assert$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/assert.ts'),
    }));
    build.onResolve({ filter: /^(node:)?path$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/path.ts'),
    }));
    build.onResolve({ filter: /^(node:)?dns$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/dns.ts'),
    }));
    build.onResolve({ filter: /^(node:)?process$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/process.ts'),
    }));
    build.onResolve({ filter: /^(node:)?url$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/url.ts'),
    }));
    build.onResolve({ filter: /^(node:)?os$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/os.ts'),
    }));
    build.onResolve({ filter: /^(node:)?util$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/util.ts'),
    }));
    build.onResolve({ filter: /^(node:)?stream$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/stream.ts'),
    }));
    build.onResolve({ filter: /^(node:)?fs\/promises$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/fs/promises.ts'),
    }));
    build.onResolve({ filter: /^(node:)?events$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/events.ts'),
    }));
    build.onResolve({ filter: /^(node:)?perf_hooks$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/perf_hooks.ts'),
    }));
    build.onResolve({ filter: /^(node:)?tty$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/tty.ts'),
    }));
    build.onResolve({ filter: /^(node:)?module$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/module.ts'),
    }));
    build.onResolve({ filter: /^(node:)?crypto$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/crypto.ts'),
    }));
    build.onResolve({ filter: /^(node:)?http$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/http.ts'),
    }));
    build.onResolve({ filter: /^(node:)?https$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/https.ts'),
    }));
    build.onResolve({ filter: /^(node:)?net$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/net.ts'),
    }));
    build.onResolve({ filter: /^(node:)?child_process$/ }, async (args) => ({
      path: path.resolve('./test/polyfills/child_process.ts'),
    }));
    build.onResolve({ filter: /^@effect\/platform-gjs\/.*$/ }, async (args) => ({
      path:
        args.path === '@effect/platform-gjs'
          ? path.resolve('./src/index.ts')
          : path.resolve(args.path.replace('@effect/platform-gjs', './src')),
    }));
    build.onLoad({ filter: /.*\.(js|ts)x?$/ }, async (args) => {
      console.log(args);
      let contents = await fs.promises.readFile(args.path, 'utf8');
      // if (args.path.includes('source-map')) {
      // contents = contents.replace(/\${__dirname}/g, `'${path.dirname(args.path)}'`);
      if (contents.includes('__dirname') && !contents.includes('const __dirname')) {
        contents = `const __dirname = "${args.path}"\n${contents}`;
      }
      // }
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
    'node:*',
    // 'buffer',
    // 'child_process',
    // 'crypto',
    // 'events',
    // 'fs',
    // 'http',
    // 'https',
    // 'module',
    // 'net',
    '@edge-runtime/vm',
    // 'readline',
    // 'async_hooks',
    'jsdom',
    'happy-dom',
    // 'os',
    // 'path',
    '@vitest/ui',
    // 'process',
    '@vitest/browser',
    // 'perf_hooks',
    // 'querystring',
    // 'stream',
    // 'tls',
    // 'tty',
    // 'url',
    // 'util',
    // 'worker_threads',
    // 'zlib',
  ],
  tsconfig: 'tsconfig.test.json',
  sourcemap: true,
  inject: ['test/process.env.shim.ts'],
  resolveExtensions: ['.tsx', '.ts', '.jsx', '.js', '.json'],
  plugins: [injectGjsPolyfill],
});
