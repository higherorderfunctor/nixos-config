import * as internal from './internal/runtime.js';

export type { RunMain, Teardown } from '@effect/platform/Runtime';
export { defaultTeardown } from '@effect/platform/Runtime';

export const { runMain } = internal;
