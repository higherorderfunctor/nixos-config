import cspellRecommended from '@cspell/eslint-plugin/recommended';
import { fixupConfigRules, fixupPluginRules } from '@eslint/compat';
import { FlatCompat } from '@eslint/eslintrc';
import eslint from '@eslint/js';
import * as stylisticPlugin from '@stylistic/eslint-plugin';
import { Array, pipe, Record } from 'effect';
import codegenPlugin from 'eslint-plugin-codegen';
import importPlugin from 'eslint-plugin-import';
import perfectionistPlugin from 'eslint-plugin-perfectionist';
import preferArrowFunctionsPlugin from 'eslint-plugin-prefer-arrow-functions';
import prettierPlugin from 'eslint-plugin-prettier';
import prettierRecommended from 'eslint-plugin-prettier/recommended';
import promisePlugin from 'eslint-plugin-promise';
import securityPlugin from 'eslint-plugin-security';
import simpleImportSortPlugin from 'eslint-plugin-simple-import-sort';
import tsdocPlugin from 'eslint-plugin-tsdoc';
import * as tseslint from 'typescript-eslint';
import { globals } from '../constants.js';
import { declareGlobals, overrideWith } from '../overrideHelpers.js';
const compat = new FlatCompat({
    baseDirectory: process.cwd(),
});
const plugins = {
    '@typescript-eslint': tseslint.plugin,
    codegen: codegenPlugin,
    import: fixupPluginRules(importPlugin),
    'prefer-arrow-functions': fixupPluginRules(preferArrowFunctionsPlugin),
    prettier: prettierPlugin,
    promise: promisePlugin,
    'simple-import-sort': simpleImportSortPlugin,
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
        'import/cache': {
            lifetime: Infinity,
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
                project: ['tsconfig.utils.json', 'packages/*/tsconfig.{src,lib,tests}.json'],
            },
        },
    },
};
export const eslintConfig = pipe(tseslint.config(eslint.configs.recommended, stylisticPlugin.default.configs['recommended-flat'], ...compat.extends('eslint-config-airbnb-base'), ...fixupConfigRules(compat.extends('eslint-config-airbnb-base/whitespace')), ...compat.extends('eslint-config-airbnb-typescript/base'), ...tseslint.configs.strictTypeChecked, ...tseslint.configs.stylisticTypeChecked, perfectionistPlugin.configs['recommended-alphabetical'], prettierRecommended, { rules: importPlugin.configs.recommended.rules ?? {} }, { rules: importPlugin.configs.typescript.rules ?? {} }, { rules: promisePlugin.configs.recommended.rules ?? {} }, securityPlugin.configs.recommended, cspellRecommended, {
    rules: {
        ...{
            '@typescript-eslint/no-empty-interface': 'off',
            '@typescript-eslint/no-empty-object-type': 'off',
            '@typescript-eslint/no-unnecessary-type-parameters': 'off',
        },
        '@typescript-eslint/naming-convention': [
            'error',
            ...declareGlobals(globals),
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
            {
                format: ['camelCase', 'PascalCase'],
                selector: 'typeProperty',
            },
            {
                format: ['UPPER_CASE'],
                modifiers: ['static', 'readonly', 'public'],
                selector: 'classProperty',
            },
            {
                format: [],
                selector: 'objectLiteralProperty',
            },
            {
                filter: { match: true, regex: '^_$' },
                format: [],
                selector: 'typeProperty',
            },
            {
                format: ['camelCase', 'PascalCase'],
                leadingUnderscore: 'allow',
                selector: 'parameter',
            },
            {
                filter: { match: true, regex: '^(_tag)$' },
                format: [],
                selector: ['typeProperty', 'memberLike'],
            },
        ],
        ...{
            '@typescript-eslint/prefer-readonly': 'error',
            '@typescript-eslint/switch-exhaustiveness-check': 'error',
            'no-param-reassign': 'error',
            'no-var': 'error',
            'prefer-const': 'error',
        },
        ...{
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
            '@stylistic/quote-props': ['error', 'as-needed'],
            '@stylistic/yield-star-spacing': ['error', 'after'],
            '@typescript-eslint/consistent-type-definitions': 'off',
            '@typescript-eslint/no-redeclare': 'off',
            'no-underscore-dangle': 'off',
            ...{
                '@stylistic/indent': 'off',
                '@stylistic/indent-binary-ops': 'off',
                '@stylistic/operator-linebreak': 'off',
                '@stylistic/quotes': 'off',
                '@stylistic/semi': 'off',
            },
            '@typescript-eslint/no-shadow': 'off',
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
        ...{
            '@stylistic/arrow-parens': ['error', 'always'],
            'arrow-body-style': ['error', 'as-needed'],
            'func-names': [
                'warn',
                'always',
                {
                    generators: 'never',
                },
            ],
            'func-style': 'error',
            'prefer-arrow-callback': 'error',
            'prefer-arrow-functions/prefer-arrow-functions': [
                'error',
                {
                    disallowPrototype: true,
                    returnStyle: 'implicit',
                },
            ],
        },
        ...{
            'no-warning-comments': [
                'warn',
                {
                    location: 'anywhere',
                },
            ],
        },
        ...{
            ...{
                '@typescript-eslint/no-namespace': 'off',
                'import/namespace': ['error', { allowComputed: true }],
            },
            '@typescript-eslint/consistent-type-imports': 'error',
            '@typescript-eslint/no-deprecated': 'warn',
            'import/extensions': 'off',
            'import/no-duplicates': 'error',
            'import/no-unresolved': 'off',
            ...{
                'import/order': 'off',
                'perfectionist/sort-imports': 'off',
                'perfectionist/sort-named-imports': 'off',
            },
            'import/prefer-default-export': 'off',
            'simple-import-sort/exports': ['error'],
            'simple-import-sort/imports': [
                'error',
                {
                    groups: [['^\\u0000'], ['^node:'], ['^@?\\w'], ['^@(astal-plugin)'], ['^#'], ['^\\.']],
                },
            ],
            'sort-imports': 'off',
        },
        ...{
            'promise/always-return': ['error', { ignoreLastCallback: true }],
        },
        ...{
            'codegen/codegen': 'error',
        },
        'tsdoc/syntax': 'warn',
        ...{
            complexity: ['warn', { max: 15 }],
            'max-depth': ['warn', { max: 4 }],
            'max-lines-per-function': ['warn', { max: 25 }],
            'max-nested-callbacks': ['warn', { max: 4 }],
            'max-params': ['warn', { max: 5 }],
            'max-statements': ['warn', { max: 10 }],
        },
        '@typescript-eslint/no-this-alias': 'warn',
    },
}), hotfixes, overrideWith(overrides));
export default eslintConfig;
//# sourceMappingURL=strict.js.map