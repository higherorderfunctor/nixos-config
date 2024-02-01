/* File needed to bundle the tests to run on GJS */
import { GLib } from '@girs/glib-2.0';

const global = globalThis as typeof globalThis & {
  process: { env: Record<string, string> };
};

global.process = { env: {} };

const decoder = new TextDecoder('utf-8');

console.log('test');

GLib.log_set_writer_func(
  (_logLlevel, fields: { MESSAGE: Uint8Array; PRIORITY: Uint8Array; GLIB_DOMAIN: Uint8Array }) => {
    const message = decoder.decode(fields.MESSAGE);
    // const priority = Number(decoder.decode(fields.PRIORITY));
    // const domain = decoder.decode(fields.GLIB_DOMAIN);
    print('11', message);
    return GLib.LogWriterOutput.HANDLED;
  },
);

console.log('test');
