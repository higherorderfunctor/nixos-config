import { Gio } from "@girs/gio-2.0"

import * as Effect from "effect/Effect"

type ArgsWithCancellable<Args extends Array<any>> = [...args: Args, cancellable: Gio.Cancellable | null]

type EndsWith<T, U extends string> = T extends string ? (T extends `${infer _Start}${U}` ? T : never) : never

type AsyncMethodKeys<T> = {
  [K in keyof T]: K extends EndsWith<K, "_async">
    ? T[K] extends (...args: ArgsWithCancellable<infer _Args>) => Promise<infer _R> ? K
    : never
    : never
}[keyof T]

type RemoveLast<T extends Array<any>> = T extends [...infer Rest, any] ? Rest : never

export type Effectify<
  T extends abstract new(...args: any) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  E
> = InstanceType<T>[K] extends (...args: ArgsWithCancellable<infer Args>) => Promise<any> ? (
    obj: InstanceType<T>,
    ...args: [...Args, cancellable?: Gio.Cancellable | null]
  ) => Effect.Effect<Awaited<ReturnType<InstanceType<T>[K]>>, E>
  : never

export const effectify = <
  T extends abstract new(...args: Array<any>) => any,
  K extends AsyncMethodKeys<InstanceType<T>>,
  E
>(
  proto: T,
  method: K,
  onError: (e: unknown, args: [obj: InstanceType<T>, ...Parameters<InstanceType<T>[K]>]) => E
): Effectify<T, K, E> => {
  Gio._promisify(proto.prototype, method as string)
  return (
    obj: InstanceType<T>,
    ...args: [...RemoveLast<Parameters<InstanceType<T>[K]>>, cancellable?: Gio.Cancellable | null]
  ) => {
    const cancellable = (args[args.length - 1] as Gio.Cancellable | null | undefined)
      ? (args[args.length - 1] as Gio.Cancellable)
      : Gio.Cancellable.new()
    const result = Effect.tryPromise({
      try: (signal) => {
        signal.addEventListener("abort", () => {
          cancellable.cancel()
        })
        return obj[method](...args.slice(0, args.length - 2), cancellable) as Promise<
          Awaited<ReturnType<InstanceType<T>[K]>>
        >
      },
      catch: (error) => onError(error, [obj, ...args])
    })
    return result
  }
}
