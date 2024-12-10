declare module 'eslint-plugin-promise' {
  import type { TSESLint } from '@typescript-eslint/utils';

  const plugin: TSESLint.FlatConfig.Plugin & { configs: { recommended: TSESLint.FlatConfig.Config } };
  export default plugin;
}
