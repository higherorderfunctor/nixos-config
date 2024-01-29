/**
 * @since 1.0.0
 */

import * as InternalTerminal from './internal/terminal.js';

export type {
  /**
   * @since 1.0.0
   * @category model
   */
  Key,
  /**
   * @since 1.0.0
   * @category model
   */
  UserInput,
} from '@effect/platform/Terminal';
export {
  /**
   * @since 1.0.0
   * @category tag
   */
  Terminal,
} from '@effect/platform/Terminal';

/**
 * @since 1.0.0
 * @category constructors
 */
export const { make } = InternalTerminal;

/**
 * @since 1.0.0
 * @category layer
 */
export const { layer } = InternalTerminal;
