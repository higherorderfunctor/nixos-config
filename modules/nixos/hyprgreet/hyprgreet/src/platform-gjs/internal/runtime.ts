import { defaultTeardown, type RunMain } from '@effect/platform/Runtime';
import System from '@girs/gjs/system';
import { GLib } from '@girs/glib-2.0';
import * as Cause from 'effect/Cause';
import * as Effect from 'effect/Effect';

const SIGINT = 2;
const SIGTERM = 15;

/** @internal */
export const runMain: RunMain = (effect, options) => {
  const teardown = options?.teardown ?? defaultTeardown;
  const keepAlive = setInterval(() => {}, 2 ** 31 - 1);

  // const loop = GLib.MainLoop.new(null, false)

  const fiber = Effect.runFork(
    options?.disableErrorReporting === true
      ? effect
      : Effect.tapErrorCause(effect, (cause) => {
          if (Cause.isInterruptedOnly(cause)) {
            return Effect.unit;
          }
          return Effect.logError(cause);
        }),
  );

  fiber.addObserver((exit) => {
    clearInterval(keepAlive);
    teardown(exit, (code) => {
      // loop.quit()
      System.exit(code);
    });
  });

  let sigintSource = 0;
  let sigtermSource = 0;

  const onSigint = (source: number) => () => {
    // remove the other signal listeners that did not trigger this handler
    if (source === SIGINT && sigtermSource) {
      GLib.source_remove(sigtermSource);
      sigtermSource = 0;
    }
    if (source === SIGTERM && sigintSource) {
      GLib.source_remove(sigintSource);
      sigintSource = 0;
    }
    fiber.unsafeInterruptAsFork(fiber.id());
    // remove this signal listener
    return GLib.SOURCE_REMOVE;
  };

  sigintSource = GLib.unix_signal_add(GLib.PRIORITY_DEFAULT, SIGINT, onSigint(SIGINT));
  sigtermSource = GLib.unix_signal_add(GLib.PRIORITY_DEFAULT, SIGTERM, onSigint(SIGTERM));
};
