import EslintPluginPrettier from 'eslint-plugin-prettier';
import TypescriptEslintParser from '@typescript-eslint/parser';
import js from '@eslint/js';

import { FlatCompat } from '@eslint/eslintrc';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const jsFiles = ['**/*.js'];
const tsFiles = ['**/*.ts'];

const common = {
  files: [...jsFiles, ...tsFiles],
  languageOptions: {
    parser: TypescriptEslintParser,
    parserOptions: {
      project: ['tsconfig.json'],
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
        project: ['tsconfig.json'],
      },
    },
  },
};

const compat = new FlatCompat({
  baseDirectory: __dirname,
});

const eslintRecommended = [
  {
    ...js.configs.recommended,
    ...common,
  },
];

const eslintPluginPrettier = [
  ...compat.config(EslintPluginPrettier.configs.recommended).map((config) => ({ ...config, ...common })),
];

const eslintConfig = [...eslintRecommended, ...eslintPluginPrettier];

export default eslintConfig;
