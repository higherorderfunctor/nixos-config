import { GLib } from '@girs/glib-2.0';

const loop = GLib.MainLoop.new(null, false);

run({ testSuite });

loop.run();
