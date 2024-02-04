import { FlatCompat } from '@eslint/eslintrc';
import js from '@eslint/js';
import EslintPluginStylistic from '@stylistic/eslint-plugin';
import TypescriptEslintParser from '@typescript-eslint/parser';
import EslintPluginCodegen from 'eslint-plugin-codegen';
import EslintPluginDeprecation from 'eslint-plugin-deprecation';
import EslintPluginImport from 'eslint-plugin-import';
import EslintPluginPreferArrowFunctions from 'eslint-plugin-prefer-arrow-functions';
import EslintPluginPrettier from 'eslint-plugin-prettier';
import EslintPluginPromise from 'eslint-plugin-promise';
import EslintPluginSimpleImportSort from 'eslint-plugin-simple-import-sort';
import EslintPluginSortDestructureKeys from 'eslint-plugin-sort-destructure-keys';
import path from 'path';
import { fileURLToPath } from 'url';

const jsFiles = ['**/*.js'];
const tsFiles = ['**/*.ts'];

const ignores = ['packages/*/dist/**/*', '**/*.md/*'];

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const compat = new FlatCompat({
  baseDirectory: __dirname,
});

const common = {
  ignores,
  files: [...jsFiles, ...tsFiles],
  languageOptions: {
    parser: TypescriptEslintParser,
    parserOptions: {
      project: ['tsconfig.json'],
      ecmaVersion: 'latest',
      sourceType: 'module',
      tsconfigRootDir: __dirname,
    },
    globals: {
      ARGV: 'readonly',
      Debugger: 'readonly',
      GIRepositoryGType: 'readonly',
      globalThis: 'readonly',
      imports: 'readonly',
      Intl: 'readonly',
      log: 'readonly',
      logError: 'readonly',
      pkg: 'readonly',
      print: 'readonly',
      printerr: 'readonly',
      window: 'readonly',
      TextEncoder: 'readonly',
      TextDecoder: 'readonly',
      console: 'readonly',
      setTimeout: 'readonly',
      setInterval: 'readonly',
      clearTimeout: 'readonly',
      clearInterval: 'readonly',
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
        project: ['tsconfig.json'],
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

const airbnbBase = compat.extends('eslint-config-airbnb-base').map((config) => ({
  ...config,
  ...common,
}));

const airbnbWhitespace = compat.extends('eslint-config-airbnb-base/whitespace').map((config) => ({
  ...config,
  ...common,
}));

const airbnbTypescriptBase = compat.extends('eslint-config-airbnb-typescript/base').map((config) => ({
  ...config,
  ...common,
}));

const typescriptEslintStrictTypeChecked = compat
  .extends('plugin:@typescript-eslint/strict-type-checked')
  .map((config) => ({
    ...config,
    ...common,
    files: tsFiles,
  }));

const typescriptEslintStylisticTypeChecked = compat
  .extends('plugin:@typescript-eslint/stylistic-type-checked')
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

const eslintPluginCodegen = [
  {
    rules: { 'codegen/codegen': 'error' },
    plugins: {
      codegen: EslintPluginCodegen,
    },
    files: ['*.md', '**/*.md/*', ...tsFiles],
    ignores,
  },
];

const eslintPluginStylistic = [
  {
    // eslint-disable-next-line import/no-named-as-default-member
    ...EslintPluginStylistic.configs['recommended-flat'],
    plugins: {
      '@stylistic': EslintPluginStylistic,
    },
    ...common,
  },
];

const eslintConfig = [
  ...eslintRecommended,
  ...eslintPluginStylistic,
  ...eslintPluginCodegen,
  ...airbnbBase,
  ...airbnbWhitespace,
  ...airbnbTypescriptBase,
  ...typescriptEslintStrictTypeChecked,
  ...typescriptEslintStylisticTypeChecked,
  // ...eslintPluginTypescript,
  ...eslintPluginPrettier,
  ...eslintPlugImport,
  ...eslintPlugPromise,
  {
    ...common,
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
      // allow console for gjs
      'no-console': 'off',
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
          devDependencies: [
            'eslint.config.js',
            'packages/*/vitest.*.ts',
            'packages/*/esbuild.*.js',
            'packages/*/test/*test.ts',
          ],
        },
      ],
      // default is off; set custom sort order
      'simple-import-sort/imports': [
        'error',
        {
          groups: [['^\\u0000'], ['^@girs'], ['^@?\\w'], ['^\\.']],
        },
      ],
      // default is off
      'simple-import-sort/exports': ['error'],
      // type imports
      '@typescript-eslint/consistent-type-imports': 'error',
      // doesn't mix well with @effect
      'import/prefer-default-export': 'off',
      // See: https://eslint.org/docs/latest/rules/#possible-problems
      'array-callback-return': 'error',
      'no-await-in-loop': 'error',
      'no-constant-binary-expression': 'error',
      'no-constructor-return': 'error',
      'no-new-native-nonconstructor': 'error',
      'no-promise-executor-return': 'error',
      'no-self-compare': 'error',
      'no-template-curly-in-string': 'error',
      'no-unmodified-loop-condition': 'error',
      'no-unreachable-loop': 'error',
      'no-unused-private-class-members': 'error',
      'no-use-before-define': [
        'error',
        {
          functions: false,
          classes: true,
          variables: true,
          allowNamedExports: true,
        },
      ],
      // See: https://eslint.org/docs/latest/rules/#suggestions
      'block-scoped-var': 'error',
      complexity: 'warn',
      'consistent-return': 'error',
      'default-param-last': 'error',
      eqeqeq: 'error',
      'no-array-constructor': 'error',
      'no-caller': 'error',
      'no-extend-native': 'error',
      'no-extra-bind': 'error',
      'no-extra-label': 'error',
      'no-iterator': 'error',
      'no-label-var': 'error',
      'no-loop-func': 'error',
      'no-multi-assign': 'warn',
      'no-new-object': 'error',
      'no-new-wrappers': 'error',
      'no-proto': 'error',
      'no-shadow': 'off',
      '@typescript-eslint/no-shadow': 'off',
      'no-unused-vars': [
        'error',
        {
          varsIgnorePattern: '^_',
          argsIgnorePattern: '^_',
        },
      ],
      'no-var': 'warn',
      'unicode-bom': 'error',
      // GJS Restrictions
      'no-restricted-globals': [
        'error',
        {
          name: 'Debugger',
          message: 'Internal use only',
        },
        {
          name: 'GIRepositoryGType',
          message: 'Internal use only',
        },
        {
          name: 'log',
          message: 'Use console.log()',
        },
        {
          name: 'logError',
          message: 'Use console.warn() or console.error()',
        },
      ],
      'no-restricted-properties': [
        'error',
        {
          object: 'imports',
          property: 'format',
          message: 'Use template strings',
        },
        {
          object: 'pkg',
          property: 'initFormat',
          message: 'Use template strings',
        },
        {
          object: 'Lang',
          property: 'copyProperties',
          message: 'Use Object.assign()',
        },
        {
          object: 'Lang',
          property: 'bind',
          message: 'Use arrow notation or Function.prototype.bind()',
        },
        {
          object: 'Lang',
          property: 'Class',
          message: 'Use ES6 classes',
        },
      ],
      'no-restricted-syntax': [
        'error',
        {
          selector:
            'MethodDefinition[key.name="_init"] CallExpression[arguments.length<=1][callee.object.type="Super"][callee.property.name="_init"]',
          message: 'Use constructor() and super()',
        },
      ],
    },
  },
];

export default eslintConfig;

// enable to review generated rules
//
// import { inspect } from 'node:util';
// console.log(inspect(eslintConfig, false, null, false));
