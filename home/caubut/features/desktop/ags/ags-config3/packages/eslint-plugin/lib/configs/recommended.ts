import cspellRecommended from '@cspell/eslint-plugin/recommended';
import { fixupConfigRules, fixupPluginRules } from '@eslint/compat';
import { FlatCompat } from '@eslint/eslintrc';
import eslint from '@eslint/js';
import * as stylisticPlugin from '@stylistic/eslint-plugin';
import type { TSESLint } from '@typescript-eslint/utils';
import { Array, pipe, Record } from 'effect';
import codegenPlugin from 'eslint-plugin-codegen';
import importPlugin from 'eslint-plugin-import';
// FIXME:
// import functionalPlugin from 'eslint-plugin-functional/flat';
// import securityPlugin from 'eslint-plugin-security';
// import perfectionistPlugin from 'eslint-plugin-perfectionist';
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

const compat = new FlatCompat({
  baseDirectory: process.cwd(),
});

const plugins = {
  '@typescript-eslint': tseslint.plugin,
  prettier: prettierPlugin,
  import: fixupPluginRules(importPlugin),
  'prefer-arrow-functions': fixupPluginRules(preferArrowFunctionsPlugin),
  'simple-import-sort': simpleImportSortPlugin,
  'sort-destructure-keys': sortDestructureKeysPlugin,
  codegen: codegenPlugin,
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
      Record.toEntries(config.rules ?? {}).map(([key, value]) => {
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
    'import/parsers': {
      '@typescript-eslint/parser': ['.ts', '.cts', '.mts', '.tsx', '.js', '.cjs', '.mjs', '.jsx'],
    },
    'import/resolver': {
      typescript: {
        alwaysTryTypes: true,
        project: ['tsconfig.utils.json', 'packages/*/tsconfig.{src,lib,tests}.json'],
        extensionAlias: {
          '.js': ['.ts'],
        },
      },
      node: true,
    },
    'import/cache': {
      lifetime: Infinity, // speeds up LSP but requires manual cache clearing
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
    ...compat.extends('eslint-config-airbnb-base'),
    ...fixupConfigRules(compat.extends('eslint-config-airbnb-base/whitespace')),
    ...compat.extends('eslint-config-airbnb-typescript/base'),
    // typescript-eslint
    ...tseslint.configs.strictTypeChecked,
    ...tseslint.configs.stylisticTypeChecked,
    // FIXME: perfectionistPlugin.configs['recommended-alphabetical'],
    // prettier
    prettierRecommended,
    // import
    { rules: importPlugin.configs.recommended.rules ?? {} },
    { rules: importPlugin.configs.typescript.rules ?? {} },
    // promise
    { rules: promisePlugin.configs.recommended.rules ?? {} },
    // FIXME: functional
    // functionalPlugin.configs.strict,
    // functionalPlugin.configs.stylistic,
    // FIXME: security
    // securityPlugin.configs.recommended,
    // spellchecking
    cspellRecommended as TSESLint.FlatConfig.Config,
    {
      rules: {
        /**
         * Custom deprecation rules
         */
        '@typescript-eslint/no-deprecated': 'warn',
        /**
         * Custom general style rules
         */
        // sort destructuring keys
        'sort-destructure-keys/sort-destructure-keys': 'error',
        // FIXME: https://perfectionist.dev/rules/sort-intersection-types
        // sort union and other stuff
        // types
        // FIXME: '@typescript-eslint/ban-types': ['error', { types: { '{}': false }, extendDefaults: true }],
        '@typescript-eslint/no-empty-interface': 'off',
        '@typescript-eslint/no-empty-object-type': 'off',
        '@typescript-eslint/no-unnecessary-type-parameters': 'off',
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
            format: ['camelCase', 'PascalCase'],
          },
          // Effect exception(s) to underscore rules
          {
            selector: ['typeProperty', 'memberLike'],
            format: [],
            filter: { regex: '^(_tag)$', match: true },
          },
        ],
        // immutability rules
        // NOTE: https://github.com/eslint-functional/eslint-plugin-functional/?tab=readme-ov-file#external-recommended-rules
        '@typescript-eslint/prefer-readonly': 'error',
        '@typescript-eslint/switch-exhaustiveness-check': 'error',
        'no-var': 'error',
        'no-param-reassign': 'error',
        'prefer-const': 'error',
        // default is warn, covered by above
        'no-underscore-dangle': 'off',
        // there are some situations where one is better than the other
        // // default convention is interface, changed to type
        // // FIXME: set to interface when ready to do conversions
        // '@typescript-eslint/consistent-type-definitions': ['error', 'type'], #44
        '@typescript-eslint/consistent-type-definitions': 'off',
        // default is on, conflicts with Effect conventions
        // e.g., const A = ...; type A = MappedType<typeof A>
        '@typescript-eslint/no-redeclare': 'off',
        // match effects style conventions
        '@stylistic/yield-star-spacing': ['error', 'after'],
        // han:dled by prettier
        '@stylistic/operator-linebreak': 'off',
        '@stylistic/brace-style': 'off',
        '@stylistic/indent': 'off',
        '@stylistic/indent-binary-ops': 'off',
        '@stylistic/semi': 'off',
        '@stylistic/quotes': 'off',
        // emulate TS with exceptions for names that start with _
        '@typescript-eslint/no-unused-vars': [
          'error',
          {
            args: 'all',
            argsIgnorePattern: '^_',
            caughtErrors: 'all',
            caughtErrorsIgnorePattern: '^_',
            destructuredArrayIgnorePattern: '^_',
            varsIgnorePattern: '^_',
            ignoreRestSiblings: true,
          },
        ],
        // allow redclares in different scopes
        '@typescript-eslint/no-shadow': 'off',
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
        // namespaces rules
        '@typescript-eslint/no-namespace': 'off',
        'import/namespace': ['error', { allowComputed: true }],
        // disable as TypeScript will catch with TS2307
        'import/no-unresolved': 'off',
        // // bun hacks
        // 'import/no-unresolved': ['error', { ignore: ['bun:test'] }],
        // disable as it conflicts with simple-import-sort
        'sort-imports': 'off',
        // disable as it conflicts with simple-import-sort
        'import/order': 'off',
        // default is warn
        'import/no-duplicates': 'error',
        // disable as TypeScript will catch with TS2835
        'import/extensions': 'off',
        // doesn't mix well with @effect
        'import/prefer-default-export': 'off',
        // default is off; set custom sort order
        'simple-import-sort/imports': [
          'error',
          {
            groups: [['^\\u0000'], ['^node:'], ['^@?\\w'], ['^@(astal-config)/'], ['^@/'], ['^\\.']],
          },
        ],
        // default is off
        'simple-import-sort/exports': ['error'],
        // type imports
        '@typescript-eslint/consistent-type-imports': 'error',
        /**
         * Custom promise rules
         */
        'promise/always-return': ['error', { ignoreLastCallback: true }],
        /**
         * Code generator rules
         */
        'codegen/codegen': 'error',
        /**
         * Doc comment rules
         */
        'tsdoc/syntax': 'warn',
      },
    },
  ),
  hotfixes,
  overrideWith(overrides),
);

export default eslintConfig;
