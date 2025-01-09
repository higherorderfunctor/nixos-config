import * as path from 'path';
import { Extractor, ExtractorConfig, IConfigFile } from '@microsoft/api-extractor';

function createConfig(entryPoint: string, outputFile: string): IConfigFile {
  return {
    $schema: "https://developer.microsoft.com/json-schemas/api-extractor/v7/api-extractor.json",
    projectFolder: process.cwd(),
    mainEntryPointFilePath: path.join(process.cwd(), entryPoint),
    bundledPackages: [],
    compiler: {
      tsconfigFilePath: path.join(process.cwd(), "tsconfig.json")
    },
    dtsRollup: {
      enabled: true,
      untrimmedFilePath: path.join(process.cwd(), outputFile)
    },
    apiReport: { enabled: false },
    docModel: { enabled: false },
    tsdocMetadata: { enabled: false },
    messages: {
      extractorMessageReporting: {
        "ae-forgotten-export": { logLevel: "none" },
        "ae-missing-release-tag": { logLevel: "none" },
        "ae-unresolved-link": { logLevel: "none" },
        "ae-internal-missing-underscore": { logLevel: "none" }
      }
    },
  };
}

async function extractApi(entryPoint: string, outputFile: string): Promise<boolean> {
  const config = createConfig(entryPoint, outputFile);

  const extractorConfig = ExtractorConfig.prepare({
    configObject: config,
    configObjectFullPath: process.cwd(),
    packageJsonFullPath: path.join(process.cwd(), "package.json")
  });

  console.log(extractorConfig);

  const extractorResult = Extractor.invoke(extractorConfig, {
    localBuild: true,
    showVerboseMessages: true
  });

  if (!extractorResult.succeeded) {
    console.error(
      `API Extractor for ${entryPoint} completed with ${extractorResult.errorCount} errors` +
      ` and ${extractorResult.warningCount} warnings`
    );
  }

  return extractorResult.succeeded;
}

// Run all bundles
const bundles = [
  { entry: "dist/dts/index.d.ts", output: "dist/index.d.ts" },
  // { entry: "dist/dts/gtk3/index.d.ts", output: "dist/gtk3.d.ts" },
  // { entry: "dist/dts/gtk4/index.d.ts", output: "dist/gtk4.d.ts" }
];

async function main() {
  const results = await Promise.all(
    bundles.map(bundle => extractApi(bundle.entry, bundle.output))
  );

  if (results.every(result => result)) {
    console.log("All API Extractions completed successfully");
    process.exitCode = 0;
  } else {
    console.error("Some API Extractions failed");
    process.exitCode = 1;
  }
}

main().catch(error => {
  console.error(error);
  process.exitCode = 1;
});
