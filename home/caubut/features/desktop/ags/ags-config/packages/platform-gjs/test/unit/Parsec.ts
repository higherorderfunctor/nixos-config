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

export const apply = <A, B>(p: Parser<(a: A) => B>, q: Parser<A>): Parser<B> =>
  flow(
    p,
    Effect.flatMap(([f, o]) =>
      Option.map(o, (s) => Effect.map(q(s), ([a, r]): [B, Option.Option<string>] => [f(a), r])).pipe(
        Option.getOrElse(() => Effect.fail(makeError('InsufficientInputError', ''))),
      ),
    ),
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

export const space = char(' ');
export const tab = char('\t');

// # -- | One or more.
// # some :: f a -> f [a]
// # some v = some_v
// #   where
// #     many_v = some_v <|> pure []
// #     some_v = (:) <$> v <*> many_v
// def some(v: Parser[A]) -> Parser[Sequence[A]]:
//     def many_v(s: Text) -> Sequence[Tuple[Sequence[A], Text]]:
//         return option(some_v, ret([]))(s)
//     def some_v(s: Text) -> Sequence[Tuple[Sequence[A], Text]]:
//         return ap(fmap(lambda x: lambda y: [x, *y], v), many_v)(s)
//     return some_v

// const some: <A>(v: Parser<A>) => Parser<A[]> = (v) => (source) => {
