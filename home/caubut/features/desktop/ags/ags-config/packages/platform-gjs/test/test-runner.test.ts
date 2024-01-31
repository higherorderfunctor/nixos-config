/* File needed to bundle the tests to run on GJS */
import { GLib } from '@girs/glib-2.0';

import { run } from '@gjsify/unit';

import { testSuite } from './FileSystem.test.js';

const loop = new GLib.MainLoop(null, false);

run({ testSuite }).then(() => {
  loop.quit();
});

loop.run();
