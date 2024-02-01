/* File needed to bundle the tests to run on GJS */

import { GLib } from '@girs/glib-2.0';

// import { run } from '@gjsify/unit';
import { testSuite } from './FileSystem.test.js';

const decoder = new TextDecoder('utf-8');

// GLib.log_set_writer_func(
//   (logLlevel, fields: { MESSAGE: Uint8Array; PRIORITY: Uint8Array; GLIB_DOMAIN: Uint8Array }) => {
//     const message = decoder.decode(fields.MESSAGE);
//     // const priority = Number(decoder.decode(fields.PRIORITY));
//     // const domain = decoder.decode(fields.GLIB_DOMAIN);
//     print('11', message);
//     return GLib.LogWriterOutput.HANDLED;
//   },
// );

try {
  const loop = new GLib.MainLoop(null, false);
  run({ testSuite }).then(() => {
    loop.quit();
  });
  loop.run();
} catch (error) {
  console.error(error);
}
