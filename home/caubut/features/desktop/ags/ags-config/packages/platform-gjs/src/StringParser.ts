/* eslint-disable @typescript-eslint/ban-types */

import type { Data, Effect, Types } from 'effect';

import * as internal from './internal/stringParser.js';

export type Sequence<A> = {
  [_: number]: A;
  slice: (start: number, end?: number) => Sequence<A>;
  length: number;
};

// export type ParseState<I, A = never> = A extends never
//   ? {
//       input: Sequence<I>;
//       index: number;
//     }
//   : {
//       input: Sequence<I>;
//       index: number;
//       result: A;
//     };
export type ParseState<I, A = never> = {
  input: Sequence<I>;
  index: number;
  result: A;
};

export type Z = ParseState<string>;
export type ZZ = ParseState<string, number>;

export type ParseError<I> = Data.TaggedEnum<{
  IncompleteParseError: { input: Sequence<I> };
  MatchError: { input: Sequence<I> };
  ZeroError: {};
}>;

export type IncompleteParseError<I> = Types.ExtractTag<ParseError<I>, 'IncompleteParseError'>;
export type MatchError<I> = Types.ExtractTag<ParseError<I>, 'MatchError'>;
export type ZeroError = Types.ExtractTag<ParseError<never>, 'ZeroError'>;

export const { IncompleteParseError, MatchError, ZeroError } = internal;

export type ParseResult<I, O, E extends ParseError<I> = never> = Effect.Effect<ParseState<I, O>, E>;

export type Parser<I, A, O = A, E extends ParseError<I> = never> = (state: ParseState<I, A>) => ParseResult<I, O, E>;

export const { parse } = internal;

export const { flatMap } = internal;
