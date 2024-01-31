import * as esbuild from 'esbuild';
import fs from 'node:fs';
import path from 'node:path';

const injectGjsPolyfill = {
  name: 'inject-dirname',
  setup: (build) => {
    build.onLoad({ filter: /.*/ }, async (args) => {
      const contents = await fs.promises.readFile(args.path, 'utf8');
      let modifiedContents = contents.replace(/__dirname/g, `'${path.dirname(args.path)}'`);
      if (
        modifiedContents.includes('AbortController') &&
        !modifiedContents.includes('import AbortController from "abort-controller/dist/abort-controller.mjs"')
      ) {
        modifiedContents = `import AbortController from "abort-controller/dist/abort-controller.mjs";\n${modifiedContents}`;
      }
      return { contents: modifiedContents, loader: 'ts' };
    });
  },
};

await esbuild.build({
  entryPoints: ['test/test-runner.test.ts'],
  // entryPoints: ['vitest.gjs.ts'],
  bundle: true,
  format: 'esm',
  treeShaking: true,
  // minify: true,
  // minifySyntax: true,
  outfile: 'dist/test/test.gjs.js',
  external: ['gi://*', 'system'],
  tsconfig: 'tsconfig.test.json',
  sourcemap: true,
  plugins: [injectGjsPolyfill],
  define: {
    process: JSON.stringify({
      env: {
        NODE_ENV: 'test',
      },
    }),
  },
});
