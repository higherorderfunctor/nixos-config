/* eslint-disable @typescript-eslint/no-explicit-any */
/* eslint-disable @typescript-eslint/consistent-type-definitions */
import type { Types } from 'effect';
import { Data, Effect, flow, Match, pipe } from 'effect';

import type * as P from '../StringParser.js';

interface ParseErrorDefinition extends Data.TaggedEnum.WithGenerics<1> {
  readonly taggedEnum: P.ParseError<this['A']>;
}

export const { IncompleteParseError, MatchError, ZeroError } = Data.taggedEnum<ParseErrorDefinition>();

const makeState = <I>(input: P.Sequence<I>): P.ParseState<I> =>
  ({
    input,
    index: 0,
  }) as P.ParseState<I>;

export const parse: <I, O, E extends P.ParseError<I> = never>(
  parser: P.Parser<I, never, O, E>,
) => (input: P.Sequence<I>) => Effect.Effect<O, E | Types.ExtractTag<P.ParseError<I>, 'IncompleteParseError'>> = (
  parser,
) =>
  flow(
    makeState,
    parser,
    Effect.flatMap((state) =>
      Match.value(state.index >= state.input.length).pipe(
        Match.when(false, () => Effect.fail(IncompleteParseError({ input: state.input.slice(state.index) }))),
        Match.when(true, () => Effect.succeed(state.result)),
        Match.exhaustive,
      ),
    ),
  );

export const flatMap: <I, B, O, E2 extends P.ParseError<I> = never>(
  f: (value: B) => P.Parser<I, B, O, E2>,
) => <A = never, E1 extends P.ParseError<I> = never>(parser: P.Parser<I, A, B, E1>) => P.Parser<I, A, O, E1 | E2> =
  (f) => (parser) =>
    flow(
      parser,
      Effect.flatMap((state) => f(state.result)(state)),
    );

export const result: <I, O>(value: O) => P.Parser<I, any, O> = (value) => (state) =>
  Effect.succeed({ ...state, value });

export const fail: <E extends P.ParseError<any>>(error: E) => P.Parser<any, any, never, E> = (error) => () =>
  Effect.fail(error);

export const zero: P.Parser<any, any, never, P.ZeroError> = () => Effect.fail(ZeroError());

export const item: <I>(state: P.ParseState<I, any>) => P.ParseResult<I, I, P.ZeroError> = (state) =>
  state.index + 1 <= state.input.length
    ? Effect.succeed({ ...state, index: state.index + 1, value: state.input[state.index] })
    : zero(state);

export const satisfy: <I>(predicate: (input: I) => boolean) => P.Parser<I, any, I, P.MatchError<I> | P.ZeroError> = <I>(
  predicate: (input: I) => boolean,
) =>
  pipe(
    item<I>,
    flatMap((value) => (predicate(value) ? result(value) : fail(MatchError({ input: [value] })))),
  );

// item :: Parser Char
// item = Parser parseItem
//   where
//     parseItem [] = []
//     parseItem (x:xs) = [(x, xs)]
// item :: Parser Char
// item = Parser $ \s ->
//   case s of
//    []     -> []
//    (c:cs) -> [(c,cs)]

// export type Char<S extends string> = S extends `${infer C}${infer _R}` ? C : S extends '' ? never : S;

export const map: <B, O>(
  f: (input: B) => O,
) => <I, A, E extends P.ParseError<I>>(parser: P.Parser<I, A, B, E>) => P.Parser<I, A, O, E> = (f) => (parser) =>
  flow(
    parser,
    Effect.map((state) => ({ ...state, result: f(state.result) })),
  );

export const apply: <I, A, B, O, E1 extends P.ParseError<I>>(
  parser1: P.Parser<I, A, (input: B) => O, E1>,
) => <E2 extends P.ParseError<I>>(parser2: P.Parser<I, any, B, E2>) => P.Parser<I, A, O, E1 | E2> =
  (parser1) => (parser2) =>
    flow(
      parser1,
      Effect.flatMap((state) =>
        pipe(
          parser2(state),
          Effect.map((ss) => ({ ...ss, result: state.result(ss.result) })),
        ),
      ),
    );

// TODO: better name
export const andThen: <I, A, B, E1 extends P.ParseError<I>, E2 extends P.ParseError<I>>(
  parser1: P.Parser<I, A, any, E1>,
) => (parser2: P.Parser<I, any, B, E2>) => P.Parser<I, A, B, E1 | E2> = (parser1) => (parser2) =>
  pipe(
    parser1,
    flatMap(() => parser2),
  );

export const append: <I, A, O extends any[], E1 extends P.ParseError<I>, E2 extends P.ParseError<I>>(
  parser1: P.Parser<I, A, O[], E1>,
) => (parser2: P.Parser<I, any, O, E1 | E2>) => P.Parser<I, A, O[], E1 | E2> = (parser1) => (parser2) =>
  pipe(
    parser1,
    flatMap((result) =>
      pipe(
        parser2,
        map((next) => [...result, next]),
      ),
    ),
  );

export const concat: <I, A, O extends any[], E1 extends P.ParseError<I>, E2 extends P.ParseError<I>>(
  parser1: P.Parser<I, A, O[], E1>,
) => (parser2: P.Parser<I, any, O[], E1 | E2>) => P.Parser<I, A, O[], E1 | E2> = (parser1) => (parser2) =>
  pipe(
    parser1,
    flatMap((result) =>
      pipe(
        parser2,
        map((next) => [...result, ...next]),
      ),
    ),
  );

export const sequence: <I, E extends P.ParseError<I>>(seq: P.Sequence<I>) => P.Parser<I, any, P.Sequence<I>, E> =
flow(item<I>, Effect.map((asdf) => ), Effect.catchTag('ZeroError', () => Effect.succeed({ input: seq, index: 0, result: [] })));
// def string(s: Text) -> Parser[Text]:
//     try:
//         c, cs = s[0], s[1:]
//         return then(then(char(c), string(cs)), ret(c+cs))
//     except IndexError:
//         return ret('')

/// // / export const isEmpty: (source: string) => Option.Option<string> = (source) =>
/// // /  source === '' ? Option.none() : Option.some(source);
/// // /
/// // / export const string: (s: string) => Parser<string> = (s) => (source) =>
/// // /  source.startsWith(s)
/// // /    ? Effect.succeed([s, isEmpty(source.slice(s.length))])
/// // /    : Effect.fail(makeError('InsufficientInputError', source));
/// // /
/// // /
/// // / export const char: <C extends string>(c: Char<C>) => Parser<string> = string;
/// // /
/// // / export const space = char(' ');
/// // / export const tab = char('\t');
/// // /
/// // // / # -- | One or more.
/// // // / # some :: f a -> f [a]
/// // // / # some v = some_v
/// // // / #   where
/// // // / #     many_v = some_v <|> pure []
/// // // / #     some_v = (:) <$> v <*> many_v
/// // // / def some(v: Parser[A]) -> Parser[Sequence[A]]:
/// // // /     def many_v(s: Text) -> Sequence[Tuple[Sequence[A], Text]]:
/// // // /         return option(some_v, ret([]))(s)
/// // // /     def some_v(s: Text) -> Sequence[Tuple[Sequence[A], Text]]:
/// // // /         return ap(fmap(lambda x: lambda y: [x, *y], v), many_v)(s)
/// // // /     return some_v
/// // /
/// // // / const some: <A>(v: Parser<A>) => Parser<A[]> = (v) => (source) => {
/// // /
/// // // /bind :: Parser a -> (a -> Parser b) -> Parser b
/// // // /bind p f = Parser $ \s -> concatMap (\(a, s') -> parse (f a) s') $ parse p s
/// // // /
/// // // /unit :: a -> Parser a
/// // // /unit a = Parser (\s -> [(a,s)])
/// // // /
/// // // /instance Functor Parser where
/// // // /  fmap f (Parser cs) = Parser (\s -> [(f a, b) | (a, b) <- cs s])
/// // // /
/// // // /instance Applicative Parser where
/// // // /  pure = return
/// // // /  (Parser cs1) <*> (Parser cs2) = Parser (\s -> [(f a, s2) | (f, s1) <- cs1 s, (a, s2) <- cs2 s1])
/// // // /
/// // // /instance Monad Parser where
/// // // /  return = unit
/// // // /  (>>=)  = bind
/// // // /
/// // // /instance MonadPlus Parser where
/// // // /  mzero = failure
/// // // /  mplus = combine
/// // // /
/// // // /instance Alternative Parser where
/// // // /  empty = mzero
/// // // /  (<|>) = option
/// // // /
/// // // /combine :: Parser a -> Parser a -> Parser a
/// // // /combine p q = Parser (\s -> parse p s ++ parse q s)
/// // // /
/// // // /failure :: Parser a
/// // // /failure = Parser (\cs -> [])
/// // // /
/// // // /option :: Parser a -> Parser a -> Parser a
/// // // /option  p q = Parser $ \s ->
/// // // /  case parse p s of
/// // // /    []     -> parse q s
/// // // /    res    -> res
/// // // /
/// // // /satisfy :: (Char -> Bool) -> Parser Char
/// // // /satisfy p = item `bind` \c ->
/// // // /  if p c
/// // // /  then unit c
/// // // /  else failure
/// // // /
/// // // /-------------------------------------------------------------------------------
/// // // /-- Combinators
/// // // /-------------------------------------------------------------------------------
/// // // /
/// // // /oneOf :: [Char] -> Parser Char
/// // // /oneOf s = satisfy (flip elem s)
/// // // /
/// // // /chainl :: Parser a -> Parser (a -> a -> a) -> a -> Parser a
/// // // /chainl p op a = (p `chainl1` op) <|> return a
/// // // /
/// // // /chainl1 :: Parser a -> Parser (a -> a -> a) -> Parser a
/// // // /p `chainl1` op = do {a <- p; rest a}
/// // // /  where rest a = (do f <- op
/// // // /                     b <- p
/// // // /                     rest (f a b))
/// // // /                 <|> return a
/// // // /
/// // // /char :: Char -> Parser Char
/// // // /char c = satisfy (c ==)
/// // // /
/// // // /natural :: Parser Integer
/// // // /natural = read <$> some (satisfy isDigit)
/// // // /
/// // // /string :: String -> Parser String
/// // // /string [] = return []
/// // // /string (c:cs) = do { char c; string cs; return (c:cs)}
/// // // /
/// // // /token :: Parser a -> Parser a
/// // // /token p = do { a <- p; spaces ; return a}
/// // // /
/// // // /reserved :: String -> Parser String
/// // // /reserved s = token (string s)
/// // // /
/// // // /spaces :: Parser String
/// // // /spaces = many $ oneOf " \n\r"
/// // // /
/// // // /digit :: Parser Char
/// // // /digit = satisfy isDigit
/// // // /
/// // // /number :: Parser Int
/// // // /number = do
/// // // /  s <- string "-" <|> return []
/// // // /  cs <- some digit
/// // // /  return $ read (s ++ cs)
/// // // /
/// // // /parens :: Parser a -> Parser a
/// // // /parens m = do
/// // // /  reserved "("
/// // // /  n <- m
/// // // /  reserved ")"
/// // // /  return n
/// // // /
/// // // /-------------------------------------------------------------------------------
/// // // /-- Calulator parser
/// // // /-------------------------------------------------------------------------------
/// // // /
/// // // /-- number = [ "-" ] digit { digit }.
/// // // /-- digit = "0" | "1" | ... | "8" | "9".
/// // // /-- expr = term { addop term }.
/// // // /-- term = factor { mulop factor }.
/// // // /-- factor = "(" expr ")" | number.
/// // // /-- addop = "+" | "-".
/// // // /-- mulop = "*".
/// // // /
/// // // /data Expr
/// // // /  = Add Expr Expr
/// // // /  | Mul Expr Expr
/// // // /  | Sub Expr Expr
/// // // /  | Lit Int
/// // // /  deriving Show
/// // // /
/// // // /eval :: Expr -> Int
/// // // /eval ex = case ex of
/// // // /  Add a b -> eval a + eval b
/// // // /  Mul a b -> eval a * eval b
/// // // /  Sub a b -> eval a - eval b
/// // // /  Lit n   -> n
/// // // /
/// // // /int :: Parser Expr
/// // // /int = do
/// // // /  n <- number
/// // // /  return (Lit n)
/// // // /
/// // // /expr :: Parser Expr
/// // // /expr = term `chainl1` addop
/// // // /
/// // // /term :: Parser Expr
/// // // /term = factor `chainl1` mulop
/// // // /
/// // // /factor :: Parser Expr
/// // // /factor =
/// // // /      int
/// // // /  <|> parens expr
/// // // /
/// // // /infixOp :: String -> (a -> a -> a) -> Parser (a -> a -> a)
/// // // /infixOp x f = reserved x >> return f
/// // // /
/// // // /addop :: Parser (Expr -> Expr -> Expr)
/// // // /addop = (infixOp "+" Add) <|> (infixOp "-" Sub)
/// // /
/// // / mulop :: Parser (Expr -> Expr -> Expr)
/// // / mulop = infixOp "*" Mul
/// // /
/// // / run :: String -> Expr
/// // / run = runParser expr
/// // /
/// // / main :: IO ()
/// // / main = forever $ do
/// // /  putStr "> "
/// // /  a <- getLine
/// // /  print $ eval $ run a
