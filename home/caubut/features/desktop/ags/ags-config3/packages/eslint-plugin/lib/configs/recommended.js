import cspellRecommended from '@cspell/eslint-plugin/recommended';
import { fixupConfigRules, fixupPluginRules } from '@eslint/compat';
import { FlatCompat } from '@eslint/eslintrc';
import eslint from '@eslint/js';
import * as stylisticPlugin from '@stylistic/eslint-plugin';
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
const hotfixes = Array.map((config) => ({
    ...config,
    plugins: { ...config.plugins, ...plugins },
    rules: Record.fromEntries(Record.toEntries(config.rules ?? {}).map(([key, value]) => {
        switch (key) {
            case '@typescript-eslint/lines-between-class-members':
                return ['@stylistic/lines-between-class-members', value];
            case '@typescript-eslint/no-throw-literal':
                return ['@typescript-eslint/only-throw-error', value];
            default:
                return [key, value];
        }
    })),
}));
export const overrides = {
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
            lifetime: Infinity,
        },
    },
};
export const eslintConfig = pipe(tseslint.config(eslint.configs.recommended, stylisticPlugin.default.configs['recommended-flat'], ...compat.extends('eslint-config-airbnb-base'), ...fixupConfigRules(compat.extends('eslint-config-airbnb-base/whitespace')), ...compat.extends('eslint-config-airbnb-typescript/base'), ...tseslint.configs.strictTypeChecked, ...tseslint.configs.stylisticTypeChecked, prettierRecommended, { rules: importPlugin.configs.recommended.rules ?? {} }, { rules: importPlugin.configs.typescript.rules ?? {} }, { rules: promisePlugin.configs.recommended.rules ?? {} }, cspellRecommended, {
    rules: {
        '@typescript-eslint/no-deprecated': 'warn',
        'sort-destructure-keys/sort-destructure-keys': 'error',
        '@typescript-eslint/no-empty-interface': 'off',
        '@typescript-eslint/no-empty-object-type': 'off',
        '@typescript-eslint/no-unnecessary-type-parameters': 'off',
        '@typescript-eslint/no-invalid-void-type': [
            'error',
            {
                allowAsThisParameter: true,
                allowInGenericTypeArguments: true,
            },
        ],
        '@typescript-eslint/naming-convention': [
            'error',
            ...declareGlobals(globals),
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
            {
                selector: 'typeProperty',
                format: ['camelCase', 'PascalCase'],
            },
            {
                selector: 'classProperty',
                modifiers: ['static', 'readonly', 'public'],
                format: ['UPPER_CASE'],
            },
            {
                selector: 'objectLiteralProperty',
                format: [],
            },
            {
                selector: 'typeProperty',
                format: [],
                filter: { regex: '^_$', match: true },
            },
            {
                selector: 'parameter',
                leadingUnderscore: 'allow',
                format: ['camelCase', 'PascalCase'],
            },
            {
                selector: ['typeProperty', 'memberLike'],
                format: [],
                filter: { regex: '^(_tag)$', match: true },
            },
        ],
        '@typescript-eslint/prefer-readonly': 'error',
        '@typescript-eslint/switch-exhaustiveness-check': 'error',
        'no-var': 'error',
        'no-param-reassign': 'error',
        'prefer-const': 'error',
        'no-underscore-dangle': 'off',
        '@typescript-eslint/consistent-type-definitions': 'off',
        '@typescript-eslint/no-redeclare': 'off',
        '@stylistic/yield-star-spacing': ['error', 'after'],
        '@stylistic/operator-linebreak': 'off',
        '@stylistic/brace-style': 'off',
        '@stylistic/indent': 'off',
        '@stylistic/indent-binary-ops': 'off',
        '@stylistic/semi': 'off',
        '@stylistic/quotes': 'off',
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
        '@typescript-eslint/no-shadow': 'off',
        '@stylistic/quote-props': ['error', 'as-needed'],
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
        'arrow-body-style': ['error', 'as-needed'],
        '@stylistic/arrow-parens': ['error', 'always'],
        'prefer-arrow-callback': 'error',
        'func-names': [
            'warn',
            'always',
            {
                generators: 'never',
            },
        ],
        'func-style': 'error',
        'prefer-arrow-functions/prefer-arrow-functions': [
            'error',
            {
                disallowPrototype: true,
                returnStyle: 'implicit',
            },
        ],
        'no-warning-comments': [
            'warn',
            {
                location: 'anywhere',
            },
        ],
        '@typescript-eslint/no-namespace': 'off',
        'import/namespace': ['error', { allowComputed: true }],
        'import/no-unresolved': 'off',
        'sort-imports': 'off',
        'import/order': 'off',
        'import/no-duplicates': 'error',
        'import/extensions': 'off',
        'import/prefer-default-export': 'off',
        'simple-import-sort/imports': [
            'error',
            {
                groups: [['^\\u0000'], ['^node:'], ['^@?\\w'], ['^@(astal-config)/'], ['^@/'], ['^\\.']],
            },
        ],
        'simple-import-sort/exports': ['error'],
        '@typescript-eslint/consistent-type-imports': 'error',
        'promise/always-return': ['error', { ignoreLastCallback: true }],
        'codegen/codegen': 'error',
        'tsdoc/syntax': 'warn',
    },
}), hotfixes, overrideWith(overrides));
export default eslintConfig;
//# sourceMappingURL=recommended.js.map