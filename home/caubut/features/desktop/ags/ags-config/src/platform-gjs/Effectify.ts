import { Gio } from "@girs/gio-2.0"

import * as Effect from "effect/Effect"

type ArgsWithoutCancellable<Args extends Array<any>> = [...args: Args, cancellable: Gio.Cancellable | null]

type EndsWith<T, U extends string> = T extends string ? (T extends `${infer _Start}${U}` ? T : never) : never

type AsyncMethodKeys<T> = {
  [K in keyof T]: K extends EndsWith<K, "_async">
    ? T[K] extends (...args: ArgsWithoutCancellable<infer _Args>) => Promise<infer _R> ? K
    : never
    : never
}[keyof T]

type WithoutPromise<T> = T extends Promise<infer R> ? R : never

export type Effectify<
  T extends abstract new(...args: any) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  E
> = InstanceType<T>[K] extends (...args: ArgsWithoutCancellable<infer Args>) => Promise<infer R>
  ? (obj: InstanceType<T>, ...args: [...Args, cancellable?: Gio.Cancellable | null]) => Effect.Effect<never, E, R>
  : never

export const effectify: <
  T extends abstract new(...args: Array<any>) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  E
>(
  proto: T,
  method: K,
  onError: (e: unknown, args: [obj: InstanceType<T>, ...Parameters<InstanceType<T>[K]>]) => E
) => Effectify<T, K, E> = <
  T extends abstract new(...args: Array<any>) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  E,
  R extends WithoutPromise<ReturnType<InstanceType<T>[K]>>
>(
  proto: T,
  method: K,
  onError: (e: unknown, args: [obj: InstanceType<T>, ...Parameters<InstanceType<T>[K]>]) => E
) => {
  Gio._promisify(proto.prototype, method as string)
  return (...args: [obj: InstanceType<T>, ...args: Parameters<InstanceType<T>[K]>]) => {
    const obj = args[0]
    const cancellable = (args[args.length - 1] as Gio.Cancellable | null)
      ? (args[args.length - 1] as Gio.Cancellable)
      : Gio.Cancellable.new()
    return Effect.tryPromise({
      try: (signal) => {
        signal.addEventListener("abort", () => {
          cancellable.cancel()
        })
        return obj[method](...args.slice(0, args.length - 2), cancellable) as Promise<R>
      },
      catch: (error) => onError(error, args)
    })
  }
}
