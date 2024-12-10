import type { TSESLint } from '@typescript-eslint/utils';
import { pipe } from 'effect';
import jsoncPlugin from 'eslint-plugin-jsonc';
import prettierPlugin from 'eslint-plugin-prettier';
import prettierRecommended from 'eslint-plugin-prettier/recommended';
import jsoncParser from 'jsonc-eslint-parser';
import tseslint from 'typescript-eslint';

import { overrideWith } from '../../overrideHelpers.js';

const plugins = {
  jsonc: jsoncPlugin,
  prettier: prettierPlugin,
};

const overrides: Partial<Partial<TSESLint.FlatConfig.Config>> = {
  plugins,
  languageOptions: {
    parser: jsoncParser,
  },
};

const eslintConfig: TSESLint.FlatConfig.ConfigArray = pipe(
  tseslint.config(
    prettierRecommended,
    ...(jsoncPlugin.configs['flat/prettier'] as TSESLint.FlatConfig.ConfigArray),
    ...(jsoncPlugin.configs['flat/recommended-with-jsonc'] as TSESLint.FlatConfig.ConfigArray),
  ),
  overrideWith(overrides),
);

export default eslintConfig;
