import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import { FileSystem } from '@effect/platform-gjs';
import { Effect } from 'effect';
import type { RawSourceMap } from 'source-map';
import { SourceMapConsumer } from 'source-map';
import * as vlq from 'vlq';

// const decodeVLQ = (encoded: string) => {
//   const BASE64_DIGITS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/';
//   const VLQ_BASE_SHIFT = 5;
//   const VLQ_BASE = 1 << VLQ_BASE_SHIFT;
//   const VLQ_BASE_MASK = VLQ_BASE - 1;
//   const VLQ_CONTINUATION_BIT = VLQ_BASE;
//
//   const values = [];
//   let currentIndex = 0;
//
//   while (currentIndex < encoded.length) {
//     let value = 0;
//     let shift = 0;
//     let continuation;
//     let digit;
//
//     do {
//       if (currentIndex >= encoded.length) {
//         throw new Error('Invalid VLQ sequence');
//       }
//
//       digit = BASE64_DIGITS.indexOf(encoded.charAt(currentIndex++));
//       if (digit === -1) {
//         throw new Error('Invalid base64 digit');
//       }
//
//       continuation = !!(digit & VLQ_CONTINUATION_BIT);
//       digit &= VLQ_BASE_MASK;
//       value += digit << shift;
//       shift += VLQ_BASE_SHIFT;
//     } while (continuation);
//
//     // Convert from a two's complement value to a value where the sign bit is
//     // placed in the least significant bit. For example, as decimals:
//     // 1 becomes 2 (10 binary), -1 becomes 3 (11 binary)
//     // 2 becomes 4 (100 binary), -2 becomes 5 (101 binary)
//     const shouldNegate = value & 1;
//     value >>= 1;
//     if (shouldNegate) {
//       value = -value;
//     }
//
//     values.push(value);
//   }
//
//   return values;
// };
//
// const findOriginalPositionAndFile = (sourceMap: RawSourceMap, generatedLine: number, generatedColumn: number) => {
//   // Assuming sourceMap is already the parsed JSON object of the source map
//   const { mappings } = sourceMap;
//   const { sources } = sourceMap;
//
//   // Split the mappings into lines
//   const lines = mappings.split(';');
//
//   print(lines.length);
//
//   // Find the closest line
//   if (generatedLine >= lines.length) {
//     throw new Error('Line out of range');
//   }
//
//   const lineMappings = lines[generatedLine];
//
//   // Decode the VLQ encoded mappings for the requested line (simplified, real decoding is more complex)
//   // This is a very simplified parser and does not fully implement VLQ decoding
//   const segments = lineMappings.split(',').map(decodeVLQ);
//
//   // Initialize variables to store the closest match
//   let closestSegment = null;
//   let closestDistance = Number.MAX_VALUE;
//
//   for (const segment of segments) {
//     // A segment is [generatedColumn, sourceIndex, sourceLine, sourceColumn, nameIndex]
//     // For simplicity, we're assuming segments are already decoded by decodeVLQ
//     if (segment.length < 4) continue; // Incomplete segment
//
//     const [segmentGeneratedColumn, , segmentSourceLine, segmentSourceColumn] = segment;
//
//     // Find the segment with the closest column number to the generatedColumn
//     const distance = Math.abs(generatedColumn - segmentGeneratedColumn);
//     if (distance < closestDistance) {
//       closestDistance = distance;
//       closestSegment = segment;
//     }
//   }
//
//   if (!closestSegment) {
//     throw new Error('No matching segment found');
//   }
//
//   // Extract the original position information
//   const [, sourceIndex, sourceLine, sourceColumn] = closestSegment;
//   const originalFile = sourceMap.sources[sourceIndex];
//
//   return {
//     file: originalFile,
//     line: sourceLine,
//     column: sourceColumn,
//   };
// };

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
  source: string;
  line: number;
  column: number;
  name: string;
};

// const formatSegment = (col, source, sourceLine, sourceCol, name, sources, names) =>
//   `${col + 1} => ${sources[source]} ${sourceLine + 1}:${sourceCol + 1}${names[name] ? ` ${names[name]}` : ``}`

const formatLine = (line: string, state: VlqState, sources: string[], names: string[]) => {
  const acc: Record<number, LookupInfo> = {};
  const segs = line.split(',');
  return segs.map((seg) => {
    if (!seg)
      return {
        source: '!!',
        line: 0,
        column: 0,
        name: '',
      };
    const [columnIndex, source, line, column, name] = vlq.decode(seg) as VlqState;
    acc[columnIndex] = { source: sources[source], line, column, name: names[name] };
    // for (let i = 0; i < 5; i++) {
    //   state[i] = typeof decoded[i] === 'number' ? state[i] + decoded[i] : state[i];
    // }
    // return formatSegment(...state.concat([sources, names]));
    return {
      source: sources[state[1]],
      line: state[2] + 1,
      column: state[3] + 1,
      name: names[state[4]],
    };
  });
};

let sourceFileIndex = 0; // second field
let sourceCodeLine = 0; // third field
let sourceCodeColumn = 0; // fourth field
let nameIndex = 0; // fifth field

export const decodeLine = (line: string, decoded: VlqState) => {
  let generatedCodeColumn = 0; // first field - reset each time

  return line.map((segment) => {
    generatedCodeColumn += segment[0];

    const result = [generatedCodeColumn];

    if (segment.length === 1) {
      // only one field!
      return result;
    }

    sourceFileIndex += segment[1];
    sourceCodeLine += segment[2];
    sourceCodeColumn += segment[3];

    result.push(sourceFileIndex, sourceCodeLine, sourceCodeColumn);

    if (segment.length === 5) {
      nameIndex += segment[4];
      result.push(nameIndex);
    }

    return result;
  });
};

const formatMappings = (mappings: string, sources: string[], names: string[]) => {
  const vlqState: VlqState = [0, 0, 0, 0, 0];
  return mappings.split(';').map((line) => {
    const formattedLine = formatLine(line, vlqState, sources, names);
    vlqState[0] = 0;
    return formattedLine;
  });
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
        let mappings = formatMappings(sourceMap.mappings, sourceMap.sources, sourceMap.names);
        mappings = sourceMap.mappings.split(';').map((line) => line.split(',').map(() => ({})));
        // const lines = sourceMap.mappings.split(';');
        // const lc = lines.map((line) => line.split(','));
        print(mappings.length);
        const lookup = (
          line: number,
          column: number,
        ):
          | {
              source: string;
              line: number;
              column: number;
              name: string;
            }
          | undefined => {
          print(
            line,
            column,
            mappings[line - 1].length,
            mappings[line].length,
            mappings[line + 1].length,
            mappings[line][column]?.source,
            mappings[line][column]?.line,
            mappings[line][column]?.column,
            mappings[line][column]?.name,
          );
          return mappings[line - 1][column - 1];
        };
        return lookup;
      }),
      // Effect.flatMap((bytes) =>
      //   Effect.try({
      //     try: () => {
      //       const sourceMap = JSON.parse(decoder.decode(bytes)) as RawSourceMap;
      //       return (line: number, column: number) => findOriginalPositionAndFile(sourceMap, line, column);
      //     },
      //     catch: (error) => {
      //       print('111', error);
      //       return error;
      //     },
      //   }),
      // ),
      // Effect.tapBoth({
      //   onFailure: (error) =>
      //     Effect.sync(() => {
      //       print('E', error);
      //     }),
      //   onSuccess: (error) =>
      //     Effect.sync(() => {
      //       print('S', error);
      //     }),
      // }),
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
          try {
            print(path, line, column);
            const zz = sourceMap(Number(line), Number(column));
            if (zz) return `@@@${zz.source}:${zz.line}:${zz.column}@@@`;
          } catch (error) {
            console.error(error);
          }
          return `!${path}:${line}:${column}`;
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
      print('!!', getPid(), logLevelToString(priority), domain, codeFile, line, message, '<<');
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
    console.error('##', error);
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
