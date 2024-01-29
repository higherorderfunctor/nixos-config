/**
 * @since 1.0.0
 */

import * as internal from './internal/path.js';

export {
  /**
   * @since 1.0.0
   * @category tag
   */
  Path,
} from '@effect/platform/Path';

/**
 * @since 1.0.0
 * @category layer
 */
export const { layer } = internal;

/**
 * @since 1.0.0
 * @category layer
 */
export const { layerPosix } = internal;

/**
 * @since 1.0.0
 * @category layer
 */
export const { layerWin32 } = internal;
