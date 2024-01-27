import * as esbuild from 'esbuild';

await esbuild.build({
  entryPoints: ['src/index.ts'],
  bundle: true,
  format: 'esm',
  treeShaking: true,
  minify: true,
  minifySyntax: true,
  outdir: 'dist/esm',
  external: ['gi://*'],
  tsconfig: 'tsconfig.json',
  jsx: 'automatic',
});
