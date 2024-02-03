/* eslint-disable @typescript-eslint/ban-types */
/* eslint-disable @typescript-eslint/naming-convention */


/* eslint-disable @typescript-eslint/no-explicit-any */

import { Gio } from '@girs/gio-2.0';

import * as Effect from 'effect/Effect';

type ArgsWithoutCancellable<Args extends any[]> = [...args: Args, cancellable: Gio.Cancellable | null];

type EndsWith<T, U extends string> = T extends string ? (T extends `${infer _Start}${U}` ? T : never) : never;

type AsyncMethodKeys<T> = {
  [K in keyof T]: K extends EndsWith<K, '_async'>
    ? T[K] extends (...args: ArgsWithoutCancellable<infer _Args>) => Promise<infer _R>
      ? K
      : never
    : never;
}[keyof T];

type MethodKeys<T> = {
  [P in keyof T]: T[P] extends Function ? P : never;
}[keyof T];

type Z = MethodKeys<Gio.File>;
type ZZ = AsyncMethodKeys<Gio.File>;

export type Effectify<
  T extends abstract new (...args: any) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  E,,
> = InstanceType<T>[K] extends (...args: ArgsWithoutCancellable<infer Args>) => Promise<infer R>
  ? (obj: InstanceType<T>, ...args: [...Args, cancellable?: Gio.Cancellable | null]) => Effect.Effect<never, E, R>
  : never;

export const effectify: <
  T extends abstract new (...args: any[]) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  F extends InstanceType<T>[K],
  E>(
    proto: T,
    method: K,
    onError: (e: unknown, args: [obj: InstanceType<T>, ...Parameters<InstanceType<T>[K]>]) => E,
) => Effectify<T, K, E> = <
  T extends abstract new (...args: any[]) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  F extends InstanceType<T>[K],
  E,
>(
  proto: T,
  method: K,
  onError: (e: unknown, args: [obj: InstanceType<T>, ...Parameters<InstanceType<T>[K]>]) => E,
) => {
  Gio._promisify(proto, method as string);
  return (
    obj: InstanceType<T>,
    ...args: Parameters<F>
  ) => {
    const cancellable = args[args.length - 1] as Gio.Cancellable | null;
    const f = obj[method];
    Effect.tryPromise({
      try: (signal) => {
        const _cancellable = cancellable || Gio.Cancellable.new();
        signal.addEventListener('abort', () => {
          _cancellable.cancel();
        });
        const z = obj[method];
        const zz = z(...args, _cancellable);

        return zz;
      },
      catch: onError,
    });
  };
};

export const x = effectify(Gio.File, 'make_symbolic_link_async', () => new Error());

// const file = Gio.File.new_for_path('');
