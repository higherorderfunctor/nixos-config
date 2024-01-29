import * as esbuild from 'esbuild';

await esbuild.build({
  entryPoints: ['test/test-runner.test.ts'],
  bundle: true,
  format: 'esm',
  treeShaking: true,
  minify: true,
  minifySyntax: true,
  outfile: 'dist/test/test.gjs.js',
  external: ['gi://*', 'system'],
  tsconfig: 'tsconfig.test.json',
});
