import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import * as Fs from '@effect/platform-gjs/FileSystem.js';
import { run } from '@gjsify/unit';
import { Effect } from 'effect';
import * as vlq from 'vlq';

export type RawSourceMap = {
  version: number;
  sources: string[];
  names: string[];
  sourceRoot?: string;
  sourcesContent?: string[];
  mappings: string;
  file: string;
};

type VlqState = [number, number, number, number, number];

type SegmentInfo = {
  columnIndex: number;
  source: string;
  line: number;
  column: number;
  name?: string | undefined;
};

const colors = {
  reset: '\x1b[0m',
  bright: '\x1b[1m',
  dim: '\x1b[2m',
  underscore: '\x1b[4m',
  blink: '\x1b[5m',
  reverse: '\x1b[7m',
  hidden: '\x1b[8m',

  fg: {
    black: '\x1b[30m',
    red: '\x1b[31m',
    green: '\x1b[32m',
    yellow: '\x1b[33m',
    blue: '\x1b[34m',
    magenta: '\x1b[35m',
    cyan: '\x1b[36m',
    white: '\x1b[37m',
    crimson: '\x1b[38m',
  },
  bg: {
    black: '\x1b[40m',
    red: '\x1b[41m',
    green: '\x1b[42m',
    yellow: '\x1b[43m',
    blue: '\x1b[44m',
    magenta: '\x1b[45m',
    cyan: '\x1b[46m',
    white: '\x1b[47m',
    crimson: '\x1b[48m',
  },
};

const logLevelToString = (logLevel: GLib.LogLevelFlags) => {
  switch (logLevel) {
    case GLib.LogLevelFlags.LEVEL_CRITICAL:
      return 'CRITICAL';
    case GLib.LogLevelFlags.LEVEL_ERROR:
      return 'ERROR';
    case GLib.LogLevelFlags.LEVEL_WARNING:
      return 'WARNING';
    case GLib.LogLevelFlags.LEVEL_MESSAGE:
      return 'MESSAGE';
    case GLib.LogLevelFlags.LEVEL_INFO:
      return 'INFO';
    case GLib.LogLevelFlags.LEVEL_DEBUG:
      return 'DEBUG';
    default:
      return 'UNKNOWN';
  }
};

const logLevelToColor = (logLevel: GLib.LogLevelFlags) => {
  switch (logLevel) {
    case GLib.LogLevelFlags.LEVEL_CRITICAL:
      return colors.fg.red;
    case GLib.LogLevelFlags.LEVEL_ERROR:
      return colors.fg.crimson;
    case GLib.LogLevelFlags.LEVEL_WARNING:
      return colors.fg.yellow;
    case GLib.LogLevelFlags.LEVEL_MESSAGE:
      return colors.fg.blue;
    case GLib.LogLevelFlags.LEVEL_INFO:
      return colors.fg.green;
    case GLib.LogLevelFlags.LEVEL_DEBUG:
      return colors.fg.white;
    default:
      return colors.fg.magenta;
  }
};

const bisectLeft = <T, U>(arr: T[], value: U, cmp: (a: T) => U, low = 0, high: number = arr.length): T => {
  if (low >= high) return arr[low];
  const mid = (low + high) >> 1;
  if (cmp(arr[mid]) < value) return bisectLeft(arr, value, cmp, mid + 1, high);
  return bisectLeft(arr, value, cmp, low, mid);
};

const program = Effect.Do.pipe(
  // https://stackoverflow.com/questions/44815538/how-to-get-process-pid-in-gjs
  Effect.bind('getPid', () => {
    const credentials = new Gio.Credentials();
    return Effect.succeed(credentials.get_unix_pid.bind(credentials));
  }),
  Effect.bind('sourceMapLookup', () =>
    Effect.flatMap(Fs.FileSystem, (fs) => fs.readFile('./dist/test/test.gjs.js.map')).pipe(
      Effect.map((bytes) => JSON.parse(new TextDecoder('utf-8').decode(bytes)) as RawSourceMap),
      Effect.map((sourceMap) => {
        const state = [0, 0, 0, 0, 0] as VlqState;
        const mappings: SegmentInfo[][] = sourceMap.mappings.split(';').map((segments) => {
          state[0] = 0;
          return segments.split(',').map((segment) => {
            const stateUpdate = vlq.decode(segment) as [number, number, number, number, number | undefined];
            const updatedState = state.map((value, i) => value + (stateUpdate[i] ?? 0)) as VlqState;
            return {
              columnIndex: updatedState[0],
              source: sourceMap.sources[updatedState[1]],
              line: updatedState[2] + 1,
              column: updatedState[3],
              name: stateUpdate[4] ? sourceMap.names[updatedState[4]] : undefined,
            };
          });
        });
        const sourceMapLookup = (line: number, column: number) => {
          if (mappings[line - 1][0].columnIndex > column - 1) return undefined;
          const info = bisectLeft(mappings[line - 1], column - 1, (a) => a.columnIndex);
          return info;
        };
        return sourceMapLookup;
      }),
    ),
  ),
  Effect.tap(({ getPid, sourceMapLookup }) => {
    const decoder = new TextDecoder('utf-8');
    // TODO: GLib.log_writer_supports_color
    (
      GLib.log_set_writer_func as (
        logFunc: (
          logLevel: GLib.LogLevelFlags,
          fields: {
            MESSAGE: Uint8Array;
            PRIORITY: Uint8Array;
            /* eslint-disable-next-line @typescript-eslint/naming-convention */
            GLIB_DOMAIN: Uint8Array;
            PID: Uint8Array;
            /* eslint-disable-next-line @typescript-eslint/naming-convention */
            CODE_FILE: Uint8Array;
            /* eslint-disable-next-line @typescript-eslint/naming-convention */
            CODE_LINE: Uint8Array;
          },
        ) => GLib.LogWriterOutput,
      ) => void
    )((_logLevel, fields) => {
      console.log('here');
      const { print } = globalThis;
      globalThis.print = (...args: unknown[]) => {
        print(
          '11',
          ...args.map((arg) =>
            typeof arg === 'string'
              ? decoder.decode(fields.MESSAGE).replace(/^.*<@file:\/\/.*:(\d+):(\d+)$/gm, (match, line, column) => {
                  const info = sourceMapLookup(Number(line), Number(column));
                  if (info)
                    return `${colors.bright} ${info.name ?? ''}<@file://${info.source}:${info.line}:${info.column}${colors.reset}`;
                  return match;
                })
              : arg,
          ),
        );
      };
      const message = decoder.decode(fields.MESSAGE);
      // .replace(/^.*<@file:\/\/.*:(\d+):(\d+)$/gm, (match, line, column) => {
      //   const info = sourceMapLookup(Number(line), Number(column));
      //   if (info)
      //     return `${colors.bright} ${info.name ?? ''}<@file://${info.source}:${info.line}:${info.column}${colors.reset}`;
      //   return match;
      // });
      const priority = Number(decoder.decode(fields.PRIORITY));
      const domain = decoder.decode(fields.GLIB_DOMAIN);
      // const codeFile = decoder.decode(fields.CODE_FILE);
      // const line = Number(decoder.decode(fields.CODE_LINE));
      print(`${getPid()} ${logLevelToColor(priority)}${logLevelToString(priority)}${colors.reset}`, domain, message);
      return GLib.LogWriterOutput.HANDLED;
    });
  }),
);

const loop = new GLib.MainLoop(null, false);

const z = await Effect.runPromise(program.pipe(Effect.provide(Fs.layer))).then(console.log);

print('hi');
loop.run();

// eslint-disable-next-line import/first
import FileSystemTest from './test/FileSystem.test.js';

await run({ FileSystemTest });
