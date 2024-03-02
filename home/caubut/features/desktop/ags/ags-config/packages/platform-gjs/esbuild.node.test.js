import * as esbuild from 'esbuild';

await esbuild.build({
  entryPoints: ['test/unit.ts'],
  platform: 'node',
  bundle: true,
  format: 'esm',
  treeShaking: true,
  minify: true,
  minifySyntax: true,
  outfile: 'dist/test/test.node.js',
  tsconfig: 'tsconfig.unit.json',
  sourcemap: true,
  resolveExtensions: ['.tsx', '.ts', '.jsx', '.js', '.json'],
  define: { 'process.env.NODE_RUNTIME': '"node"' },
});
