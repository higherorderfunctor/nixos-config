import { Effect, Option, Types } from 'effect';

export type ExtraInputError<A> = {
  readonly _tag: 'ExtraInputError';
  readonly parsed: A;
  readonly extra: string;
};

export type InsufficientInputError<A> = {
  readonly _tag: 'InsufficientInputError';
  readonly parsed: A;
  readonly rest: string;
};

export type ParseError<A> = ExtraInputError<A> | InsufficientInputError<A>;

export type MakeError<A = any> = {
  (_tag: 'ExtraInputError', parsed: A, extra: string): ExtraInputError<A>;
  (_tag: 'InsufficientInputError', parsed: A, rest: string): InsufficientInputError<A>;
};

export const makeError: MakeError<A> = <A>(_tag: ParseError<A>['_tag'], ...rest: any[]) => ({ _tag, ...rest });

export type Parser<A> = (source: string) => Effect.Effect<[A, Option.Option<string>], ParseError<A>>;

export const parse =
  <T>(parser: Parser<T>) =>
  (source: string) =>
    parser(source);

export const parseAll =
  <T>(parser: Parser<T>) =>
  (source: string) =>
    parser(source).pipe(
      Effect.flatMap(([a, extra]) =>
        extra.pipe(
          Option.map((extra) => Effect.fail(makeError('ExtraInputError', a, extra))),
          Option.getOrElse(() => Effect.succeed(a)),
        ),
      ),
    );

// # bind :: Parser a -> (a -> Parser b) -> Parser b
// # bind p f = Parser $ \s -> concatMap (\(a, s') -> parse (f a) s') $ parse p s
// def bind(p: Parser[A], f: Callable[[A], Parser[B]]) -> Parser[B]:
//     return lambda s: concat_map(lambda a, _s: f(a)(_s), p(s))

export const flatMap =
  <A, B>(p: Parser<A>, f: (a: A) => Parser<B>): Parser<B> =>
  (s: string) =>
    p(s).pipe(Effect.flatMap(([a, s]) => f(a)(s)));
