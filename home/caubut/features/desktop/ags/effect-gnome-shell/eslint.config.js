import { FlatCompat } from '@eslint/eslintrc';
import js from '@eslint/js';
import EslintPluginStylistic from '@stylistic/eslint-plugin';
import TypescriptEslintParser from '@typescript-eslint/parser';
import EslintPluginCodegen, { processors as EslintPluginCodegenProcessors } from 'eslint-plugin-codegen';
import EslintPluginDeprecation from 'eslint-plugin-deprecation';
import EslintPluginImport from 'eslint-plugin-import';
import EslintPluginJsonc from 'eslint-plugin-jsonc';
import EslintPluginMarkdown from 'eslint-plugin-markdown';
import EslintPluginPreferArrowFunctions from 'eslint-plugin-prefer-arrow-functions';
// import EslintPluginTypescript from '@typescript-eslint/eslint-plugin';
import EslintPluginPrettier from 'eslint-plugin-prettier';
import EslintPluginPromise from 'eslint-plugin-promise';
import EslintPluginSimpleImportSort from 'eslint-plugin-simple-import-sort';
import EslintPluginSortDestructureKeys from 'eslint-plugin-sort-destructure-keys';
import JsoncEslintParser from 'jsonc-eslint-parser';
import path from 'path';
import { fileURLToPath } from 'url';

const tsFiles = ['**/*.ts'];
const jsonFiles = ['**/*.json', '**/*.json5', '**/*.jsonc'];

const ignores = ['dist/**/*', '**/*.md/*'];

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const compat = new FlatCompat({
  baseDirectory: __dirname,
});

const common = {
  ignores,
  files: [...tsFiles],
  languageOptions: {
    parser: TypescriptEslintParser,
    parserOptions: {
      project: ['tsconfig.json', 'packages/*/tsconfig.json'],
      ecmaVersion: 'latest',
      sourceType: 'module',
      tsconfigRootDir: __dirname,
    },
  },
  settings: {
    'import/parsers': {
      espree: ['.js', '.cjs', '.mjs', '.jsx'],
      '@typescript-eslint/parser': ['.ts', '.tsx'],
    },
    'import/resolver': {
      typescript: {
        alwaysTryTypes: true,
        project: ['tsconfig.json', 'packages/*/tsconfig.json'],
      },
      node: true,
    },
  },
};

const thisConfig = {
  files: ['eslint.config.js'],
  languageOptions: {
    parser: TypescriptEslintParser,
    parserOptions: {
      project: ['tsconfig.eslint.json'],
      ecmaVersion: 'latest',
      sourceType: 'module',
      tsconfigRootDir: __dirname,
    },
  },
  settings: {
    'import/parsers': {
      espree: ['.js', '.cjs', '.mjs', '.jsx'],
      '@typescript-eslint/parser': ['.ts', '.tsx'],
    },
    'import/resolver': {
      typescript: {
        alwaysTryTypes: true,
        project: ['tsconfig.eslint.json'],
      },
      node: true,
    },
  },
};

const eslintRecommended = [common, thisConfig].map((filter) => ({
  ...js.configs.recommended,
  ...filter,
}));

const airbnbBase = [common, thisConfig]
  .map((filter) =>
    compat.extends('eslint-config-airbnb-base').map((config) => ({
      ...config,
      ...filter,
    })),
  )
  .flat();

const airbnbWhitespace = [common, thisConfig]
  .map((filter) =>
    compat.extends('eslint-config-airbnb-base/whitespace').map((config) => ({
      ...config,
      ...filter,
    })),
  )
  .flat();
const airbnbTypescriptBase = [common, thisConfig]
  .map((filter) =>
    compat.extends('eslint-config-airbnb-typescript/base').map((config) => ({
      ...config,
      ...filter,
    })),
  )
  .flat();
const typescriptEslintStrictTypeChecked = [common, thisConfig]
  .map((filter) =>
    compat.extends('plugin:@typescript-eslint/strict-type-checked').map((config) => ({
      ...config,
      ...filter,
      files: tsFiles,
    })),
  )
  .flat();
const typescriptEslintStylisticTypeChecked = [common, thisConfig]
  .map((filter) =>
    compat.extends('plugin:@typescript-eslint/stylistic-type-checked').map((config) => ({
      ...config,
      ...filter,
    })),
  )
  .flat();

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

const eslintPluginPrettier = [common, thisConfig]
  .map((filter) =>
    compat.config(EslintPluginPrettier.configs.recommended).map((config) => ({
      ...config,
      plugins: {
        prettier: EslintPluginPrettier,
      },
      ...filter,
    })),
  )
  .flat();

const eslintPlugImport = [common, thisConfig]
  .map((filter) =>
    [
      ...compat.config(EslintPluginImport.configs.recommended),
      ...compat.config(EslintPluginImport.configs.typescript),
    ].map((config) => ({
      ...config,
      // plugins: {
      //   import: EslintPluginImport,
      // },
      ...filter,
    })),
  )
  .flat();

const eslintPlugPromise = [common, thisConfig]
  .map((filter) =>
    compat.config(EslintPluginPromise.configs.recommended).map((config) => ({
      ...config,
      plugins: {
        promise: EslintPluginPromise,
      },
      ...filter,
    })),
  )
  .flat();

const eslintPluginJsonc = compat.config(EslintPluginJsonc.configs['recommended-with-jsonc']).map((config) => ({
  ...config,
  plugins: {
    jsonc: EslintPluginJsonc,
  },
  languageOptions: {
    parser: JsoncEslintParser,
  },
  files: jsonFiles,
  ignores,
}));

const eslintPluginMarkdown = [
  {
    plugins: {
      markdown: EslintPluginMarkdown,
      codegen: EslintPluginCodegen,
    },
    processor: {
      ...EslintPluginCodegenProcessors.processor,
      // hack for eslint --cache to work
      meta: { name: 'eslint-plugin-codegen-md-processor', version: EslintPluginCodegen.version },
    },
    files: ['*.md'],
    ignores,
  },
];

const eslintPuginCodegen = [
  {
    rules: { 'codegen/codegen': 'error' },
    plugins: {
      codegen: EslintPluginCodegen,
    },
    files: ['*.md', '**/*.md/*', ...tsFiles],
    ignores,
  },
];

const eslintPluginStylistic = [common, thisConfig].map((filter) => ({
  ...EslintPluginStylistic.configs['recommended-flat'],
  plugins: {
    '@stylistic': EslintPluginStylistic,
  },
  ...filter,
}));

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
  ...eslintPlugImport,
  ...eslintPlugPromise,
  ...[common, thisConfig].map((filter) => ({
    ...filter,
    plugins: {
      deprecation: EslintPluginDeprecation,
      'prefer-arrow-functions': EslintPluginPreferArrowFunctions,
      'simple-import-sort': EslintPluginSimpleImportSort,
      'sort-destructure-keys': EslintPluginSortDestructureKeys,
    },
    linterOptions: {
      reportUnusedDisableDirectives: true,
    },
    rules: {
      /**
       * Custom deprecation rules
       */
      'deprecation/deprecation': 'warn',
      /**
       * Custom general style rules
       */
      // sort destructuring keys
      'sort-destructure-keys/sort-destructure-keys': 'error',
      // naming conventions
      '@typescript-eslint/naming-convention': [
        'error',
        // preferred defaults
        {
          selector: 'default',
          leadingUnderscore: 'forbid',
          trailingUnderscore: 'forbid',
          format: [],
        },
        {
          selector: 'variableLike',
          format: ['camelCase', 'PascalCase', 'UPPER_CASE'],
        },
        { selector: 'function', format: ['camelCase'] },
        { selector: 'typeLike', format: ['PascalCase'] },
        {
          selector: 'property',
          format: ['camelCase'],
        },
        // global exceptions
        {
          selector: 'variable',
          modifiers: ['global', 'const'],
          format: [],
          filter: { regex: '^(__dirname|__filename)$', match: true },
        },
        // adds PascalCase for nested types
        {
          selector: 'typeProperty',
          format: ['camelCase', 'PascalCase'],
        },
        // adds UPPER_CASE for static constants
        {
          selector: 'classProperty',
          modifiers: ['static', 'readonly', 'public'],
          format: ['UPPER_CASE'],
        },
        // remove restrictions when working with JSON objects
        {
          selector: 'objectLiteralProperty',
          format: [],
        },
        // useful for error reporting types with one ignored property
        // e.g., type MyErrorType = { _: never }
        {
          selector: 'typeProperty',
          format: [],
          filter: { regex: '^_$', match: true },
        },
        // useful for ignored parameters
        {
          selector: 'parameter',
          leadingUnderscore: 'allow',
          format: ['camelCase'],
        },
        // Effect exception(s) to underscore rules
        {
          selector: ['typeProperty', 'memberLike'],
          format: [],
          filter: { regex: '^(_tag)$', match: true },
        },
      ],
      // default is warn, covered by above
      'no-underscore-dangle': 'off',
      // default convention is interface, changed to type
      '@typescript-eslint/consistent-type-definitions': ['error', 'type'],
      // default is on, conflicts with Effect conventions
      // e.g., const A = ...; type A = MappedType<typeof A>
      '@typescript-eslint/no-redeclare': 'off',
      // match effects style conventions
      '@stylistic/yield-star-spacing': ['error', 'after'],
      // prettier handles these
      '@stylistic/operator-linebreak': 'off',
      '@stylistic/brace-style': 'off',
      '@stylistic/indent': 'off',
      '@stylistic/indent-binary-ops': 'off',
      '@stylistic/semi': 'off',
      '@stylistic/quotes': 'off',
      // only require quotes when needed
      '@stylistic/quote-props': ['error', 'as-needed'],
      // semis preferred for types
      '@stylistic/member-delimiter-style': [
        'error',
        {
          multiline: {
            delimiter: 'semi',
            requireLast: true,
          },
          singleline: {
            delimiter: 'semi',
            requireLast: false,
          },
          multilineDetection: 'brackets',
        },
      ],
      /**
       * Custom arrow function style enforcement rules
       */
      // default is off
      'arrow-body-style': ['error', 'as-needed'],
      // default is off
      '@stylistic/arrow-parens': ['error', 'always'],
      // default is off
      'prefer-arrow-callback': 'error',
      // default is warn; adds exceptions for generators used by this project
      'func-names': [
        'warn',
        'always',
        {
          generators: 'never',
        },
      ],
      // default is off
      'func-style': 'error',
      // default is off
      'prefer-arrow-functions/prefer-arrow-functions': [
        'error',
        {
          disallowPrototype: true,
          returnStyle: 'implicit',
        },
      ],
      /**
       * Custom comment rules
       */
      // default is off; also adjusted location
      'no-warning-comments': [
        'warn',
        {
          location: 'anywhere',
        },
      ],
      /**
       * Custom import/export rules
       */
      // disable as it conflicts with simple-import-sort
      'sort-imports': 'off',
      // disable as it conflicts with simple-import-sort
      'import/order': 'off',
      // default is warn
      'import/no-duplicates': 'error',
      // check type imports and add dev exceptions
      'import/no-extraneous-dependencies': [
        'error',
        {
          includeTypes: true,
          devDependencies: ['eslint.config.js'],
        },
      ],
      // default is off; set custom sort order
      'simple-import-sort/imports': [
        'error',
        {
          groups: [['^\\u0000'], ['^@?\\w'], ['^#'], ['^\\.']],
        },
      ],
      // default is off
      'simple-import-sort/exports': ['error'],
      // type imports
      '@typescript-eslint/consistent-type-imports': 'error',
      // doesn't mix well with @effect
      'import/prefer-default-export': 'off',
    },
  })),
];

export default eslintConfig;

// enable to review generated rules
//
// import { inspect } from 'node:util';
// console.log(inspect(eslintConfig, false, null, false));
