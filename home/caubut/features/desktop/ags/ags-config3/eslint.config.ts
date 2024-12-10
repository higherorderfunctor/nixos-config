import type { TSESLint } from '@typescript-eslint/utils';
import * as tseslint from 'typescript-eslint';

import astalPlugin from '@astal-config/eslint-plugin';

const ignores = [
  '**/.rollup-cache/**/*', // rollup cache
  '**/node_modules/**/*', // node dependencies
  'packages/*/dist/**/*', // build artifacts
];

const extraFileExtensions: string[] = [];

/**
 * Base CSpell ESLint configuration.
 */
const cspellRules: TSESLint.FlatConfig.Rules = {
  '@cspell/spellchecker': ['warn', { configFile: './cspell.config.json' }],
};

/**
 * Base TypeScript ESLint configuration.
 */
const tsParserOptions: TSESLint.FlatConfig.ParserOptions = {
  ecmaVersion: 'latest',
  // optimization only for ProjectService to prevent project refresh
  extraFileExtensions,
  projectService: true,
  sourceType: 'module',
  tsconfigRootDir: import.meta.dirname,
  warnOnUnsupportedTypeScriptVersion: false,
};

const tsConfigOverrides: TSESLint.FlatConfig.Config = {
  rules: {
    // performance exceptions outside of CI (e.g., LSP)
    ...(process.env.GITLAB_CI === undefined
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
                'eslint.*.[tj]s',
                'packages/*/tests/**/*.[tj]s',
                'packages/*/tests/*.[tj]s',
                'rollup.config.ts',
                'vendor/**/*.d.ts',
              ],
              includeTypes: true,
            },
          ],
          'import/no-relative-packages': 'error',
          'import/no-self-import': 'error',
        }),
    // spellchecking
    ...cspellRules,
  },
};

const tsConfigLanguageOptions: TSESLint.FlatConfig.LanguageOptions = {
  parser: tseslint.parser,
  parserOptions: tsParserOptions,
};

/**
 * Strict TypeScript configuration.
 */
const strictTsConfigFiles = ['eslint.config.ts', 'packages/core/rollup-build/bin/*.ts'];

const strictTsConfig = astalPlugin.overrideWith([...astalPlugin.configs.strict, tsConfigOverrides], {
  files: strictTsConfigFiles,
  languageOptions: tsConfigLanguageOptions,
});

/**
 * Recommended TypeScript ESLint configuration.
 */
const tsConfig = astalPlugin.overrideWith([...astalPlugin.configs.recommended, tsConfigOverrides], {
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
 * JSON ESLint configuration.
 */
const jsonConfig = astalPlugin.overrideWith(astalPlugin.configs['json/recommended'], {
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
const eslintConfig = [
  // global configs
  { ignores },
  {
    linterOptions: {
      reportUnusedDisableDirectives: true,
    },
  },
  // specific configs
  ...tsConfig,
  ...strictTsConfig,
  ...jsonConfig,
  // ...markdownConfig,
];

export default eslintConfig;
