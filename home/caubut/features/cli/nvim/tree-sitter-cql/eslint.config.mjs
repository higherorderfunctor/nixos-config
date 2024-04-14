import { FlatCompat } from "@eslint/eslintrc";
import js from "@eslint/js";
import EslintPluginStylistic from "@stylistic/eslint-plugin";
import TypescriptEslintParser from "@typescript-eslint/parser";
import EslintPluginCodegen, {
  processors as EslintPluginCodegenProcessors,
} from "eslint-plugin-codegen";
import EslintPluginDeprecation from "eslint-plugin-deprecation";
import EslintPluginImport from "eslint-plugin-import";
import EslintPluginJsonc from "eslint-plugin-jsonc";
import EslintPluginMarkdown from "eslint-plugin-markdown";
import EslintPluginPreferArrowFunctions from "eslint-plugin-prefer-arrow-functions";
// import EslintPluginTypescript from '@typescript-eslint/eslint-plugin';
import EslintPluginPrettier from "eslint-plugin-prettier";
import EslintPluginPromise from "eslint-plugin-promise";
import EslintPluginSimpleImportSort from "eslint-plugin-simple-import-sort";
import EslintPluginSortDestructureKeys from "eslint-plugin-sort-destructure-keys";
import JsoncEslintParser from "jsonc-eslint-parser";
import path from "path";
import { fileURLToPath } from "url";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const jsFiles = ["**/*.js", "**/*.cjs", "**/*.mjs"];
const tsFiles = ["**/*.ts"];
const jsonFiles = ["**/*.json", "**/*.json5", "**/*.jsonc"];

const ignores = [];
const compat = new FlatCompat({
  baseDirectory: __dirname,
});

const common = {
  ignores,
  files: [...jsFiles, ...tsFiles],
  languageOptions: {
    parser: TypescriptEslintParser,
    parserOptions: {
      project: ["[tj]sconfig.json", "packages/*/[tj]sconfig.json"],
      // ecmaVersion: "latest",
      // sourceType: "module",
      sourceType: "commonjs",
      tsconfigRootDir: __dirname,
    },
    globals: {
      // add declared globals here so eslint doesn't throw errors
    },
  },
  settings: {
    "import/parsers": {
      espree: [".js", ".cjs", ".mjs", ".jsx"],
      "@typescript-eslint/parser": [".ts", ".tsx"],
    },
    "import/resolver": {
      typescript: {
        alwaysTryTypes: true,
        project: ["[tj]sconfig.json", "packages/*/[tj]sconfig.json"],
      },
      node: true,
    },
  },
};

const eslintRecommended = [
  {
    ...js.configs.recommended,
    ...common,
  },
];

const airbnbBase = compat
  .extends("eslint-config-airbnb-base")
  .map((config) => ({
    ...config,
    ...common,
  }));

const airbnbWhitespace = compat
  .extends("eslint-config-airbnb-base/whitespace")
  .map((config) => ({
    ...config,
    ...common,
  }));

const airbnbTypescriptBase = compat
  .extends("eslint-config-airbnb-typescript/base")
  .map((config) => ({
    ...config,
    ...common,
  }));

const typescriptEslintStrictTypeChecked = compat
  .extends("plugin:@typescript-eslint/strict-type-checked")
  .map((config) => ({
    ...config,
    ...common,
    files: tsFiles,
  }));

const typescriptEslintStylisticTypeChecked = compat
  .extends("plugin:@typescript-eslint/stylistic-type-checked")
  .map((config) => ({
    ...config,
    ...common,
  }));

// const eslintPluginTypescript = [
//   ...[
//     ...compat.config(EslintPluginTypescript.configs['strict-type-checked']),
//     ...compat.config(EslintPluginTypescript.configs['stylistic-type-checked']),
//   ].map((config) => ({
//     ...config,
//     plugins: {
//       '@typescript-eslint': EslintPluginTypescript,
//     },
//     ...common,
//   })),
// ];

const eslintPluginPrettier = [
  ...compat.config(EslintPluginPrettier.configs.recommended).map((config) => ({
    ...config,
    plugins: {
      prettier: EslintPluginPrettier,
    },
    ...common,
  })),
];

const eslintPluginPrettierJson = [
  ...compat.config(EslintPluginPrettier.configs.recommended).map((config) => ({
    ...config,
    plugins: {
      prettier: EslintPluginPrettier,
    },
    languageOptions: {
      parser: JsoncEslintParser,
    },
    files: jsonFiles,
    ignores,
  })),
];

const eslintPlugImport = [
  ...[
    ...compat.config(EslintPluginImport.configs.recommended),
    ...compat.config(EslintPluginImport.configs.typescript),
  ].map((config) => ({
    ...config,
    // plugins: {
    //   import: EslintPluginImport,
    // },
    ...common,
  })),
];

const eslintPlugPromise = [
  ...compat.config(EslintPluginPromise.configs.recommended).map((config) => ({
    ...config,
    plugins: {
      promise: EslintPluginPromise,
    },
    ...common,
  })),
];

const eslintPluginJsonc = [
  ...compat
    .config(EslintPluginJsonc.configs["recommended-with-jsonc"])
    .map((config) => ({
      ...config,
      plugins: {
        jsonc: EslintPluginJsonc,
      },
      languageOptions: {
        parser: JsoncEslintParser,
      },
      files: jsonFiles,
      ignores,
    })),
];

const eslintPluginMarkdown = [
  {
    plugins: {
      markdown: EslintPluginMarkdown,
      codegen: EslintPluginCodegen,
    },
    processor: {
      ...EslintPluginCodegenProcessors.processor,
      // hack for eslint --cache to work
      meta: {
        name: "eslint-plugin-codegen-md-processor",
        version: EslintPluginCodegen.version,
      },
    },
    files: ["*.md"],
    ignores,
  },
];

const eslintPuginCodegen = [
  {
    rules: { "codegen/codegen": "error" },
    plugins: {
      codegen: EslintPluginCodegen,
    },
    files: ["*.md", "**/*.md/*", ...tsFiles],
    ignores,
  },
];

const eslintPluginStylistic = [
  {
    // eslint-disable-next-line import/no-named-as-default-member
    ...EslintPluginStylistic.configs["recommended-flat"],
    plugins: {
      "@stylistic": EslintPluginStylistic,
    },
    ...common,
  },
];

const eslintConfig = [
  ...eslintRecommended,
  ...eslintPluginStylistic,
  ...eslintPluginJsonc,
  ...eslintPluginMarkdown,
  ...eslintPuginCodegen,
  ...airbnbBase,
  ...airbnbWhitespace,
  ...airbnbTypescriptBase,
  ...typescriptEslintStrictTypeChecked,
  ...typescriptEslintStylisticTypeChecked,
  // ...eslintPluginTypescript,
  ...eslintPluginPrettier,
  ...eslintPluginPrettierJson,
  ...eslintPlugImport,
  ...eslintPlugPromise,
  {
    ...common,
    plugins: {
      deprecation: EslintPluginDeprecation,
      "prefer-arrow-functions": EslintPluginPreferArrowFunctions,
      "simple-import-sort": EslintPluginSimpleImportSort,
      "sort-destructure-keys": EslintPluginSortDestructureKeys,
    },
    linterOptions: {
      reportUnusedDisableDirectives: true,
    },
    rules: {
      /**
       * Custom deprecation rules
       */
      "deprecation/deprecation": "warn",
      /**
       * Custom general style rules
       */
      // sort destructuring keys
      "sort-destructure-keys/sort-destructure-keys": "error",
      // types
      "@typescript-eslint/ban-types": [
        "error",
        { types: { "{}": false }, extendDefaults: true },
      ],
      "@typescript-eslint/no-empty-interface": "off",
      // naming conventions
      "@typescript-eslint/naming-convention": [
        "error",
        // preferred defaults
        {
          selector: "default",
          leadingUnderscore: "forbid",
          trailingUnderscore: "forbid",
          format: [],
        },
        {
          selector: "variableLike",
          format: ["snake_case", "camelCase", "PascalCase", "UPPER_CASE"],
        },
        {
          selector: "function",
          format: ["snake_case", "camelCase"],
          leadingUnderscore: "allow",
        },
        { selector: "typeLike", format: ["PascalCase"] },
        {
          selector: "property",
          format: ["camelCase"],
        },
        // global exceptions
        {
          selector: "variable",
          modifiers: ["global", "const"],
          format: [],
          filter: {
            regex: "^(__dirname|__filename)$",
            match: true,
          },
        },
        // work around for declared globals
        {
          selector: "variable",
          modifiers: ["const"], // global doesn't work in a `declare global` block
          format: [],
          filter: {
            regex: `^(${Object.keys(common.languageOptions.globals).join("|")})$`,
            match: true,
          },
        },
        // adds PascalCase for nested types
        {
          selector: "typeProperty",
          format: ["camelCase", "PascalCase"],
        },
        // adds UPPER_CASE for static constants
        {
          selector: "classProperty",
          modifiers: ["static", "readonly", "public"],
          format: ["UPPER_CASE"],
        },
        // remove restrictions when working with JSON objects
        {
          selector: "objectLiteralProperty",
          format: [],
        },
        {
          selector: "objectLiteralMethod",
          format: ["snake_case"],
          leadingUnderscore: "allow",
        },
        // useful for error reporting types with one ignored property
        // e.g., type MyErrorType = { _: never }
        {
          selector: "typeProperty",
          format: [],
          filter: { regex: "^_$", match: true },
        },
        // useful for ignored parameters
        {
          selector: "parameter",
          leadingUnderscore: "allow",
          format: ["camelCase"],
        },
        // Effect exception(s) to underscore rules
        {
          selector: ["typeProperty", "memberLike"],
          format: [],
          filter: { regex: "^(_tag)$", match: true },
        },
      ],
      // default is warn, covered by above
      "no-underscore-dangle": "off",
      // default convention is interface, changed to type
      // default is on, conflicts with Effect conventions
      // e.g., const A = ...; type A = MappedType<typeof A>
      "@typescript-eslint/no-redeclare": "off",
      // match effects style conventions
      "@stylistic/yield-star-spacing": ["error", "after"],
      // prettier handles these
      "@stylistic/operator-linebreak": "off",
      "@stylistic/brace-style": "off",
      "@stylistic/indent": "off",
      "@stylistic/indent-binary-ops": "off",
      "@stylistic/semi": "off",
      "@stylistic/quotes": "off",
      // emulate TS with exceptions for names that start with _
      "@typescript-eslint/no-unused-vars": [
        "error",
        {
          args: "all",
          argsIgnorePattern: "^_",
          caughtErrors: "all",
          caughtErrorsIgnorePattern: "^_",
          destructuredArrayIgnorePattern: "^_",
          varsIgnorePattern: "^_",
          ignoreRestSiblings: true,
        },
      ],
      "@typescript-eslint/no-shadow": "off",
      // only require quotes when needed
      "@stylistic/quote-props": ["error", "as-needed"],
      // semis preferred for types
      "@stylistic/member-delimiter-style": [
        "error",
        {
          multiline: {
            delimiter: "semi",
            requireLast: true,
          },
          singleline: {
            delimiter: "semi",
            requireLast: false,
          },
          multilineDetection: "brackets",
        },
      ],
      /**
       * Custom arrow function style enforcement rules
       */
      // default is off
      "arrow-body-style": ["error", "as-needed"],
      // default is off
      "@stylistic/arrow-parens": ["error", "always"],
      // default is off
      "prefer-arrow-callback": "error",
      // default is warn; adds exceptions for generators used by this project
      "func-names": [
        "warn",
        "always",
        {
          generators: "never",
        },
      ],
      // default is off
      "func-style": "error",
      // default is off
      "prefer-arrow-functions/prefer-arrow-functions": [
        "error",
        {
          disallowPrototype: true,
          returnStyle: "implicit",
        },
      ],
      /**
       * Custom comment rules
       */
      // default is off; also adjusted location
      "no-warning-comments": [
        "warn",
        {
          location: "anywhere",
        },
      ],
      /**
       * Custom import/export rules
       */
      // bun hacks
      "import/no-unresolved": ["error", { ignore: ["bun:test"] }],
      // disable as it conflicts with simple-import-sort
      "sort-imports": "off",
      // disable as it conflicts with simple-import-sort
      "import/order": "off",
      // default is warn
      "import/no-duplicates": "error",
      // makes js and ts rules in sync
      "import/extensions": ["error", "ignorePackages", { ts: "js" }],
      // check type imports and add development exceptions
      "import/no-extraneous-dependencies": [
        "error",
        {
          includeTypes: true,
          devDependencies: [
            "esbuild.*.ts",
            "eslint.*.[tj]s",
            "eslint.*.c[tj]s",
            "eslint.*.m[tj]s",
            "jest.*.[tj]s",
            "packages/*/esbuild.*.ts",
            "packages/*/tests/*.[tj]s",
            "packages/*/tests/**/*.[tj]s",
          ],
        },
      ],
      // default is off; set custom sort order
      "simple-import-sort/imports": [
        "error",
        {
          groups: [["^\\u0000"], ["^node:"], ["^@?\\w"], ["^#"], ["^\\."]],
        },
      ],
      // default is off
      "simple-import-sort/exports": ["error"],
      // type imports
      "@typescript-eslint/consistent-type-imports": "error",
      // doesn't mix well with @effect
      "import/prefer-default-export": "off",
      /**
       * Custom promise rules
       */
      "promise/always-return": ["error", { ignoreLastCallback: true }],
    },
  },
];

export default eslintConfig;

// enable to review generated rules
//
// import { inspect } from 'node:util';
// console.log(inspect(eslintConfig, false, null, false));
