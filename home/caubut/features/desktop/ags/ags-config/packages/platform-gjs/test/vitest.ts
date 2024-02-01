import { defineConfig } from 'vitest/config';

export default defineConfig({
  test: {
    environment: './vitest.env.ts',
    include: ['**/*.test.ts'],
  },
});
