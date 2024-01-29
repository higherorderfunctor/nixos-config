import '@girs/gjs/dom';

import { GObject } from '@girs/gobject-2.0';
import { Gtk } from '@girs/gtk-4.0';

import { Args, Command, Options } from '@effect/cli';
import { NodeContext, Runtime } from '@effect/platform-gjs';
import { Config, ConfigProvider, Console, Effect, Option, ReadonlyArray } from 'effect';

// const loop = GLib.MainLoop.new(null, false);

// const help = (bin: string) => `USAGE:
//     ${bin} [OPTIONS]
//
// OPTIONS:
//     -h, --help              Print this help and exit
//     -v, --version           Print version and exit
//     -q, --quit              Kill AGS
//     -c, --config            Path to the config file. Default: ${DEFAULT_CONF}
//     -b, --bus-name          Bus name of the process
//     -i, --inspector         Open up the Gtk debug tool
//     -t, --toggle-window     Show or hide a window
//     -r, --run-js            Execute string as an async function
//     -f, --run-file          Execute file as an async function
//     -I, --init              Initialize the configuration directory
//     -C, --clear-cache       Remove ${Utils.CACHE_DIR}`;
class App extends Gtk.Application {
  vfunc_activate() {
    const window = new Gtk.ApplicationWindow({ application: this });
    const label = new Gtk.Label({ label: 'Hello World!' });
    window.child = label;
    window.connect('close-request', () => {
      // TODO: loop.quit();
    });
    window.present();
  }
}

export const FbrApplication = GObject.registerClass(
  {
    GTypeName: 'FbrApplication',
  },
  App,
);

const program = Effect.gen(function* (_) {
  const app = new App();
  app.run(null);
});

const configs = Options.keyValueMap('c').pipe(Options.optional);
const egs = Command.make('effect-gnome-shell', { configs }, ({ configs }) => {
  console.log('!!', configs);
  return Option.match(configs, {
    onNone: () => Console.log("Running 'effect-gnome-shel'"),
    onSome: (configs) => {
      const keyValuePairs = Array.from(configs)
        .map(([key, value]) => `${key}=${value}`)
        .join(', ');
      return Console.log(`Running 'minigit' with the following configs: ${keyValuePairs}`);
    },
  });
});

const command = egs;

const cli = Command.run(command, {
  name: 'effect-gnome-shell',
  version: 'v1.0.0',
});

console.log(ARGV);
console.log(['test', ...ARGV]);
Effect.suspend(() => cli(['effect-gnome-shell', ...ARGV])).pipe(
  Effect.withConfigProvider(ConfigProvider.nested(ConfigProvider.fromEnv(), 'GIT')),
  Effect.provide(NodeContext.layer),
  Runtime.runMain,
);

// export const main = () => new FbrApplication({ application_id: 'egs' }).run(null);
// loop.run();
