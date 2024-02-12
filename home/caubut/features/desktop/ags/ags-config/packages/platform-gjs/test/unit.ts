import type { FileSystem } from '@effect/platform';
import type { PlatformError } from '@effect/platform/Error';
import { NodeFileSystem } from '@effect/platform-node';
import * as Ansi from '@effect/printer-ansi/Ansi';
import * as Doc from '@effect/printer-ansi/AnsiDoc';
import { Effect, flow, HashMap, Layer, Option, pipe, ReadonlyArray, ReadonlyRecord, SynchronizedRef } from 'effect';
import { inspect } from 'node:util';

import * as SourceMap from './unit/SourceMap.js';
import * as Stacktrace from './unit/Stacktrace.js';
import * as StacktraceReporter from './unit/StacktraceReporter.js';

const FileSystemLive = NodeFileSystem.layer;
// const FileSystemLive =
//   process.env.NODE_RUNTIME === 'gjs'
//     ? await import('@effect/platform-gjs').then((_) => _.FileSystem.layer)
//     : await import('@effect/platform-node').then((_) => _.NodeFileSystem.layer);

export type UnhandledError = { _tag: 'UnhandledError'; message: string; stack: Option.Option<string> };

export type TestError = UnhandledError;

export type Test = () => Effect.Effect<void, TestError>;

export type TestSuiteName = string;
export type TestFilename = string;
export type TestDescription = string;

export type TestResult = {
  suite: TestSuiteName | null;
  file: TestFilename;
  description: TestDescription;
  output: string;
  error: Option.Option<TestError>;
};

export type TestRunnerState = {
  suites: HashMap.HashMap<
    TestSuiteName,
    SynchronizedRef.SynchronizedRef<
      HashMap.HashMap<TestFilename, HashMap.HashMap<TestDescription, Effect.Effect<TestResult>>>
    >
  >;
  current: Option.Option<{
    suite: TestSuiteName;
    ref: SynchronizedRef.SynchronizedRef<
      HashMap.HashMap<TestFilename, HashMap.HashMap<TestDescription, Effect.Effect<TestResult>>>
    >;
  }>;
  global: SynchronizedRef.SynchronizedRef<
    HashMap.HashMap<TestFilename, HashMap.HashMap<TestDescription, Effect.Effect<TestResult>>>
  >;
};

export const serializeError =
  (tag: TestError['_tag']) =>
  (error: unknown): TestError => {
    if (error instanceof Error) {
      return { _tag: tag, message: error.message, stack: Option.fromNullable(error.stack) };
    }
    return { _tag: tag, message: JSON.stringify(error), stack: Option.none() };
  };

export const runTest = (
  suite: TestSuiteName | null,
  file: TestFilename,
  description: TestDescription,
  test: () => Effect.Effect<void, TestError>,
): Effect.Effect<TestResult> =>
  test().pipe(
    Effect.map(Option.none<TestError>),
    Effect.catchAll(flow(Option.some, Effect.succeed)),
    Effect.catchAllDefect(Effect.fail),
    Effect.catchAll(flow(serializeError('UnhandledError'), Option.some, Effect.succeed)),
    Effect.map((error) => ({
      suite,
      file,
      description,
      output: '',
      error,
    })),
  );

export const testRunnerState: ((
  state: TestRunnerState,
) => Effect.Effect<TestRunnerState, PlatformError, FileSystem.FileSystem | SourceMap.SourceMap>)[] = [];

export const describe = (suite: TestSuiteName, tests: () => void) => {
  testRunnerState.push(({ global, suites }) =>
    Effect.gen(function* (_) {
      const currentRef = yield* _(
        SynchronizedRef.make(
          HashMap.empty<TestFilename, HashMap.HashMap<TestDescription, Effect.Effect<TestResult>>>(),
        ),
      );
      return {
        suites: HashMap.set(suites, suite, currentRef),
        current: Option.some({ suite, ref: currentRef }),
        global,
      };
    }),
  );
  tests();
  testRunnerState.push(({ global, suites }: TestRunnerState) =>
    Effect.succeed({
      suites,
      current: Option.none(),
      global,
    }),
  );
};

const getCaller = Effect.gen(function* (_) {
  const stacktrace = yield* _(
    Stacktrace.from(new Error('asdf')).pipe(Option.map(StacktraceReporter.format), Option.getOrThrow),
  );
  console.log('>>>', stacktrace, '<<<');
  return '';
}); // # TODO:.pipe(Effect.provide(Layer.merge(SourceMapLookupLive, FileSystem.layer)));

export const it = (file: TestFilename, description: TestDescription, test: Test) => {
  testRunnerState.push(({ current, global, suites }) =>
    pipe(
      Option.getOrElse(current, () => ({ suite: null, ref: global })),
      ({ ref, suite }) =>
        getCaller.pipe(
          Effect.tap(console.log),
          Effect.flatMap(() =>
            SynchronizedRef.getAndUpdate(ref, (results) =>
              HashMap.get(results, file).pipe(
                Option.getOrElse(() => HashMap.empty<TestDescription, Effect.Effect<TestResult>>()),
                HashMap.set(description, runTest(suite, file, description, test)),
                (update) => HashMap.set(results, file, update),
              ),
            ),
          ),
          Effect.map(
            () =>
              ({
                global,
                current,
                suites,
              }) as TestRunnerState,
          ),
        ),
    ),
  );
};

const report = (state: TestRunnerState) =>
  pipe(
    // suites
    pipe(HashMap.values(state.suites), ReadonlyArray.fromIterable),
    ReadonlyArray.append(state.global),
    // files
    ReadonlyArray.map(flow(SynchronizedRef.get, Effect.map(flow(HashMap.values, ReadonlyArray.fromIterable)))),
    // tests
    ReadonlyArray.map(
      Effect.flatMap(flow(ReadonlyArray.flatMap(flow(HashMap.values, ReadonlyArray.fromIterable)), Effect.all)),
    ),
    // flatten
    flow(Effect.all, Effect.map(ReadonlyArray.flatten)),
    // sum totals
    Effect.map(
      ReadonlyArray.reduce(
        {
          files: {} as Record<TestFilename, { failed: number; passed: number } | undefined>,
          tests: { failed: 0, passed: 0 },
        },
        ({ files, tests }, next) => ({
          files: {
            ...files,
            [next.file]: {
              failed: (files[next.file]?.failed ?? 0) + (Option.isSome(next.error) ? 1 : 0),
              passed: (files[next.file]?.passed ?? 0) + (Option.isNone(next.error) ? 1 : 0),
            },
          },
          tests: {
            failed: tests.failed + (Option.isSome(next.error) ? 1 : 0),
            passed: tests.passed + (Option.isNone(next.error) ? 1 : 0),
          },
        }),
      ),
    ),
    Effect.map(({ files, tests }) => ({
      files: {
        failed: ReadonlyRecord.size(ReadonlyRecord.filter(files, (file) => !!file?.failed)),
        passed: ReadonlyRecord.size(ReadonlyRecord.filter(files, (file) => !file?.failed)),
      },
      tests,
    })),
    Effect.tap(({ files, tests }) => {
      const makeFieldSum = ({ failed, passed }: { passed: number; failed: number }) =>
        Doc.hsep(
          ReadonlyArray.getSomes([
            Option.fromNullable(failed || null).pipe(
              Option.map((failed) => Doc.text(`${failed} failed`).pipe(Doc.annotate(Ansi.red))),
            ),
            Option.fromNullable(passed + failed === 0 ? passed : passed || null).pipe(
              Option.map((passed) => Doc.text(`${passed} passed`).pipe(Doc.annotate(Ansi.green))),
            ),
            Option.some(Doc.text(`(${passed + failed})`)),
          ]),
        );
      const fields = { 'Test files': makeFieldSum(files), Tests: makeFieldSum(tests) };
      const firstColumnWidth = Math.max(...ReadonlyArray.map(ReadonlyRecord.keys(fields), (field) => field.length)) + 1;
      (globalThis.print ?? console.log)(
        Doc.render(
          Doc.vsep(
            ReadonlyArray.map(ReadonlyRecord.keys(fields) as (keyof typeof fields)[], (field) =>
              Doc.hsep([Doc.text(`${field.padStart(firstColumnWidth, ' ')} `), fields[field]]),
            ),
          ).pipe(Doc.annotate(Ansi.blackBright)),
          { style: 'pretty' },
        ),
      );
    }),
  );

const run = () =>
  Effect.gen(function* (_) {
    const results = yield* _(
      ReadonlyArray.reduce(
        testRunnerState,
        Effect.succeed({
          suites: HashMap.empty(),
          current: Option.none(),
          global: SynchronizedRef.unsafeMake(HashMap.empty()),
        }) as Effect.Effect<TestRunnerState, PlatformError, SourceMap.SourceMap | FileSystem.FileSystem>,
        (results, op) => Effect.flatMap(results, op),
      ),
    );

    const reportz = yield* _(report(results));

    // const report = ReadonlyArray.reduce(
    //   { files: { pass: 0, fail: 0 }, tests: { pass: 0, fail: 0 }},
    //   results,
    //   ({ files, tests }
    // )

    // const text = Doc.hsep([Doc.text(JSON.stringify(results, null, 2))]);

    // (globalThis.print ?? console.log)(Doc.render(text, { style: 'pretty' }));
  });

describe('FileSystem', () => {
  it('asdf', 'readFile', () =>
    Effect.gen(function* (_) {
      yield* _(
        Effect.sync(() => {
          console.log('I RAN!!!');
        }),
      );
      // expect(null).toEqual('lorem ipsum dolar sit amet');
    }),
  );

  it('asdf', 'test', () =>
    Effect.gen(function* (_) {
      yield* _(
        Effect.sync(() => {
          console.log('I FAILED!!!');
        }),
      );
      throw new Error('I failed');
      // expect(null).toEqual('lorem ipsum dolar sit amet');
    }),
  );
});

it('asdfaksdf', 'nop', () =>
  Effect.gen(function* (_) {
    yield* _(
      Effect.sync(() => {
        console.log('I ALSO FAILED!!!');
      }),
    );
    throw new Error('I failed');
    // expect(null).toEqual('lorem ipsum dolar sit amet');
  }),
);

await Effect.runPromiseExit(run().pipe(Effect.provide(Layer.provideMerge(SourceMap.layer, FileSystemLive))))
  .then((exit) => {
    console.log(inspect(exit, false, null, true));
  })
  .catch((error) => {
    console.log(inspect(error, false, null, true));
  });

// export type TestReport = { name: string; result: TestResult[] };
// export type TestSuiteReport = TestReport[];
//
// export const runTest = (suiteName: string, name: string, test: TestMethod): Effect.Effect<never, never, TestResult> => {
//   let output = '';
//   const collector = (...args: string[]) => {
//     output += args.join('');
//   };
//   let print = null;
//   let log = null;
//   if (globalThis.print) {
//     print = globalThis.print;
//     globalThis.print = collector;
//   } else {
//     log = console.log;
//     console.log = collector;
//   }
//   const result = test().pipe(
//     Effect.map(Option.none<TestError>),
//     Effect.catchAllDefect(Effect.fail),
//     Effect.catchAll((error) => Effect.succeedSome<TestError>({ _tag: 'UnhandledError', error })),
//     Effect.map((error) => ({
//       suiteName,
//       name,
//       output,
//       error,
//     })),
//   );
//   if (print) {
//     globalThis.print = print;
//   } else {
//     console.log = log;
//   }
//   console.log('✓');
//   return result;
// };
//
//
// const rez = await Effect.runPromise(
//   program.pipe(
//     Effect.map((report) => {
//       console.info(report);
//       return report;
//     }),
//     Effect.catchAllDefect((error) => Effect.succeed(error)),
//     Effect.catchAll((error) => {
//       console.log(error);
//       return Effect.succeed(error);
//     }),
//   ),
// ).catch(console.error);
//
// const printReport = (report: TestSuiteReport) => {
//   const firstStage = report
//     .map((asdf) => `${asdf.name}\n${asdf.result.map((r) => r.name + (Option.isSome(r.error) ? 'x' : '+')).join('\n')}`)
//     .join('\n');
//   const f = report
//     .flatMap((asdf) =>
//       asdf.result
//         .filter((xx) => Option.isSome(xx.error))
//         .map((r) => `${r.name}\n${Option.getOrThrow(r.error).error?.message ?? 'nope'}`),
//     )
//     .join('\n');
//   return `${firstStage}\n${f}`;
// };
// import '@girs/gjs';

// import nodeAssert from 'assert';
// import type GLib from 'gi://GLib?version=2.0';
//
// const mainloop: GLib.MainLoop | undefined = (globalThis as any)?.imports?.mainloop;
//
// let countTestsOverall = 0;
// let countTestsFailed = 0;
// let countTestsIgnored = 0;
// const runtime = '';
//
// const RED = '\x1B[31m';
// const GREEN = '\x1B[32m';
// const BLUE = '\x1b[34m';
// const GRAY = '\x1B[90m';
// const RESET = '\x1B[39m';

// export type Runtime = 'Gjs' | 'Deno' | 'Node.js' | 'Unknown' | 'Browser';
//
// // Makes this work on Gjs and Node.js
// export const print = globalThis.print || console.log;
//
// class MatcherFactory {
//   public not: MatcherFactory;
//
//   constructor(
//     protected readonly actualValue: any,
//     protected readonly positive: boolean,
//     negated?: MatcherFactory,
//   ) {
//     if (negated) {
//       this.not = negated;
//     } else {
//       this.not = new MatcherFactory(actualValue, !positive, this);
//     }
//   }
//
//   triggerResult(success: boolean, msg: string) {
//     if ((success && !this.positive) || (!success && this.positive)) {
//       ++countTestsFailed;
//       throw new Error(msg);
//     }
//   }
//
//   to(callback: (actualValue: any) => boolean) {
//     this.triggerResult(callback(this.actualValue), `      Expected callback to validate`);
//   }
//
//   toBe(expectedValue: any) {
//     this.triggerResult(
//       this.actualValue === expectedValue,
//       `      Expected values to match using ===\n` +
//         `      Expected: ${expectedValue} (${typeof expectedValue})\n` +
//         `      Actual: ${this.actualValue} (${typeof this.actualValue})`,
//     );
//   }
//
//   toEqual(expectedValue: any) {
//     this.triggerResult(
//       this.actualValue == expectedValue,
//       `      Expected values to match using ==\n` +
//         `      Expected: ${expectedValue} (${typeof expectedValue})\n` +
//         `      Actual: ${this.actualValue} (${typeof this.actualValue})`,
//     );
//   }
//
//   toEqualArray(expectedValue: any[] | Uint8Array) {
//     let success =
//       Array.isArray(this.actualValue) &&
//       Array.isArray(expectedValue) &&
//       this.actualValue.length === expectedValue.length;
//
//     for (let i = 0; i < this.actualValue.length; i++) {
//       const actualVal = this.actualValue[i];
//       const expectedVal = expectedValue[i];
//       success = actualVal == expectedVal;
//       if (!success) break;
//     }
//
//     this.triggerResult(
//       success,
//       `      Expected array items to match using ==\n` +
//         `      Expected: ${expectedValue} (${typeof expectedValue})\n` +
//         `      Actual: ${this.actualValue} (${typeof this.actualValue})`,
//     );
//   }
//
//   toMatch(expectedValue: any) {
//     if (typeof this.actualValue.match !== 'function') {
//       throw new Error(`You can not use toMatch on type ${typeof this.actualValue}`);
//     }
//     this.triggerResult(
//       !!this.actualValue.match(expectedValue),
//       `      Expected values to match using regular expression\n` +
//         `      Expression: ${expectedValue}\n` +
//         `      Actual: ${this.actualValue}`,
//     );
//   }
//
//   toBeDefined() {
//     this.triggerResult(typeof this.actualValue !== 'undefined', `      Expected value to be defined`);
//   }
//
//   toBeUndefined() {
//     this.triggerResult(typeof this.actualValue === 'undefined', `      Expected value to be undefined`);
//   }
//
//   toBeNull() {
//     this.triggerResult(this.actualValue === null, `      Expected value to be null`);
//   }
//
//   toBeTruthy() {
//     this.triggerResult(this.actualValue as unknown as boolean, `      Expected value to be truthy`);
//   }
//
//   toBeFalsy() {
//     this.triggerResult(!this.actualValue, `      Expected value to be falsy`);
//   }
//
//   toContain(needle: any) {
//     this.triggerResult(
//       this.actualValue instanceof Array && this.actualValue.includes(needle),
//       `      Expected ${this.actualValue} to contain ${needle}`,
//     );
//   }
//
//   toBeLessThan(greaterValue: number) {
//     this.triggerResult(
//       this.actualValue < greaterValue,
//       `      Expected ${this.actualValue} to be less than ${greaterValue}`,
//     );
//   }
//
//   toBeGreaterThan(smallerValue: number) {
//     this.triggerResult(
//       this.actualValue > smallerValue,
//       `      Expected ${this.actualValue} to be greater than ${smallerValue}`,
//     );
//   }
//
//   toBeCloseTo(expectedValue: number, precision: number) {
//     const shiftHelper = 10 ** precision;
//     this.triggerResult(
//       Math.round((this.actualValue as unknown as number) * shiftHelper) / shiftHelper ===
//         Math.round(expectedValue * shiftHelper) / shiftHelper,
//       `      Expected ${this.actualValue} with precision ${precision} to be close to ${expectedValue}`,
//     );
//   }
//
//   toThrow(ErrorType?: typeof Error) {
//     let errorMessage = '';
//     let didThrow = false;
//     let typeMatch = true;
//     try {
//       this.actualValue();
//       didThrow = false;
//     } catch (e) {
//       errorMessage = e.message || '';
//       didThrow = true;
//       if (ErrorType) {
//         typeMatch = e instanceof ErrorType;
//       }
//     }
//     const functionName =
//       this.actualValue.name || typeof this.actualValue === 'function'
//         ? '[anonymous function]'
//         : this.actualValue.toString();
//     this.triggerResult(
//       didThrow,
//       `      Expected ${functionName} to ${this.positive ? 'throw' : 'not throw'} an exception ${!this.positive && errorMessage ? `, but an error with the message "${errorMessage}" was thrown` : ''}`,
//     );
//
//     if (ErrorType) {
//       this.triggerResult(
//         typeMatch,
//         `      Expected Error type '${ErrorType.name}', but the error is not an instance of it`,
//       );
//     }
//   }
// }
//

// export type TestRunner = {
//   registerSuite: (name: string, tests: () => Effect.Effect<never, never, void>) => Effect.Effect<never, never, void>;
// };
//
// export const TestRunner = Context.Tag<TestRunner>()
//
// export const TestRunnerLive = Layer.effect(
//   TestRunner,
//   Effect.gen(function* (_) {
//     const suites = yield* _(TMap.empty<string, null>().pipe(STM.commit, Effect.flatMap(SynchronizedRef.make)));
//     return TestRunner.of({
//       registerSuite(name) {
//       SynchronizedRef.updateEffect(suites, (suites) => {
//         return TMap.set(suites, name, null).pipe(v=>v,STM.commit, v=>v);
//       })
//       }
//     })
//   })
// )
//
// Effect.gen(function* (_) {
//   console.log(moduleName);
//   // const config = yield* _(TestRunner);
//   // yield* _(config.registerSuite(moduleName, tests));
//   // Reset after and before callbacks
//   // beforeEachCb = null;
//   // afterEachCb = null;
// });

// const createTestSuite = () => {
//   return {
//     describe:
//   };
// }

//
// const runtimeMatch = async (onRuntime: Runtime[], version?: string) => {
//   const currRuntime = await getRuntime();
//
//   const foundRuntime = onRuntime.find((r) => currRuntime.includes(r));
//
//   if (!foundRuntime) {
//     return {
//       matched: false,
//     };
//   }
//
//   if (typeof version === 'string') {
//     // TODO allow version wildcards like 16.x.x
//     if (!currRuntime.includes(version)) {
//       return {
//         matched: false,
//       };
//     }
//   }
//
//   return {
//     matched: true,
//     runtime: foundRuntime,
//     version,
//   };
// };
//
// // TODO add support for Browser
// /** E.g on('Deno', () {  it(...) }) */
// export const on = async (onRuntime: Runtime | Runtime[], version: string | Callback, callback?: Callback) => {
//   if (typeof onRuntime === 'string') {
//     onRuntime = [onRuntime];
//   }
//
//   if (typeof version === 'function') {
//     callback = version;
//     version = undefined;
//   }
//
//   const { matched } = await runtimeMatch(onRuntime, version as string | undefined);
//
//   if (!matched) {
//     ++countTestsIgnored;
//     return;
//   }
//
//   print(`\nOn ${onRuntime.join(', ')}${version ? ` ${version}` : ''}`);
//
//   await callback();
// };
//
// let beforeEachCb: Callback | undefined | null;
// let afterEachCb: Callback | undefined | null;
//
// export const beforeEach = (callback?: Callback) => {
//   beforeEachCb = callback;
// };
//
// export const afterEach = (callback?: Callback) => {
//   afterEachCb = callback;
// };
//
// export const it = async (expectation: string, callback: () => void | Promise<void>) => {
//   try {
//     if (typeof beforeEachCb === 'function') {
//       await beforeEachCb();
//     }
//
//     await callback();
//
//     if (typeof afterEachCb === 'function') {
//       await afterEachCb();
//     }
//
//     print(`  ${GREEN}✔${RESET} ${GRAY}${expectation}${RESET}`);
//   } catch (e) {
//     print(`  ${RED}❌${RESET} ${GRAY}${expectation}${RESET}`);
//     print(`${RED}${e.message}${RESET}`);
//     if (e.stack) print(e.stack);
//   }
// };
//
// export const expect = (actualValue: any) => {
//   ++countTestsOverall;
//
//   const expecter = new MatcherFactory(actualValue, true);
//
//   return expecter;
// };
//
// export const assert = (success: any, message?: string | Error) => {
//   ++countTestsOverall;
//
//   if (!success) {
//     ++countTestsFailed;
//   }
//
//   nodeAssert(success, message);
// };
//
// assert.strictEqual = <T>(actual: unknown, expected: T, message?: string | Error): asserts actual is T => {
//   ++countTestsOverall;
//   try {
//     nodeAssert.strictEqual(actual, expected, message);
//   } catch (error) {
//     ++countTestsFailed;
//     throw error;
//   }
// };
//
// assert.throws = (promiseFn: () => unknown, ...args: any[]) => {
//   ++countTestsOverall;
//   let error: any;
//   try {
//     promiseFn();
//   } catch (e) {
//     error = e;
//   }
//
//   if (!error) ++countTestsFailed;
//
//   nodeAssert.throws(
//     () => {
//       if (error) throw error;
//     },
//     args[0],
//     args[1],
//   );
// };
//
// assert.deepStrictEqual = <T>(actual: unknown, expected: T, message?: string | Error): asserts actual is T => {
//   ++countTestsOverall;
//   try {
//     nodeAssert.deepStrictEqual(actual, expected, message);
//   } catch (error) {
//     ++countTestsFailed;
//     throw error;
//   }
// };
//
// // TODO wrap more assert methods
//
// const runTests = async (namespaces: Namespaces) => {
//   // recursively check the test directory for executable tests
//   for (const subNamespace in namespaces) {
//     const namespace = namespaces[subNamespace];
//     // execute any test functions
//     if (typeof namespace === 'function') {
//       await namespace();
//     }
//     // descend into subfolders and objects
//     else if (typeof namespace === 'object') {
//       await runTests(namespace);
//     }
//   }
// };
//
// const printResult = () => {
//   if (countTestsIgnored) {
//     // some tests ignored
//     print(`\n${BLUE}✔ ${countTestsIgnored} ignored test${countTestsIgnored > 1 ? 's' : ''}${RESET}`);
//   }
//
//   if (countTestsFailed) {
//     // some tests failed
//     print(`\n${RED}❌ ${countTestsFailed} of ${countTestsOverall} tests failed${RESET}`);
//   } else {
//     // all tests okay
//     print(`\n${GREEN}✔ ${countTestsOverall} completed${RESET}`);
//   }
// };

// export const run = async (namespaces: Namespaces) => {
//   console.log('here!!@#1@#');
//   // async () =>
//   //   runTests(namespaces).then(() => {
//   //     printResult();
//   //     print();
//   //     mainloop?.quit();
//   //   });
//   // // Run the GJS mainloop for async operations
//   // mainloop?.run();
// };

export default {
  // run,
  //   assert,
  //   expect,
  //   it,
  //   afterEach,
  //   beforeEach,
  //   on,
  describe,
};
