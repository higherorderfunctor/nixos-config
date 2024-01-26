import { Command, Options } from '@effect/cli';
import { Console, Effect } from 'effect';

// minigit [--version] [-h | --help] [-c <name>=<value>]
const config = Options.file('config', { exists: 'yes' }).pipe(Options.withAlias('v'));
const egs = Command.make('minigit', { config }, ({ config }) => Effect.succeed(Console.log(config)));

const cli = Command.run(egs, {
  name: 'effect-gnome-shell',
  version: 'v0.0.0',
});

import '@girs/gjs';
import '@girs/glib-2.0';
import '@girs/gio-2.0';
import GLib from 'gi://GLib';
import Gio from 'gi://Gio';

Gio._promisify(Gio.File.prototype, 'query_info_async');
const file = Gio.File.new_for_path('/tmp/tes');
try {
  const z = await file.query_info_async(
    Gio.FILE_ATTRIBUTE_ACCESS_CAN_READ,
    Gio.FileQueryInfoFlags.NONE,
    GLib.PRIORITY_DEFAULT,
    null,
    //(...args: any[]) => console.log('!', args),
  );
} catch (e) {
  if (e instanceof GLib.Error) {
    console.log(e.line);
    console.log({
      arguments: e.arguments,
      message: e.message,
      code: e.code,
      line: e.line,
      domain: e.domain,
      name: e.name,
      stack: e.stack,
      caller: e.caller,
      column: e.column,
      length: e.length,
      source: e.source,
      fileName: e.fileName,
    });
    console.log('###', e.message.match(/(?<=^Error when getting information for file “).*(?=”:)/));
    console.log(e.domain, e.code, Gio.io_error_quark());
    console.log(e.matches(Gio.IOErrorEnum, Gio.IOErrorEnum.NOT_FOUND));
  }
  console.log('@@', e);
}
// console.log('!', z.has_attribute(Gio.FILE_ATTRIBUTE_ACCESS_CAN_READ));
// console.log('!', z.get_attribute_boolean(Gio.FILE_ATTRIBUTE_ACCESS_CAN_READ));

// FileSystem | Path | Terminal

const program = Effect.suspend(() => cli(process.argv));
Effect.runSync(Effect.suspend(() => Console.log('test')));

import { Effect, Console, Schedule } from 'effect';

const barJob = Effect.repeat(Console.log('Bar: still running!'), Schedule.fixed('1 seconds'));

const fooJob = Effect.gen(function* (_) {
  yield* _(Effect.forkDaemon(barJob));
  yield* _(Effect.sleep('3 seconds'));
});

await Effect.runPromise(fooJob);
