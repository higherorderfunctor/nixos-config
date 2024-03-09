import { FileSystem } from '@effect/platform';
import { Context, Effect, Layer, Option } from 'effect';
import * as vlq from 'vlq';

type VlqState = [number, number, number, number, number];

export type RawSourceMap = {
  version: number;
  sources: string[];
  names: string[];
  sourceRoot?: string;
  sourcesContent?: string[];
  mappings: string;
  file: string;
};

export type SegmentInfo = {
  columnIndex: number;
  symbol: Option.Option<string>;
  source: string;
  line: number;
  column: number;
};

export const bisectLeft = <T, U>(arr: T[], value: U, cmp: (a: T) => U, low = 0, high: number = arr.length): T => {
  if (low >= high) return arr[low];
  const mid = (low + high) >> 1;
  if (cmp(arr[mid]) < value) return bisectLeft(arr, value, cmp, mid + 1, high);
  return bisectLeft(arr, value, cmp, low, mid);
};

export class SourceMap extends Context.Tag('SourceMap')<
  // eslint-disable-next-line no-use-before-define
  SourceMap,
  {
    readonly lookup: (line: number, column: number) => Option.Option<SegmentInfo>;
  }
>() {}

export const layer = Layer.effect(
  SourceMap,
  Effect.gen(function* (_) {
    const fs = yield* _(FileSystem.FileSystem);

    const lookup = yield* _(
      fs.readFile(`./dist/test/test.${process.env.NODE_RUNTIME}.js.map`).pipe(
        Effect.map((bytes) => JSON.parse(new TextDecoder('utf-8').decode(bytes)) as RawSourceMap),
        // Effect.flatMap((sourceMap) =>
        //   Effect.gen(function* () {
        Effect.map((sourceMap) => {
          const state = [0, 0, 0, 0, 0] as VlqState;
          const mappings: SegmentInfo[][] = sourceMap.mappings.split(';').map((segments) => {
            state[0] = 0;
            return segments.split(',').map((segment) => {
              // eslint-disable-next-line @typescript-eslint/no-unsafe-call, @typescript-eslint/no-unsafe-member-access
              const stateUpdate = vlq.decode(segment) as [number, number, number, number, number | undefined];
              state.forEach((value, i) => {
                state[i] = value + (stateUpdate[i] ?? 0);
              });
              return {
                columnIndex: state[0],
                symbol: state[4] ? Option.fromNullable(sourceMap.names[state[4]]) : Option.none(),
                source: sourceMap.sources[state[1]],
                line: state[2] + 1,
                column: state[3],
              };
            });
          });
          // yield* _(fs.writeFileString('sourceMap.json', JSON.stringify(mappings, null, 2)));
          return (line: number, column: number) => {
            if (mappings[line - 1][0].columnIndex > column - 1) return Option.none();
            const info = bisectLeft(mappings[line - 1], column - 1, (a) => a.columnIndex);
            return Option.some({ ...info, query: [line, column] });
          };
        }),
        // ),
      ),
    );

    return SourceMap.of({
      lookup,
    });
  }),
);
