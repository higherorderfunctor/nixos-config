import '@girs/gjs';
import '@girs/glib-2.0';
import '@girs/gio-2.0';

import { Command, Options } from '@effect/cli';
import { NodeContext, Runtime } from '@egs/platform-gjs';
import { Console, Effect } from 'effect';
// import Gio from 'gi://Gio';
// import GLib from 'gi://GLib';

const config = Options.file('config', { exists: 'yes' }).pipe(Options.withAlias('v'));
const egs = Command.make('minigit', { config }, ({ config }) => Effect.succeed(Console.log(config)));

const cli = Command.run(egs, {
  name: 'effect-gnome-shell',
  version: 'v0.0.0',
});

Effect.suspend(() => cli(process.argv.slice(2))).pipe(Effect.provide(NodeContext.layer), Runtime.runMain);
