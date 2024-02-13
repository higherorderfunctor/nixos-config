import { Effect, flow, Option, pipe } from 'effect';

export type ExtraInputError = {
  readonly _tag: 'ExtraInputError';
  readonly extraInput: string;
};

export type InsufficientInputError = {
  readonly _tag: 'InsufficientInputError';
  readonly rest: string;
};

export type ParseError = ExtraInputError | InsufficientInputError;

export type MakeError = {
  (_tag: 'ExtraInputError', extra: string): ExtraInputError;
  (_tag: 'InsufficientInputError', rest: string): InsufficientInputError;
};

export const makeError: MakeError = <A>(_tag: ParseError['_tag'], ...rest: any[]) => ({ _tag, ...rest });

export type Parser<A> = (source: string) => Effect.Effect<[A, Option.Option<string>], ParseError>;

export const parse: <A>(parser: Parser<A>) => (source: string) => Effect.Effect<A, ParseError> = (parser) =>
  flow(
    parser,
    Effect.map(([a]) => a),
  );

export const parseAll: <A>(parser: Parser<A>) => (source: string) => Effect.Effect<A, ParseError> = (parser) =>
  flow(
    parser,
    Effect.flatMap(([a, extra]) =>
      extra.pipe(
        Option.map((extra) => Effect.fail(makeError('ExtraInputError', extra))),
        Option.getOrElse(() => Effect.succeed(a)),
      ),
    ),
  );

export const map: <A, B>(p: Parser<A>, f: (a: A) => B) => Parser<B> = (parser, f) =>
  flow(
    parser,
    Effect.map(([a, s]) => [f(a), s]),
  );

export const flatMap: <A, B>(p: Parser<A>, f: (a: A) => Parser<B>) => Parser<B> = (parser, f) =>
  flow(
    parser,
    Effect.flatMap(([a, s]) =>
      s.pipe(
        Option.map(f(a)),
        Option.getOrElse(() =>
          Effect.fail(
            makeError(
              'InsufficientInputError',
              Option.getOrElse(s, () => ''),
            ),
          ),
        ),
      ),
    ),
  );

export const isEmpty: (source: string) => Option.Option<string> = (source) =>
  source === '' ? Option.none() : Option.some(source);

export const string: (s: string) => Parser<string> = (s) => (source) =>
  source.startsWith(s)
    ? Effect.succeed([s, isEmpty(source.slice(s.length))])
    : Effect.fail(makeError('InsufficientInputError', source));

type Char<S extends string> = S extends `${infer C}${infer _R}` ? C : S extends '' ? never : S;

export const char: <C extends string>(c: Char<C>) => Parser<string> = string;
