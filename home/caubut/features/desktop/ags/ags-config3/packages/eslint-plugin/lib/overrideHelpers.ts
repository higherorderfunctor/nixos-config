import type { TSESLint } from '@typescript-eslint/utils';
import { Array } from 'effect';
import { dual } from 'effect/Function';

export const overrideWith: {
  (
    overrides: Partial<TSESLint.FlatConfig.Config>,
  ): (configs: TSESLint.FlatConfig.ConfigArray) => TSESLint.FlatConfig.ConfigArray;
  (
    configs: TSESLint.FlatConfig.ConfigArray,
    overrides: Partial<TSESLint.FlatConfig.Config>,
  ): TSESLint.FlatConfig.ConfigArray;
} = dual(
  2,
  (
    configs: TSESLint.FlatConfig.ConfigArray,
    overrides: Partial<TSESLint.FlatConfig.Config>,
  ): TSESLint.FlatConfig.ConfigArray =>
    configs.map((config) => ({
      ...config,
      ...overrides,
      plugins: { ...overrides.plugins, ...(config.plugins ?? {}) },
    })),
);

export const declareGlobals = (globals: readonly string[]) => {
  if (Array.isEmptyReadonlyArray(globals)) {
    return [];
  }
  return [
    {
      filter: {
        match: true,
        regex: `^(${globals.join('|')})$`,
      },
      format: [],
      modifiers: ['const'], // global doesn't work in a `declare global` block
      selector: 'variable',
    },
  ];
};
