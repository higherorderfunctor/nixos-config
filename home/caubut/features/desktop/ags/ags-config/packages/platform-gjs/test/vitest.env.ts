import type { Environment } from 'vitest';

export default {
  name: 'gjs',
  transformMode: 'ssr',
  setup: () => ({
    teardown: () => {
      // called after all tests with this env have been run
    },
  }),
} as Environment;
