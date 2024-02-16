/* eslint-disable @typescript-eslint/no-explicit-any, @typescript-eslint/consistent-type-definitions */
import { Effect } from 'effect';
import { flow, Match, Option, pipe } from 'effect';

// newtype Parser a = Parser { parse :: String -> [(a,String)] }

export type Sequence<T> = {
  [_: number]: T;
  slice: (start: number, end: number) => Sequence<T>;
  length: number;
};

export interface ParseState<I extends Sequence<any>, O> {
  input: I;
  index: number;
  value: O;
}

export const makeState = <I extends Sequence<any>>(input: I): ParseState<I, never> => ({
  input,
  index: 0,
  value: undefined as never,
});

export interface IncompleteParseError<I extends Sequence<any>> {
  _tag: 'IncompleteParseError';
  rest: I;
}

export interface ZeroError {
  _tag: 'ZeroError';
}

export interface InputMissing {
  _tag: 'ZeroError';
}

export interface SatisfyError<I extends Sequence<any>> {
  _tag: 'SatisfyError';
  input: I;
}

export type ParseError<I extends Sequence<any>> = IncompleteParseError<I> | ZeroError | InputMissing | SatisfyError<I>;

export type ParseResult<I extends Sequence<any>, O, E extends ParseError<I> = never> = Effect.Effect<
  ParseState<I, O>,
  E
>;

export type Parser<I extends Sequence<any>, A, O = A, E extends ParseError<I> = never> = (
  state: ParseState<I, A>,
) => ParseResult<I, O, E>;

export const parse: <I extends Sequence<any>, O, E extends ParseError<I> = never>(
  parser: Parser<I, never, O, E>,
) => (input: I) => Effect.Effect<O, E | IncompleteParseError<I>> = (parser) =>
  flow(
    makeState,
    parser,
    Effect.flatMap(<I extends Sequence<any>, O>(state: ParseState<I, O>) =>
      Match.value(state.index === state.input.length).pipe(
        Match.when(false, () =>
          Effect.fail<IncompleteParseError<I>>({ _tag: 'IncompleteParseError', rest: state.input }),
        ),
        Match.when(true, () => Effect.succeed(state.value)),
        Match.exhaustive,
      ),
    ),
  );

// instance Monad Parser where
//   p >>= f = Parser $ \inp ->
//     concat [parse (f v) inp' | (v, inp') <- parse p inp]
//   -- a -> Parser a
//   return = result

export const flatMap: <
  I extends Sequence<any>,
  A,
  B,
  O,
  E1 extends ParseError<I> = never,
  E2 extends ParseError<I> = never,
>(
  f: (state: B) => Parser<I, B, O, E2>,
) => (parser: Parser<I, A, B, E1>) => Parser<I, A, O, E1 | E2> = (f) => (parser) =>
  flow(
    parser,
    Effect.flatMap((state) => f(state.value)(state)),
  );

export const result: <I extends Sequence<any>, O>(value: O) => Parser<I, never, O> = (value) => (state) =>
  Effect.succeed({ ...state, value });

export const zero: Parser<Sequence<any>, any, never, ZeroError> = () => Effect.fail<ZeroError>({ _tag: 'ZeroError' });

export const item: <A>(state: ParseState<Sequence<A>, any>) => ParseResult<Sequence<A>, A, InputMissing> = (state) =>
  Match.value(state.index + 1 <= state.input.length).pipe(
    Match.when(false, () => Effect.fail<InputMissing>({ _tag: 'ZeroError' })),
    Match.when(true, () => Effect.succeed({ ...state, index: state.index + 1, value: state.input[state.index] })),
    Match.exhaustive,
  );

export const satisfy2: <A>(
  predicate: (a: A) => boolean,
) => Parser<Sequence<A>, any, A, ZeroError | SatisfyError<Sequence<A>>> = (predicate) =>
  flow(
    item,
    Effect.map((state) => predicate(state.value) ? result(state.value),
    (v) => v,
    // item(state),
    // (v) => v,
    // Effect.flatMap((s) => flatMap((x) => (predicate(x) ? result(x) : zero))),
  );

// sat :: (Char -> Bool) -> Parser Char
// sat p = Parser parseIfSat
//   where
//     parseIfSat (x : xs) = if p x then [(x, xs)] else []
//     parseIfSat [] = []
//
// -- Apply `item`, if it fails on an empty string, we simply short circuit and get `[]`.
// sat p =
//  item >>= \x ->
//    if p x
//      then result x
//      else zero
export const satisfy: <A>(
  predicate: (a: A) => boolean,
) => Parser<Sequence<A>, any, A, ZeroError | SatisfyError<Sequence<A>>> =
  <A>(predicate: (a: A) => boolean): Parser<Sequence<A>, any, A, ZeroError | SatisfyError<Sequence<A>>> =>
  (state) =>
    Match.value(state.index + 1 <= state.input.length).pipe(
      Match.when(false, () => Effect.fail<InputMissing>({ _tag: 'ZeroError' })),
      Match.when(true, () =>
        Match.value(predicate(state.input[state.index + 1])).pipe(
          Match.when(false, () =>
            Effect.fail<SatisfyError<Sequence<A>>>({
              _tag: 'SatisfyError',
              input: state.input.slice(state.index, state.index + 1),
            }),
          ),
          Match.when(true, () =>
            Effect.succeed<ParseState<Sequence<A>, A>>({
              ...state,
              index: state.index + 1,
              value: state.input[state.index],
            }),
          ),
          Match.exhaustive,
        ),
      ),
      Match.exhaustive,
    );

export const zzz = parse(item)('asdfasdf');

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
//
// export type Item<S = string> = Parser<Char<S>>;
//
// export const item: Parser<Item> = (source, i = 0) => {
//  if (source.length === i)
//    return [];
//  return [source[i], source, i + 1];
// }
//
// export const map: <A, B>(p: Parser<A>, f: (a: A) => B) => Parser<B> = (parser, f) =>
//  flow(
//    parser,
//    Effect.map(([a, s]) => [f(a), s]),
//  );
//
// export const apply = <A, B>(p: Parser<(a: A) => B>, q: Parser<A>): Parser<B> =>
//  flow(
//    p,
//    Effect.flatMap(([f, o]) =>
//      Option.map(o, (s) => Effect.map(q(s), ([a, r]): [B, Option.Option<string>] => [f(a), r])).pipe(
//        Option.getOrElse(() => Effect.fail(makeError('InsufficientInputError', ''))),
//      ),
//    ),
//  );
//
// export const flatMap: <A, B>(p: Parser<A>, f: (a: A) => Parser<B>) => Parser<B> = (parser, f) =>
//  flow(
//    parser,
//    Effect.flatMap(([a, s]) =>
//      s.pipe(
//        Option.map(f(a)),
//        Option.getOrElse(() =>
//          Effect.fail(
//            makeError(
//              'InsufficientInputError',
//              Option.getOrElse(s, () => ''),
//            ),
//          ),
//        ),
//      ),
//    ),
//  );
//
// export const isEmpty: (source: string) => Option.Option<string> = (source) =>
//  source === '' ? Option.none() : Option.some(source);
//
// export const string: (s: string) => Parser<string> = (s) => (source) =>
//  source.startsWith(s)
//    ? Effect.succeed([s, isEmpty(source.slice(s.length))])
//    : Effect.fail(makeError('InsufficientInputError', source));
//
//
// export const char: <C extends string>(c: Char<C>) => Parser<string> = string;
//
// export const space = char(' ');
// export const tab = char('\t');
//
/// / # -- | One or more.
/// / # some :: f a -> f [a]
/// / # some v = some_v
/// / #   where
/// / #     many_v = some_v <|> pure []
/// / #     some_v = (:) <$> v <*> many_v
/// / def some(v: Parser[A]) -> Parser[Sequence[A]]:
/// /     def many_v(s: Text) -> Sequence[Tuple[Sequence[A], Text]]:
/// /         return option(some_v, ret([]))(s)
/// /     def some_v(s: Text) -> Sequence[Tuple[Sequence[A], Text]]:
/// /         return ap(fmap(lambda x: lambda y: [x, *y], v), many_v)(s)
/// /     return some_v
//
/// / const some: <A>(v: Parser<A>) => Parser<A[]> = (v) => (source) => {
//
/// /bind :: Parser a -> (a -> Parser b) -> Parser b
/// /bind p f = Parser $ \s -> concatMap (\(a, s') -> parse (f a) s') $ parse p s
/// /
/// /unit :: a -> Parser a
/// /unit a = Parser (\s -> [(a,s)])
/// /
/// /instance Functor Parser where
/// /  fmap f (Parser cs) = Parser (\s -> [(f a, b) | (a, b) <- cs s])
/// /
/// /instance Applicative Parser where
/// /  pure = return
/// /  (Parser cs1) <*> (Parser cs2) = Parser (\s -> [(f a, s2) | (f, s1) <- cs1 s, (a, s2) <- cs2 s1])
/// /
/// /instance Monad Parser where
/// /  return = unit
/// /  (>>=)  = bind
/// /
/// /instance MonadPlus Parser where
/// /  mzero = failure
/// /  mplus = combine
/// /
/// /instance Alternative Parser where
/// /  empty = mzero
/// /  (<|>) = option
/// /
/// /combine :: Parser a -> Parser a -> Parser a
/// /combine p q = Parser (\s -> parse p s ++ parse q s)
/// /
/// /failure :: Parser a
/// /failure = Parser (\cs -> [])
/// /
/// /option :: Parser a -> Parser a -> Parser a
/// /option  p q = Parser $ \s ->
/// /  case parse p s of
/// /    []     -> parse q s
/// /    res    -> res
/// /
/// /satisfy :: (Char -> Bool) -> Parser Char
/// /satisfy p = item `bind` \c ->
/// /  if p c
/// /  then unit c
/// /  else failure
/// /
/// /-------------------------------------------------------------------------------
/// /-- Combinators
/// /-------------------------------------------------------------------------------
/// /
/// /oneOf :: [Char] -> Parser Char
/// /oneOf s = satisfy (flip elem s)
/// /
/// /chainl :: Parser a -> Parser (a -> a -> a) -> a -> Parser a
/// /chainl p op a = (p `chainl1` op) <|> return a
/// /
/// /chainl1 :: Parser a -> Parser (a -> a -> a) -> Parser a
/// /p `chainl1` op = do {a <- p; rest a}
/// /  where rest a = (do f <- op
/// /                     b <- p
/// /                     rest (f a b))
/// /                 <|> return a
/// /
/// /char :: Char -> Parser Char
/// /char c = satisfy (c ==)
/// /
/// /natural :: Parser Integer
/// /natural = read <$> some (satisfy isDigit)
/// /
/// /string :: String -> Parser String
/// /string [] = return []
/// /string (c:cs) = do { char c; string cs; return (c:cs)}
/// /
/// /token :: Parser a -> Parser a
/// /token p = do { a <- p; spaces ; return a}
/// /
/// /reserved :: String -> Parser String
/// /reserved s = token (string s)
/// /
/// /spaces :: Parser String
/// /spaces = many $ oneOf " \n\r"
/// /
/// /digit :: Parser Char
/// /digit = satisfy isDigit
/// /
/// /number :: Parser Int
/// /number = do
/// /  s <- string "-" <|> return []
/// /  cs <- some digit
/// /  return $ read (s ++ cs)
/// /
/// /parens :: Parser a -> Parser a
/// /parens m = do
/// /  reserved "("
/// /  n <- m
/// /  reserved ")"
/// /  return n
/// /
/// /-------------------------------------------------------------------------------
/// /-- Calulator parser
/// /-------------------------------------------------------------------------------
/// /
/// /-- number = [ "-" ] digit { digit }.
/// /-- digit = "0" | "1" | ... | "8" | "9".
/// /-- expr = term { addop term }.
/// /-- term = factor { mulop factor }.
/// /-- factor = "(" expr ")" | number.
/// /-- addop = "+" | "-".
/// /-- mulop = "*".
/// /
/// /data Expr
/// /  = Add Expr Expr
/// /  | Mul Expr Expr
/// /  | Sub Expr Expr
/// /  | Lit Int
/// /  deriving Show
/// /
/// /eval :: Expr -> Int
/// /eval ex = case ex of
/// /  Add a b -> eval a + eval b
/// /  Mul a b -> eval a * eval b
/// /  Sub a b -> eval a - eval b
/// /  Lit n   -> n
/// /
/// /int :: Parser Expr
/// /int = do
/// /  n <- number
/// /  return (Lit n)
/// /
/// /expr :: Parser Expr
/// /expr = term `chainl1` addop
/// /
/// /term :: Parser Expr
/// /term = factor `chainl1` mulop
/// /
/// /factor :: Parser Expr
/// /factor =
/// /      int
/// /  <|> parens expr
/// /
/// /infixOp :: String -> (a -> a -> a) -> Parser (a -> a -> a)
/// /infixOp x f = reserved x >> return f
/// /
/// /addop :: Parser (Expr -> Expr -> Expr)
/// /addop = (infixOp "+" Add) <|> (infixOp "-" Sub)
//
// mulop :: Parser (Expr -> Expr -> Expr)
// mulop = infixOp "*" Mul
//
// run :: String -> Expr
// run = runParser expr
//
// main :: IO ()
// main = forever $ do
//  putStr "> "
//  a <- getLine
//  print $ eval $ run a
