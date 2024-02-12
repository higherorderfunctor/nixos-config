import { Option } from 'effect';

export type StackFrame =
  | string
  | {
      symbol: Option.Option<string>;
      source: string;
      location: Option.Option<{
        line: number;
        column: number;
      }>;
    };

export type Stacktrace = {
  error: string;
  message: Option.Option<string>;
  stack: StackFrame[];
};

export const from = (error: Error): Option.Option<Stacktrace> =>
  Option.fromNullable(error.stack).pipe(
    Option.map((stack) => {
      const [head, ...rest] = stack.split('\n');
      const [type, message] = head.split(':', 2) as [string, string | undefined];
      return {
        error: type,
        message: Option.fromNullable(message?.trim()),
        stack: rest.map((text): StackFrame => {
          const matched = text.match(
            /^\s*at (?:(?<symbol>\S+(?: \[as .*\])?) )?\(?(?:(?<source1><.*>)|file:\/\/(?<source2>.+):(?<line>\d+):(?<column>\d+))\)?$/,
          );
          if (!matched?.groups) return text;
          // TODO: schema
          const frame = matched.groups as unknown as
            | { symbol?: string | undefined; source1: string; source2: undefined; line: undefined; column: undefined }
            | { symbol?: string | undefined; source1: undefined; source2: string; line: string; column: string };
          return {
            symbol: Option.fromNullable(frame.symbol),
            source: frame.source1 ?? frame.source2,
            location:
              frame.line !== undefined
                ? Option.some({ line: Number.parseInt(frame.line, 10), column: Number.parseInt(frame.column, 10) })
                : Option.none(),
          };
        }),
      };
    }),
  );
