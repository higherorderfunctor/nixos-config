"use strict";
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
var _a, _b, _c;
Object.defineProperty(exports, "__esModule", { value: true });
exports.eslintConfig = exports.overrides = void 0;
var recommended_1 = require("@cspell/eslint-plugin/recommended");
var compat_1 = require("@eslint/compat");
var eslintrc_1 = require("@eslint/eslintrc");
var js_1 = require("@eslint/js");
var stylisticPlugin = require("@stylistic/eslint-plugin");
var effect_1 = require("effect");
var eslint_plugin_codegen_1 = require("eslint-plugin-codegen");
var eslint_plugin_import_1 = require("eslint-plugin-import");
// FIXME:
// import functionalPlugin from 'eslint-plugin-functional/flat';
// import securityPlugin from 'eslint-plugin-security';
// import perfectionistPlugin from 'eslint-plugin-perfectionist';
var eslint_plugin_prefer_arrow_functions_1 = require("eslint-plugin-prefer-arrow-functions");
var eslint_plugin_prettier_1 = require("eslint-plugin-prettier");
var recommended_2 = require("eslint-plugin-prettier/recommended");
var eslint_plugin_promise_1 = require("eslint-plugin-promise");
var eslint_plugin_simple_import_sort_1 = require("eslint-plugin-simple-import-sort");
var eslint_plugin_sort_destructure_keys_1 = require("eslint-plugin-sort-destructure-keys");
var eslint_plugin_tsdoc_1 = require("eslint-plugin-tsdoc");
var tseslint = require("typescript-eslint");
var constants_js_1 = require("../constants.js");
var overrideHelpers_js_1 = require("../overrideHelpers.js");
var compat = new eslintrc_1.FlatCompat({
    baseDirectory: process.cwd(),
});
var plugins = {
    '@typescript-eslint': tseslint.plugin,
    prettier: eslint_plugin_prettier_1.default,
    import: (0, compat_1.fixupPluginRules)(eslint_plugin_import_1.default),
    'prefer-arrow-functions': (0, compat_1.fixupPluginRules)(eslint_plugin_prefer_arrow_functions_1.default),
    'simple-import-sort': eslint_plugin_simple_import_sort_1.default,
    'sort-destructure-keys': eslint_plugin_sort_destructure_keys_1.default,
    codegen: eslint_plugin_codegen_1.default,
    promise: eslint_plugin_promise_1.default,
    tsdoc: eslint_plugin_tsdoc_1.default,
};
var hotfixes = effect_1.Array.map(function (config) {
    var _a;
    return (__assign(__assign({}, config), { 
        // NOTE: Fixes an issue with @eslint/eslintrc in the eslint-config-airbnb-base/whitespace patch causing
        // eslint-plugin-import to not appear as the same version.  Prefer a cleaner solution, but this works well
        // enough until all dependencies have caught up to eslint 9.
        plugins: __assign(__assign({}, config.plugins), plugins), rules: effect_1.Record.fromEntries(effect_1.Record.toEntries((_a = config.rules) !== null && _a !== void 0 ? _a : {}).map(function (_a) {
            var key = _a[0], value = _a[1];
            switch (key) {
                // airbnb rules that have been renamed in newer plugin versions
                case '@typescript-eslint/lines-between-class-members':
                    return ['@stylistic/lines-between-class-members', value];
                case '@typescript-eslint/no-throw-literal':
                    return ['@typescript-eslint/only-throw-error', value];
                default:
                    return [key, value];
            }
        })) }));
});
exports.overrides = {
    plugins: plugins,
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
exports.eslintConfig = (0, effect_1.pipe)(tseslint.config.apply(tseslint, __spreadArray(__spreadArray(__spreadArray(__spreadArray(__spreadArray(__spreadArray([
    // eslint
    js_1.default.configs.recommended,
    // stylistic
    stylisticPlugin.default.configs['recommended-flat']], compat.extends('eslint-config-airbnb-base'), false), (0, compat_1.fixupConfigRules)(compat.extends('eslint-config-airbnb-base/whitespace')), false), compat.extends('eslint-config-airbnb-typescript/base'), false), tseslint.configs.strictTypeChecked, false), tseslint.configs.stylisticTypeChecked, false), [
    // FIXME: perfectionistPlugin.configs['recommended-alphabetical'],
    // prettier
    recommended_2.default,
    // import
    { rules: (_a = eslint_plugin_import_1.default.configs.recommended.rules) !== null && _a !== void 0 ? _a : {} },
    { rules: (_b = eslint_plugin_import_1.default.configs.typescript.rules) !== null && _b !== void 0 ? _b : {} },
    // promise
    { rules: (_c = eslint_plugin_promise_1.default.configs.recommended.rules) !== null && _c !== void 0 ? _c : {} },
    // FIXME: functional
    // functionalPlugin.configs.strict,
    // functionalPlugin.configs.stylistic,
    // FIXME: security
    // securityPlugin.configs.recommended,
    // spellchecking
    recommended_1.default,
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
            '@typescript-eslint/naming-convention': __spreadArray(__spreadArray([
                'error'
            ], (0, overrideHelpers_js_1.declareGlobals)(constants_js_1.globals), true), [
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
            ], false),
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
    }], false)), hotfixes, (0, overrideHelpers_js_1.overrideWith)(exports.overrides));
exports.default = exports.eslintConfig;
