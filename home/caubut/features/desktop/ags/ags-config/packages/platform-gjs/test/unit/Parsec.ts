import { Effect, Types } from 'effect';

export type ExtraInputError<A> = {
  readonly _tag: 'ExtraInputError';
  readonly parsed: A;
  readonly extra: string;
  readonly test: number;
};

export type InsufficientInputError<A> = {
  readonly _tag: 'InsufficientInputError';
  readonly parsed: A;
  readonly rest: string;
};

export type ParseError<A> = ExtraInputError<A> | InsufficientInputError<A>;

export type ExtractErrorByTag<A, Tag extends ParseError<A>['_tag']> = Types.ExtractTag<ParseError<A>, Tag>;

export type Z = ExtractErrorByTag<string, 'ExtraInputError'>;

export type ParseErrorFields<A, Tag extends Types.Tags<ParseError<A>>> = Omit<{ [F in keyof Types.ExtractTag<ParseError<A>, Tag>]: Types.ExtractTag<ParseError<A>, Tag>[F] }, '_tag'>;

export type Test = ParseErrorFields<string, 'ExtraInputError'>;

type LastOf<T> =
  Types.UnionToIntersection<T extends any ? () => T : never> extends () => (infer R) ? R : never

type Push<T extends any[], V> = [...T, V];

type TuplifyUnion<T, L = LastOf<T>, N = [T] extends [never] ? true : false> =
  true extends N ? [] : Push<TuplifyUnion<Exclude<T, L>>, L>

type ObjValueTuple<T, KS extends any[] = TuplifyUnion<keyof T>, R extends any[] = []> =
  KS extends [infer K, ...infer KT]
  ? ObjValueTuple<T, KT, [...R, T[K & keyof T]]>
  : R

export type TTT = ObjValueTuple<Test>;

export type ObjectToNamedTuple<T, KS = keyof T> = KS extends [infer K, ...infer KT]
  ? K extends keyof T
    ? [[K]: T[K], ObjectToNamedTuple<Omit<T, K>>]
    : KS extends [infer K]
      ? [[K]: T[K]]
      : never
      : never;

export type TupleTest<T> = keyof T extends infer K | infer KT
  ? K extends keyof T
    ? [`${K}`: T[K]]
    : 'keyof'
    : 'expend'

export type ZJ = keyof Test;
export type ZZZ = TupleTest<Test>;


export const makeError = <A>(_tag: Types.Tags<ParseError<A>>, ...fields: ParseErrorFields<A, typeof _tag>): Types.ExtractTag<ParseError<A>, typeof _tag> => ({ _tag, ...fields })

const test = makeError('ExtraInputError', '123', 'abc');

export type Parser<A> = (source: string) => Effect.Effect<[A, string], ParseError<A>>;

export const parse =
  <T>(parser: Parser<T>) =>
  (source: string) =>
    parser(source);

export const parseAll =
  <T>(parser: Parser<T>) =>
  (source: string) =>
    parser(source).pipe(Effect.flatMap(([a, extra]) => extra ? [a, extra]));
