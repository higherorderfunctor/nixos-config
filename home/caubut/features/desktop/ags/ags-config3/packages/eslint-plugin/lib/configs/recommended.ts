import path from 'node:path';

import cspellRecommended from '@cspell/eslint-plugin/recommended';
import { fixupConfigRules, fixupPluginRules } from '@eslint/compat';
import { FlatCompat } from '@eslint/eslintrc';
import eslint from '@eslint/js';
import * as stylisticPlugin from '@stylistic/eslint-plugin';
import type { TSESLint } from '@typescript-eslint/utils';
import { Array, pipe, Record } from 'effect';
import codegenPlugin from 'eslint-plugin-codegen';
import importPlugin from 'eslint-plugin-import';
import preferArrowFunctionsPlugin from 'eslint-plugin-prefer-arrow-functions';
import prettierPlugin from 'eslint-plugin-prettier';
import prettierRecommended from 'eslint-plugin-prettier/recommended';
import promisePlugin from 'eslint-plugin-promise';
import simpleImportSortPlugin from 'eslint-plugin-simple-import-sort';
import sortDestructureKeysPlugin from 'eslint-plugin-sort-destructure-keys';
import tsdocPlugin from 'eslint-plugin-tsdoc';
import * as tseslint from 'typescript-eslint';

import { globals } from '../constants.js';
import { declareGlobals, overrideWith } from '../overrideHelpers.js';
import { airbnbConfig } from './airbnb.js';

const compat = new FlatCompat({
  baseDirectory: path.resolve(import.meta.dirname, '../../../../'),
});

const plugins = {
  '@typescript-eslint': tseslint.plugin,
  'prefer-arrow-functions': fixupPluginRules(preferArrowFunctionsPlugin),
  'simple-import-sort': simpleImportSortPlugin,
  'sort-destructure-keys': sortDestructureKeysPlugin,
  codegen: codegenPlugin,
  import: fixupPluginRules(importPlugin),
  prettier: prettierPlugin,
  promise: promisePlugin,
  tsdoc: tsdocPlugin,
};

const hotfixes = Array.map<TSESLint.FlatConfig.ConfigArray, TSESLint.FlatConfig.Config>(
  (config: TSESLint.FlatConfig.Config) => ({
    ...config,
    // NOTE: Fixes an issue with @eslint/eslintrc in the eslint-config-airbnb-base/whitespace patch causing
    // eslint-plugin-import to not appear as the same version.  Prefer a cleaner solution, but this works well
    // enough until all dependencies have caught up to eslint 9.
    plugins: { ...config.plugins, ...plugins },
    rules: Record.fromEntries(
      Record.toEntries(config.rules ?? {}).map(([key, value]) =>   {
        switch (key) {
          // airbnb rules that have been renamed in newer plugin versions
          case '@typescript-eslint/lines-between-class-members':
            return ['@stylistic/lines-between-class-members', value];
          case '@typescript-eslint/no-throw-literal':
            return ['@typescript-eslint/only-throw-error', value];
          default:
            return [key, value];
        }
      }),
    ),
  }),
);

export const overrides: Partial<Partial<TSESLint.FlatConfig.Config>> = {
  plugins,
  settings: {
    'import/cache': {
      lifetime: Infinity, // speeds up LSP but requires manual cache clearing
    },
    'import/internal-regex': /^@(astal-plugin)?\//,
    'import/parsers': {
      '@typescript-eslint/parser': ['.ts', '.cts', '.mts', '.tsx', '.js', '.cjs', '.mjs', '.jsx'],
    },
    'import/resolver': {
      node: true,
      typescript: {
        alwaysTryTypes: true,
        extensionAlias: {
          '.js': ['.ts'],
        },
        project: ['tsconfig.json'],
      },
    },
  },
};

export const eslintConfig: TSESLint.FlatConfig.ConfigArray = pipe(
  tseslint.config(
    // eslint
    eslint.configs.recommended,
    // stylistic
    stylisticPlugin.default.configs['recommended-flat'],
    // airbnb
    airbnbConfig,
    // ...compat.extends('eslint-config-airbnb-base'),
    // ...fixupConfigRules(compat.extends('eslint-config-airbnb-base/whitespace')),
    // ...compat.extends('eslint-config-airbnb-typescript/base'),
    // typescript-eslint
    ...tseslint.configs.strictTypeChecked,
    ...tseslint.configs.stylisticTypeChecked,
    // prettier
    prettierRecommended,
    // import
    { rules: importPlugin.configs.recommended.rules ?? {} },
    { rules: importPlugin.configs.typescript.rules ?? {} },
    // promise
    { rules: promisePlugin.configs.recommended.rules ?? {} },
    // spellchecking
    cspellRecommended as TSESLint.FlatConfig.Config,
    {
      rules: {
        /**
         * Custom general style rules
         */
        // sort destructuring keys
        'sort-destructure-keys/sort-destructure-keys': 'error',
        // FIXME: https://perfectionist.dev/rules/sort-intersection-types
        // sort union and other stuff
        // types
        // FIXME: '@typescript-eslint/ban-types': ['error', { types: { '{}': false }, extendDefaults: true }],
        ...{
          '@typescript-eslint/no-empty-interface': 'off',
          '@typescript-eslint/no-empty-object-type': 'off',
          '@typescript-eslint/no-unnecessary-type-parameters': 'off',
        },
        // don't allow void in places it doesn't make sense
        '@typescript-eslint/no-invalid-void-type': [
          'error',
          {
            // prevent needing to bind functions that have an unused this
            allowAsThisParameter: true,
            // allow as a generic type parameter
            allowInGenericTypeArguments: true,
          },
        ],
        // naming conventions
        '@typescript-eslint/naming-convention': [
          'error',
          // declared globals
          ...declareGlobals(globals),
          // preferred defaults
          {
            format: [],
            leadingUnderscore: 'forbid',
            selector: 'default',
            trailingUnderscore: 'forbid',
          },
          {
            format: ['camelCase', 'PascalCase', 'UPPER_CASE'],
            selector: 'variableLike',
          },
          { format: ['camelCase'], selector: 'function' },
          { format: ['PascalCase'], selector: 'typeLike' },
          {
            format: ['camelCase'],
            selector: 'property',
          },
          // adds PascalCase for nested types
          {
            format: ['camelCase', 'PascalCase'],
            selector: 'typeProperty',
          },
          // adds UPPER_CASE for static constants
          {
            format: ['UPPER_CASE'],
            modifiers: ['static', 'readonly', 'public'],
            selector: 'classProperty',
          },
          // remove restrictions when working with JSON objects
          {
            format: [],
            selector: 'objectLiteralProperty',
          },
          // useful for error reporting types with one ignored property
          // e.g., type MyErrorType = { _: never }
          {
            filter: { match: true, regex: '^_$' },
            format: [],
            selector: 'typeProperty',
          },
          // useful for ignored parameters
          {
            format: ['camelCase', 'PascalCase'],
            leadingUnderscore: 'allow',
            selector: 'parameter',
          },
          // Effect exception(s) to underscore rules
          {
            filter: { match: true, regex: '^(_tag)$' },
            format: [],
            selector: ['typeProperty', 'memberLike'],
          },
        ],
        // immutability rules
        // NOTE: https://github.com/eslint-functional/eslint-plugin-functional/?tab=readme-ov-file#external-recommended-rules
        ...{
          '@typescript-eslint/prefer-readonly': 'error',
          '@typescript-eslint/switch-exhaustiveness-check': 'error',
          'no-param-reassign': 'error',
          'no-var': 'error',
          'prefer-const': 'error',
        },
        ...{
          // semis preferred for types
          '@stylistic/member-delimiter-style': [
            'error',
            {
              multiline: {
                delimiter: 'semi',
                requireLast: true,
              },
              multilineDetection: 'brackets',
              singleline: {
                delimiter: 'semi',
                requireLast: false,
              },
            },
          ],
          // only require quotes when needed
          '@stylistic/quote-props': ['error', 'as-needed'],
          // match effects style conventions
          '@stylistic/yield-star-spacing': ['error', 'after'],
          // there are some situations where one is better than the other
          // // default convention is interface, changed to type
          // // FIXME: set to interface when ready to do conversions
          // '@typescript-eslint/consistent-type-definitions': ['error', 'type'], #44
          '@typescript-eslint/consistent-type-definitions': 'off',
          // default is on, conflicts with Effect conventions
          // e.g., const A = ...; type A = MappedType<typeof A>
          '@typescript-eslint/no-redeclare': 'off',
          // default is warn, covered by above
          'no-underscore-dangle': 'off',
          // handled by prettier
          ...{
            '@stylistic/brace-style': 'off',
            '@stylistic/indent': 'off',
            '@stylistic/indent-binary-ops': 'off',
            '@stylistic/operator-linebreak': 'off',
            '@stylistic/quotes': 'off',
            '@stylistic/semi': 'off',
          },
          // allow redeclares in different scopes
          '@typescript-eslint/no-shadow': 'off',
          // emulate TS with exceptions for names that start with _
          '@typescript-eslint/no-unused-vars': [
            'error',
            {
              args: 'all',
              argsIgnorePattern: '^_',
              caughtErrors: 'all',
              caughtErrorsIgnorePattern: '^_',
              destructuredArrayIgnorePattern: '^_',
              ignoreRestSiblings: true,
              varsIgnorePattern: '^_',
            },
          ],
        },
        /**
         * Custom arrow function style enforcement rules
         */
        ...{
          // default is off
          '@stylistic/arrow-parens': ['error', 'always'],
          // default is off
          'arrow-body-style': ['error', 'as-needed'],
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
          'prefer-arrow-callback': 'error',
          // default is off
          'prefer-arrow-functions/prefer-arrow-functions': [
            'error',
            {
              disallowPrototype: true,
              returnStyle: 'implicit',
            },
          ],
        },
        /**
         * Custom comment rules
         */
        ...{
          // default is off; also adjusted location
          'no-warning-comments': [
            'warn',
            {
              location: 'anywhere',
            },
          ],
        },
        /**
         * Custom import/export rules
         */
        ...{
          // namespaces rules
          ...{
            '@typescript-eslint/no-namespace': 'off',
            'import/namespace': ['error', { allowComputed: true }],
          },
          // type imports
          '@typescript-eslint/consistent-type-imports': 'error',
          // deprecated rules
          '@typescript-eslint/no-deprecated': 'warn',
          // disable as TypeScript will catch with TS2835
          'import/extensions': 'off',
          // default is warn
          'import/no-duplicates': 'error',
          // disable as TypeScript will catch with TS2307
          'import/no-unresolved': 'off',
          // // bun hacks
          // 'import/no-unresolved': ['error', { ignore: ['bun:test'] }],
          // disable as it conflicts with simple-import-sort
          ...{
            'import/order': 'off',
            'sort-imports': 'off',
          },
          // doesn't mix well with @effect
          'import/prefer-default-export': 'off',
          // default is off
          'simple-import-sort/exports': ['error'],
          // default is off; set custom sort order
          'simple-import-sort/imports': [
            'error',
            {
              groups: [['^\\u0000'], ['^(bun|node):'], ['^@?\\w'], ['^@(astal-plugin)\/'], ['^@'], ['^\\.']],
            },
          ],
        },
        /**
         * Custom promise rules
         */
        ...{
          'promise/always-return': ['error', { ignoreLastCallback: true }],
        },
        /**
         * Code generator rules
         */
        ...{
          'codegen/codegen': 'error',
        },
        /**
         * Doc comment rules
         */
        ...{
          'tsdoc/syntax': 'warn',
        },
      },
    },
  ),
  hotfixes,
  overrideWith(overrides),
);

export default eslintConfig;
