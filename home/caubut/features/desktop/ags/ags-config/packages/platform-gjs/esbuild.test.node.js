import * as esbuild from 'esbuild';
import * as fs from 'node:fs';
import * as path from 'node:path';

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
