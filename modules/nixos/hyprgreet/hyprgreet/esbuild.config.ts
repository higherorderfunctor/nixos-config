import * as esbuild from 'esbuild';

await esbuild.build({
  entryPoints: ['src/index.ts'],
  bundle: true,
  format: 'esm',
  treeShaking: true,
  minify: true,
  minifySyntax: true,
  outdir: 'dist/esm',
  external: ['gi://*', 'system'],
  tsconfig: 'tsconfig.json',
  jsx: 'automatic',
  inject: ['./src/platform-gjs/AbortController.ts', './src/platform-gjs/AbortSignal.ts'],
});
