import * as Ansi from '@effect/printer-ansi/Ansi';
import * as Doc from '@effect/printer-ansi/AnsiDoc';
import { Effect, Option } from 'effect';

import * as SourceMap from './SourceMap.js';
import type * as Stacktrace from './StacktraceResolver.js';

const formatErrorType = (stacktrace: Stacktrace.Stacktrace) => Doc.text(stacktrace.error).pipe(Doc.annotate(Ansi.red));

const formatMessage = (stacktrace: Stacktrace.Stacktrace) =>
  stacktrace.message.pipe(Option.map((message) => Doc.text(message).pipe(Doc.annotate(Ansi.white))));

const formatHeader = (stacktrace: Stacktrace.Stacktrace) =>
  formatErrorType(stacktrace).pipe(
    Doc.cat(
      Option.getOrElse(
        formatMessage(stacktrace).pipe(Option.map((message) => Doc.cat(Doc.text(': '), message))),
        () => Doc.empty,
      ),
    ),
  );

const formatSource = (source: string, position: Option.Option<{ line: number; column: number }> = Option.none()) =>
  Effect.gen(function* (_) {
    const sourceMap = yield* _(SourceMap.SourceMap);
    const frame = position.pipe(
      Option.flatMap((position) => sourceMap.lookup(position.line, position.column)),
      Option.getOrUndefined,
    );
    console.log(frame);
    return position.pipe(
      Option.map((position) =>
        Doc.annotate(Doc.text(frame?.source ?? source), frame !== undefined ? Ansi.green : Ansi.yellow).pipe(
          Doc.cat(Doc.colon),
          Doc.cat(Doc.annotate(Doc.text(String(frame?.line ?? position.line)), Ansi.blue)),
          Doc.cat(Doc.colon),
          Doc.cat(Doc.annotate(Doc.text(String(frame?.column ?? position.column)), Ansi.blue)),
        ),
      ),
      Option.getOrElse(() => Doc.annotate(Doc.text(source), Ansi.yellow)),
    );
  });

// TODO: narrow on frame or position
const formatSymbol = (frame: Stacktrace.StackFrame) =>
  Effect.gen(function* (_) {
    const sourceMap = yield* _(SourceMap.SourceMap);
    if (typeof frame === 'string') return Option.none();
    if (Option.isNone(frame.symbol)) return Option.none();
    const symbol = Option.getOrThrow(frame.symbol);
    const frameInfo = frame.location.pipe(
      Option.flatMap((location) => sourceMap.lookup(location.line, location.column)),
    );
    return frameInfo.pipe(
      Option.flatMap(({ symbol }) => Option.map(symbol, (symbol) => Doc.annotate(Doc.text(symbol), Ansi.cyan))),
      Option.orElse(() => Option.some(Doc.annotate(Doc.text(symbol), Ansi.yellow))),
    );
  });

const formatFrameWithSymbol = (symbol: Doc.Doc<Ansi.Ansi>, source: Doc.Doc<Ansi.Ansi>) =>
  Doc.empty.pipe(Doc.cat(symbol), Doc.cat(Doc.text(' ')), Doc.cat(Doc.parenthesized(source)));

const formatFrame = (frame: Stacktrace.StackFrame) =>
  Effect.gen(function* (_) {
    if (typeof frame === 'string') return Doc.annotate(Doc.text(frame.trimStart()), Ansi.red);
    if (Option.isNone(frame.symbol)) return yield* _(formatSource(frame.source, frame.location));
    const symbol = yield* _(formatSymbol(frame));
    return formatFrameWithSymbol(
      // TODO: clean this all up, take care with symbol
      Option.getOrThrow(symbol),
      yield* _(formatSource(frame.source, frame.location)),
    );
  });

export const format = (stacktrace: Stacktrace.Stacktrace) =>
  Effect.gen(function* (_) {
    const frames = yield* _(
      Effect.all(
        stacktrace.stack.map((frame) =>
          formatFrame(frame).pipe(
            Effect.map((doc) => Doc.cat(Doc.indent(Doc.text('󰘍 ').pipe(Doc.annotate(Ansi.blue)), 2), doc)),
          ),
        ),
      ),
    );

    return Doc.vsep([formatHeader(stacktrace), ...frames]).pipe(
      Doc.annotate(Ansi.blackBright),
      Doc.render({ style: 'pretty' }),
    );
  });
