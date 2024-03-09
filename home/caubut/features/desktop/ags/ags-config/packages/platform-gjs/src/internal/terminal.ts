import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import * as Terminal from '@effect/platform/Terminal';
import * as Effect from 'effect/Effect';
import { identity } from 'effect/Function';
import * as Layer from 'effect/Layer';
import * as Option from 'effect/Option';

import { effectify } from '../Effectify.js';

// const defaultShouldQuit = (input: Terminal.UserInput): boolean =>
//   input.key.ctrl && (input.key.name === 'c' || input.key.name === 'd');

export const make = () => {
  const stdin = new Gio.DataInputStream(new Gio.UnixInputStream({ fd: 0, close_fd: false }));
  // const readBytesAsync = effectify(Gio.DataInputStream, 'read_bytes_async', identity);
  const readLineAsync = effectify(Gio.DataInputStream, 'read_line_async', identity);
  const readInput = Effect.sync(() => stdin.read_byte(null)).pipe(
    Effect.catchAll(Effect.die),
    Effect.map((byte): Terminal.UserInput => {
      const input = String.fromCharCode(byte);
      return {
        input: Option.some(input),
        key: { name: input, ctrl: false, meta: false, shift: false },
      };
    }),
  );
  const readLine = readLineAsync(stdin, GLib.PRIORITY_DEFAULT).pipe(
    Effect.catchAll(Effect.die),
    Effect.map((bytes) => String.fromCharCode.apply(null, Array.from((bytes as unknown as GLib.Bytes).toArray()))),
  );
  return Effect.succeed(
    Terminal.Terminal.of({
      // The columns property can be undefined if stdout was redirected
      columns: Effect.sync(() => 0),
      readInput,
      readLine,
      display: (text) =>
        Effect.sync(() => {
          print(text);
        }),
    }),
  );
};

/** @internal */
export const layer: Layer.Layer<never, never, Terminal.Terminal> = Layer.scoped(Terminal.Terminal, make());
