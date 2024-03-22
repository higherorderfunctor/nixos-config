import * as esbuild from "esbuild"

await esbuild.build({
  entryPoints: ["src/main.ts"],
  bundle: true,
  format: "esm",
  outfile: "dist/esm/config.js",
  treeShaking: true,
  external: ["gi://*", "system"],
  tsconfig: "tsconfig.json",
  sourcemap: true,
  resolveExtensions: [".tsx", ".ts", ".jsx", ".js", ".json"]
})
