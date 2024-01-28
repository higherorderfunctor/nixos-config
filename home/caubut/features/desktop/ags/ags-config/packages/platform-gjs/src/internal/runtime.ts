import '@girs/gjs';

import { GLib } from '@girs/glib-2.0';

import { defaultTeardown, type RunMain } from '@effect/platform/Runtime';
import * as Cause from 'effect/Cause';
import * as Effect from 'effect/Effect';

const SIGINT = 2;
const SIGTERM = 15;

/** @internal */
export const runMain: RunMain = <E, A>(effect: Effect.Effect<never, E, A>, teardown = defaultTeardown) => {
  imports.package.init({
    name: '@PACKAGE_NAME@',
    version: '@PACKAGE_VERSION@',
    prefix: '@PREFIX@',
    libdir: '@LIBDIR@',
  });

  const loop = GLib.MainLoop.new(null, false);

  const fiber = Effect.runFork(
    Effect.tapErrorCause(effect, (cause) => {
      if (Cause.isInterruptedOnly(cause)) {
        return Effect.unit;
      }
      return Effect.logError(cause);
    }),
  );

  fiber.addObserver((exit) => {
    teardown(exit, (code) => {
      loop.quit();
      imports.system.exit(code);
    });
  });

  let sigintSource = 0;
  let sigtermSource = 0;
  console.log('here');
  const onSigint = (source: number) => () => {
    console.log(`Received signal ${source}`);
    // remove the other signal listeners that did not trigger this handler
    if (source === SIGINT && sigtermSource) {
      GLib.source_remove(sigtermSource);
    }
    if (source === SIGTERM && sigintSource) {
      GLib.source_remove(sigintSource);
    }
    fiber.unsafeInterruptAsFork(fiber.id());
    // remove this signal listener
    return GLib.SOURCE_REMOVE;
  };

  sigintSource = GLib.unix_signal_add(GLib.PRIORITY_DEFAULT, SIGINT, onSigint(SIGINT));
  sigtermSource = GLib.unix_signal_add(GLib.PRIORITY_DEFAULT, SIGTERM, onSigint(SIGTERM));
};
