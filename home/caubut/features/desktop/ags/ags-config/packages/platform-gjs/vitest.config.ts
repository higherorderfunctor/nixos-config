import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import { FileSystem } from '@effect/platform-gjs';
import { Effect, identity, ReadonlyArray } from 'effect';
import type { RawSourceMap } from 'source-map';
import * as vlq from 'vlq';

const logLevelToString = (logLevel) => {
  switch (logLevel) {
    case GLib.LogLevelFlags.LEVEL_ERROR:
      return 'ERROR';
    case GLib.LogLevelFlags.LEVEL_CRITICAL:
      return 'CRITICAL';
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

const decoder = new TextDecoder('utf-8');

const loop = new GLib.MainLoop(null, false);

type VlqState = [number, number, number, number, number];

type LookupInfo = {
  columnIndex: number;
  source: string;
  line: number;
  column: number;
  name?: string | undefined;
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
  Effect.bind('sourceMap', () =>
    Effect.flatMap(FileSystem.FileSystem, (fs) => fs.readFile('./dist/test/test.gjs.js.map')).pipe(
      Effect.map((bytes) => JSON.parse(decoder.decode(bytes)) as RawSourceMap),
      Effect.map((sourceMap) => {
        const state = [0, 0, 0, 0, 0] as VlqState;
        const mappings: LookupInfo[][] = sourceMap.mappings.split(';').map((segments) => {
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
        // const filePath = GLib.build_filenamev([GLib.get_home_dir(), 'myObject.json']);
        // const file = Gio.File.new_for_path(filePath);
        // const encoder = new TextEncoder();
        // file.replace_contents(
        //   encoder.encode(JSON.stringify(mappings, null, 2)),
        //   null, // No etag
        //   false, // Do not make backup
        //   Gio.FileCreateFlags.REPLACE_DESTINATION,
        //   null, // No cancellable operation
        // );
        const lookup = (line: number, column: number): LookupInfo | undefined => {
          // print('Original:', line, column);
          if (mappings[line - 1][0].columnIndex > column - 1) {
            // print('Not Found');
            return undefined;
          }
          const info = bisectLeft(mappings[line - 1], column - 1, (a) => a.columnIndex);
          // print('Mapped:', info.columnIndex, info.source, info.line, info.column, info.name ?? '');
          return info;
        };
        return lookup;
      }),
    ),
  ),
  Effect.tap(({ getPid, sourceMap }) => {
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
    )((_logLlevel, fields) => {
      const message = decoder
        .decode(fields.MESSAGE)
        .replace(/(?<=@file:\/\/)(.*):(\d+):(\d+)$/gm, (match, path, line, column) => {
          // print(path, line, column);
          const zz = sourceMap(Number(line), Number(column));
          if (zz) return `${zz.source}:${zz.line}:${zz.column}`;
          return `${path}:${line}:${column}`;
        });
      const priority = Number(decoder.decode(fields.PRIORITY));
      const domain = decoder.decode(fields.GLIB_DOMAIN);
      const codeFile = decoder.decode(fields.CODE_FILE);
      const line = Number(decoder.decode(fields.CODE_LINE));
      // const v = sourceMap(line, columnn);
      // SourceMapConsumer.with(sourceMap, null, (consumer) => {
      //   consumer.originalPositionFor({
      //     line,
      //     // column,
      //   });
      // });
      const reset = '\x1b[0m';
      const red = '\x1b[31m';
      print(getPid(), `${red}${logLevelToString(priority)}${reset}`, domain, codeFile, line, message, '<<');
      return GLib.LogWriterOutput.HANDLED;
    });
  }),
  Effect.bind('defineConfig', () =>
    Effect.tryPromise({
      try: () => import('vitest/config').then(({ defineConfig }) => defineConfig),
      catch: (error) => error,
    }),
  ),
  Effect.tapError((error) => {
    console.error(error);
    return Effect.unit;
  }),
  // Effect.catchAll(() => Effect.unit),
  // (v) => v,
  // Effect.tapDefect((error) => {
  //   console.error('##**', error);
  //   return Effect.unit;
  // }),
  // Effect.bind('startVitest', () => Effect.promise(() => import('vitest/node').then(({ startVitest }) => startVitest))),
  //   const vitestConfig = defineConfig({
  //     test: {
  //       // environment: './vitest.gjs-env.ts',
  //       // runner: './vitest.gjs-runner.ts',
  //       includeSource: ['tests/**/*.test.ts'],
  //     },
  //   });
  //   return Effect.tryPromise({
  //     try: () => startVitest('test', undefined, undefined, vitestConfig).then((vitest) => vitest?.close()),
  //     catch: (error) => error,
  //   }).pipe(
  //     Effect.catchAllDefect((error) => {
  //       print('!!', error);
  //       return Effect.succeed(error);
  //     }),
  //   );
  //   // .catch((error) => {
  //   //   print('here');
  //   //   try {
  //   //     print('there');
  //   //     console.info('!!', sourceMap.length);
  //   //   } catch (error) {
  //   //     console.error(error);
  //   //   }
  //   //   // (gjs:886869): Gjs-CRITICAL **: 08:24:44.235: JS ERROR: ReferenceError: string is not defined
  //   //   // 4 Gjs-Console !! ReferenceError: string is not defined

  //   //   console.error('!!', error);
  //   // });
  // }),
).pipe(Effect.provide(FileSystem.layer));

Effect.runPromise(program)
  // .catch((error) => {
  //   console.error(error);
  // })
  .finally(() => {
    GLib.timeout_add_seconds(GLib.PRIORITY_DEFAULT, 0, () => {
      loop.quit();
      return GLib.SOURCE_REMOVE;
    });
  });

// const sourceMap = Effect.runPromise(
//   Effect.gen(function* (_) {
//     const fs = yield* _(FileSystem.FileSystem);
//     yield* _(fs.readFile('./dist/test/test.gjs.js.map')); // .pipe(Effect.map(decoder.decode.bind(decoder))));
//   }).pipe(Effect.provide(FileSystem.layer)),
// ).pipe(
//   Effect.map((sourceMap) => {
//     (
//       GLib.log_set_writer_func as (
//         logFunc: (
//           logLevel: GLib.LogLevelFlags,
//           fields: {
//             MESSAGE: Uint8Array;
//             PRIORITY: Uint8Array;
//             /* eslint-disable-next-line @typescript-eslint/naming-convention */
//             GLIB_DOMAIN: Uint8Array;
//             PID: Uint8Array;
//             /* eslint-disable-next-line @typescript-eslint/naming-convention */
//             CODE_FILE: Uint8Array;
//             /* eslint-disable-next-line @typescript-eslint/naming-convention */
//             CODE_LINE: Uint8Array;
//           },
//         ) => GLib.LogWriterOutput,
//       ) => void
//     )((_logLlevel, fields) => {
//       const message = decoder.decode(fields.MESSAGE);
//       // .replace(/(?<=@file:)(.*):(\d+):(\d+)/, (match, path, line, column) => path);
//       const priority = Number(decoder.decode(fields.PRIORITY));
//       const domain = decoder.decode(fields.GLIB_DOMAIN);
//       const codeFile = decoder.decode(fields.CODE_FILE);
//       const codeLine = Number(decoder.decode(fields.CODE_LINE));
//       // SourceMapConsumer.with(sourceMap, null, (consumer) => {});
//
//       print(credentials.get_unix_pid(), logLevelToString(priority), domain, codeFile, codeLine, message);
//       return GLib.LogWriterOutput.HANDLED;
//     });
//   }),
// );
// print('here', sourceMap.length);

// hard cast as the typedefs are not correct

// import('vitest/config')
//   .then(({ defineConfig }) => import('vitest/node').then(({ startVitest }) => ({ defineConfig, startVitest })))
//   .then(({ defineConfig, startVitest }) => {
//     const vitestConfig = defineConfig({
//       test: {
//         // environment: './vitest.gjs-env.ts',
//         // runner: './vitest.gjs-runner.ts',
//         includeSource: ['tests/**/*.test.ts'],
//       },
//     });
//     return startVitest('test', undefined, undefined, vitestConfig);
//   })
//   .then((vitest) => vitest?.close())
//   .catch((error) => {
//     print('here');
//     try {
//       print('there');
//       console.info('!!', sourceMap.length);
//     } catch (error) {
//       console.error(error);
//     }
//     // (gjs:886869): Gjs-CRITICAL **: 08:24:44.235: JS ERROR: ReferenceError: string is not defined
//     // 4 Gjs-Console !! ReferenceError: string is not defined
//
//     console.error('!!', error);
//   });
// .finally(() => {
//   loop.quit();
// });

loop.run();

// TODO text decoder instead of fromCharCode
