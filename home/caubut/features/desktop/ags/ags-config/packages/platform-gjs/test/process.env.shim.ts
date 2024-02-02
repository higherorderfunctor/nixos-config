/* File needed to bundle the tests to run on GJS */
import { GLib } from '@girs/glib-2.0';

const global = globalThis as typeof globalThis & {
  process: { env: Record<string, string> };
};

global.process = { env: {} };
