declare module 'eslint-plugin-import' {
  import type { FixupPluginDefinition } from '@eslint/compat';
  import type { TSESLint } from '@typescript-eslint/utils';

  const plugin: FixupPluginDefinition & {
    configs: { recommended: TSESLint.FlatConfig.Config; typescript: TSESLint.FlatConfig.Config };
  };
  export default plugin;
}
