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
Object.defineProperty(exports, "__esModule", { value: true });
var tseslint = require("typescript-eslint");
var vue_eslint_parser_1 = require("vue-eslint-parser");
var eslint_plugin_1 = require("@astal-config/eslint-plugin");
var ignores = [
    '**/.mypy_cache/**/*', // python type checking cache
    '**/.nvfetcher/**/*', // nix generated configs
    '**/.rollup-cache/**/*', // rollup cache
    '**/.venv/**/*', // python virtual environment
    '**/.vscode/**/*', // vscode settings
    '**/.vuepress/**/*', // vuepress generated files
    '**/node_modules/**/*', // node dependencies
    '.changeset/**/*', // changeset files
    '.direnv/**/*', // direnv virtual environment dependencies
    '.tmp/**/*', // in repo temp files
    'build/**/*', // build artifacts
    'docs/c4/**/*', // c4 generated files
    'etc/bruno/**/*', // bruno generated configs
    'etc/postman/**/*', // postman generated configs
    'packages/*/dist/**/*', // build artifacts
    'packages/client-portal/*/dist/**/*', // build artifacts
    'packages/core/*/dist/**/*', // build artifacts
    'packages/core/eslint-plugin/lib/**/*.{js,js.map,d.ts,d.ts.map}', // generated files
    'results/**/*', // nix build artifacts
];
var extraFileExtensions = ['.vue'];
/**
 * Base CSpell ESLint configuration.
 */
var cspellRules = {
    '@cspell/spellchecker': ['warn', { configFile: './cspell.config.json' }],
};
/**
 * Base TypeScript ESLint configuration.
 */
var tsParserOptions = {
    ecmaVersion: 'latest',
    // optimization only for ProjectService to prevent project refresh
    extraFileExtensions: extraFileExtensions,
    projectService: true,
    sourceType: 'module',
    tsconfigRootDir: import.meta.dirname,
    warnOnUnsupportedTypeScriptVersion: false,
};
var tsConfigOverrides = {
    rules: __assign(__assign({}, (process.env.GITLAB_CI === undefined
        ? {
            'import/namespace': 'off',
            'import/no-cycle': 'off',
            'import/no-duplicates': 'off',
            'import/no-extraneous-dependencies': 'off',
            'import/no-relative-packages': 'off',
            'import/no-self-import': 'off',
        }
        : {
            'import/namespace': 'error',
            'import/no-cycle': 'error',
            'import/no-duplicates': 'error',
            // check type imports and add development exceptions
            'import/no-extraneous-dependencies': [
                'error',
                {
                    devDependencies: [
                        'commitlint.config.ts',
                        'renovate.cjs',
                        'eslint.*.[tj]s',
                        'packages/*/*/esbuild.*.ts',
                        'packages/*/esbuild.*.ts',
                        'packages/*/tests/**/*.[tj]s',
                        'packages/*/tests/*.[tj]s',
                        'packages/core/*/tests/**/*.[tj]s',
                        'packages/core/*/tests/*.[tj]s',
                        'rollup.config.ts',
                        'vendor/**/*.d.ts',
                    ],
                    includeTypes: true,
                },
            ],
            'import/no-relative-packages': 'error',
            'import/no-self-import': 'error',
        })), cspellRules),
};
var tsConfigLanguageOptions = {
    parser: tseslint.parser,
    parserOptions: tsParserOptions,
};
/**
 * Strict TypeScript configuration.
 */
var strictTsConfigFiles = ['eslint.config.ts', 'packages/core/rollup-build/bin/*.ts'];
var strictTsConfig = eslint_plugin_1.default.overrideWith(__spreadArray(__spreadArray([], eslint_plugin_1.default.configs.strict, true), [tsConfigOverrides], false), {
    files: strictTsConfigFiles,
    languageOptions: tsConfigLanguageOptions,
});
/**
 * Recommended TypeScript ESLint configuration.
 */
var tsConfig = eslint_plugin_1.default.overrideWith(__spreadArray(__spreadArray([], eslint_plugin_1.default.configs.recommended, true), [tsConfigOverrides], false), {
    files: [
        '*.[cm]js',
        '*.[cm]ts',
        '*.js',
        '*.ts',
        'packages/*/*/esbuild.*.ts',
        'packages/*/esbuild.*.ts',
        'packages/*/{lib,tests}/**/*.ts',
        'packages/core/*/{lib,tests}/**/*.ts',
        'vendor/types/**/*.d.ts',
    ],
    ignores: strictTsConfigFiles,
    languageOptions: tsConfigLanguageOptions,
});
/**
 * Vue ESLint configuration.
 */
var vueConfig = eslint_plugin_1.default.overrideWith(__spreadArray(__spreadArray([], eslint_plugin_1.default.configs['vue/recommended'], true), [
    {
        rules: __assign({}, cspellRules),
    },
], false), {
    files: [
        'packages/client-portal/backend/esbuild.config.ts',
        'packages/client-portal/backend/{src,tests}/**/*.ts',
        'packages/client-portal/frontend/env.d.ts',
        'packages/client-portal/frontend/vite.config.ts',
        'packages/client-portal/frontend/{src,tests}/**/*.ts',
        'packages/client-portal/frontend/{src,tests}/**/*.vue',
    ],
    languageOptions: {
        parser: vue_eslint_parser_1.default,
        parserOptions: __assign(__assign({}, tsParserOptions), { extraFileExtensions: extraFileExtensions, parser: {
                '<template>': tseslint.parser,
                js: tseslint.parser,
                ts: tseslint.parser,
            } }),
    },
});
/**
 * JSON ESLint configuration.
 */
var jsonConfig = eslint_plugin_1.default.overrideWith(eslint_plugin_1.default.configs['json/recommended'], {
    files: ['**/*.json', '**/*.json[c5]'],
});
/**
 * Markdown ESLint configuration.
 *
 * TODO: lint code examples
 */
// const markdownConfig = astalPlugin.overrideWith(astalPlugin.configs['markdown/recommended'], {
//   files: ['**/*.md'],
// });
/**
 * ESLint configuration
 */
var eslintConfig = __spreadArray(__spreadArray(__spreadArray(__spreadArray([
    // global configs
    { ignores: ignores },
    {
        linterOptions: {
            reportUnusedDisableDirectives: true,
        },
    }
], tsConfig, true), strictTsConfig, true), vueConfig, true), jsonConfig, true);
exports.default = eslintConfig;
