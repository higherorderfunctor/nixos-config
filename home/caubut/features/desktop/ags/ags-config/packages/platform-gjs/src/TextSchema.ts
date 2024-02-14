import { ParseResult } from '@effect/schema';
import type { ParseOptions } from '@effect/schema/AST';
import * as S from '@effect/schema/Schema';
import { Effect, Option } from 'effect';
import * as F from 'effect/Function';

export type TextSchema<A, R = never> = S.Schema<[string, number, A], string, R>;

export const decode: <A, R>(
  schema: TextSchema<A, R>,
  options?: ParseOptions,
) => {
  (overrideOptions?: ParseOptions | undefined): (self: string) => Effect.Effect<A, ParseResult.ParseError, R>;
  (i: string, overrideOptions?: ParseOptions | undefined): Effect.Effect<A, ParseResult.ParseError, R>;
} = (schema, options) =>
  F.dual(2, (i: string, overrideOptions?: ParseOptions | undefined) =>
    S.decode(schema, options)(i, overrideOptions).pipe(
      Effect.flatMap(([inp, i, a]) =>
        inp.length === i ? Effect.succeed(a) : Effect.fail(ParseResult.index(i, ParseResult.unexpected(schema.ast))),
      ),
    ),
  );

export const string: (s: string) => TextSchema<string> =
  (s) =>
  <A>(source, i = 0, a: A) =>
    S.startsWith(s.)
      ? Effect.succeed([s, isEmpty(source.slice(s.length))])
      : Effect.fail(makeError('InsufficientInputError', source));

type Char<S extends string> = S extends `${infer C}${infer _R}` ? C : S extends '' ? never : S;

export const char: <C extends string>(c: Char<C>) => Parser<string> = string;

export const space = char(' ');
export const tab = char('\t');
