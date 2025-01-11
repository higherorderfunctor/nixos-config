import cspellRecommended from '@cspell/eslint-plugin/recommended';
import type { TSESLint } from '@typescript-eslint/utils';
import vuePrettierConfig from '@vue/eslint-config-prettier';
import vueTsConfig from '@vue/eslint-config-typescript';
import { pipe } from 'effect';
import vuePlugin from 'eslint-plugin-vue';
import vueA11yPlugin from 'eslint-plugin-vuejs-accessibility';
import vuetifyPlugin from 'eslint-plugin-vuetify';
import tseslint from 'typescript-eslint';

import { overrideWith } from '../../overrideHelpers.js';
import * as settings from '../../settings/index.js';
// import * as importConfig from '../import.js';
// import * as recommendedConfig from '../recommended.js';
import * as strictConfig from '../strict.js';

export const overrides: Partial<TSESLint.FlatConfig.Config> = {
  ...strictConfig.overrides,
  // ...recommendedConfig.overrides,
  processor: vuePlugin.processors.vue as string,
  settings: settings.typescript,
};

const eslintConfig: TSESLint.FlatConfig.ConfigArray = pipe(
  tseslint.config(
    ...vuePlugin.configs['flat/recommended'],
    ...vueTsConfig(),
    ...vuetifyPlugin.configs['flat/recommended'],
    ...(vueA11yPlugin.configs['flat/recommended'] as TSESLint.FlatConfig.ConfigArray),
    // FIXME: temp until merged with base recommended
    cspellRecommended as TSESLint.FlatConfig.Config,
    vuePrettierConfig, // should always be last of vue rules
    ...strictConfig.eslintConfig,
    // ...importConfig.default,
    {
      rules: {
        // FIXME: temp until merged with base recommended
        // '@typescript-eslint/no-unused-vars': [
        //   'error',
        //   {
        //     args: 'all',
        //     argsIgnorePattern: '^_',
        //     caughtErrors: 'all',
        //     caughtErrorsIgnorePattern: '^_',
        //     destructuredArrayIgnorePattern: '^_',
        //     ignoreRestSiblings: true,
        //     varsIgnorePattern: '^_',
        //   },
        // ],
        // doesn't work with vue
        'codegen/codegen': 'off',
      },
    },
  ),
  overrideWith(overrides),
);

export default eslintConfig;
