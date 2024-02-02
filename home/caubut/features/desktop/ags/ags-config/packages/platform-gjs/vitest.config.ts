import { GLib } from '@girs/glib-2.0';

const decoder = new TextDecoder('utf-8');

GLib.log_set_writer_func(
  (_logLlevel, fields: { MESSAGE: Uint8Array; PRIORITY: Uint8Array; GLIB_DOMAIN: Uint8Array }) => {
    const message = decoder.decode(fields.MESSAGE);
    // const priority = Number(decoder.decode(fields.PRIORITY));
    // const domain = decoder.decode(fields.GLIB_DOMAIN);
    print('11', message);
    return GLib.LogWriterOutput.HANDLED;
  },
);

const loop = new GLib.MainLoop(null, false);

import('vitest/config')
  .then(({ defineConfig }) => import('vitest/node').then(({ startVitest }) => ({ defineConfig, startVitest })))
  .then(({ defineConfig, startVitest }) => {
    const vitestConfig = defineConfig({
      test: {
        // environment: './vitest.gjs-env.ts',
        // runner: './vitest.gjs-runner.ts',
        includeSource: ['tests/**/*.test.ts'],
      },
    });
    return startVitest('test', undefined, undefined, vitestConfig);
  })
  .then((vitest) => vitest?.close())
  .then(() => {
    loop.quit();
  })
  .catch(console.error);

loop.run();
