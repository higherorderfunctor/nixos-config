/* eslint-disable @typescript-eslint/naming-convention */
/* eslint-disable @typescript-eslint/ban-types */

/* eslint-disable @typescript-eslint/no-unsafe-argument */
/* eslint-disable @typescript-eslint/no-explicit-any */
import { Gio } from '@girs/gio-2.0';

import * as Effect from 'effect/Effect';

import type { Effectify } from '../Effectify.js';

/** @internal */
export const effectify: <F extends (...args: any[]) => Promise<any>>(fn: F) => Effectify<F> =
  (fn: Function, onError?: (e: unknown, args: any) => any, cancellable: Gio.Cancellable | null = null) =>
  (...args: any[]) =>
    Effect.tryPromise({
      try: (signal) => {
        const _cancellable = cancellable;
        if (_cancellable)
          signal.addEventListener('abort', () => {
            _cancellable.cancel();
          });
        const z = obj[method](...args, _cancellable);

        return z;
      },
      catch: onError,
    });

const file = Gio.File.new_for_path(path);
Gio._promisify(Gio.File.prototype, 'make_directory_async');
const x = effectify(file.load_contents);
