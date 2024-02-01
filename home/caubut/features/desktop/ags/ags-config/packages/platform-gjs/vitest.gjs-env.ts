import type { Environment } from 'vitest';

const GjsEnvironment: Environment = {
  name: 'gjs',
  transformMode: 'ssr',
  setupVM: () => {
    const context = {};
    return {
      getVmContext: () => context,
      teardown: () => {},
    };
  },
  setup: () => ({
    teardown: () => {},
  }),
};

export default GjsEnvironment;
