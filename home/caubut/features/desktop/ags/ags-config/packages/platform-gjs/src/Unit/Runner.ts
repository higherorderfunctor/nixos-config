import '../internal/unit/runner.js';

//   /**
//    * @since 1.0.0
//    *
//    * - Docs: [Http/Etag](https://effect-ts.github.io/platform/platform-node-shared/Http/Etag.ts.html)
//    * - Module: `@effect/platform-node-shared/Http/Etag`
//    */
//   assert,
import nodeAssert from 'assert';

export const assert = (success: any, message?: string | Error) => {
  ++countTestsOverall;

  if (!success) {
    ++countTestsFailed;
  }

  nodeAssert(success, message);
};

//   /**
//    * @since 1.0.0
//    *
//    * - Docs: [Http/Etag](https://effect-ts.github.io/platform/platform-node-shared/Http/Etag.ts.html)
//    * - Module: `@effect/platform-node-shared/Http/Etag`
//    */
//   describe,
//   /**
//    * @since 1.0.0
//    *
//    * - Docs: [Http/Etag](https://effect-ts.github.io/platform/platform-node-shared/Http/Etag.ts.html)
//    * - Module: `@effect/platform-node-shared/Http/Etag`
//    */
//   expect,
//   /**
//    * @since 1.0.0
//    *
//    * - Docs: [Http/Etag](https://effect-ts.github.io/platform/platform-node-shared/Http/Etag.ts.html)
//    * - Module: `@effect/platform-node-shared/Http/Etag`
//    */
//   it,
