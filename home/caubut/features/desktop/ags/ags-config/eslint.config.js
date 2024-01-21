import EslintPluginPrettier from 'eslint-plugin-prettier';
import js from '@eslint/js';

import { FlatCompat } from '@eslint/eslintrc';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const compat = new FlatCompat({
  baseDirectory: __dirname,
});

const eslintRecommended = [
  {
    ...js.configs.recommended,
  },
];

const eslintPluginPrettier = [...compat.config(EslintPluginPrettier.configs.recommended)];

const eslintConfig = [...eslintRecommended, ...eslintPluginPrettier];

export default eslintConfig;
