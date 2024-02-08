/* eslint-disable @typescript-eslint/no-explicit-any */
// Based on https://github.com/philipphoffmann/gjsunit

import { Context, Effect, HashMap, Layer, pipe, ReadonlyArray, STM, SynchronizedRef, TMap, TRef } from 'effect';

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

export type Namespaces = {
  [key: string]: () => Promise<void> | Namespaces;
};

export type Callback = () => Promise<void>;

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

export type Test = () => Effect.Effect<never, any, void>;

export type RunnerState = {
  suites: HashMap.HashMap<string, SynchronizedRef.SynchronizedRef<HashMap.HashMap<string, Test>>>;
  current: SynchronizedRef.SynchronizedRef<HashMap.HashMap<string, Test>> | null;
};

export type RunnerBuilder = (state: RunnerState) => Effect.Effect<never, never, RunnerState>;

export const builders: RunnerBuilder[] = [];

export const describe = (name: string, makeTests: () => void) => {
  builders.push(({ suites }) =>
    Effect.gen(function* (_) {
      const current = yield* _(SynchronizedRef.make(HashMap.empty<string, Test>()));
      return {
        suites: HashMap.set(suites, name, current),
        current,
      };
    }),
  );
  makeTests();
  builders.push(({ suites }) =>
    Effect.sync(() => ({
      suites,
      current: null,
    })),
  );
};

export type TestError = { _tag: 'TestError'; message: string };

export type TestResult = Effect.Effect<never, TestError, void>;

export type TestReport = { name: string; result: TestResult };

export const runTest = (name: string, test: Test): TestReport => ({
  name,
  result: test().pipe(
    Effect.catchAllDefect(Effect.fail),
    Effect.mapError((error): TestError => ({ _tag: 'TestError', message: `${error}` })),
    (v) => v,
  ),
});

export const it = (name: string, test: Test) => {
  builders.push(({ current, suites }) =>
    Effect.gen(function* (_) {
      if (current === null) {
        throw new Error('No current suite');
      }
      yield* _(SynchronizedRef.update(current, HashMap.set(name, test)));
      return {
        suites,
        current,
      };
    }),
  );
};

describe('FileSystem', () => {
  it('readFile', () =>
    Effect.gen(function* (_) {
      console.log('I RAN!!!');
      // expect(null).toEqual('lorem ipsum dolar sit amet');
    }));
});
const program = ReadonlyArray.reduce(
  builders,
  Effect.succeed({
    suites: HashMap.empty<string, SynchronizedRef.SynchronizedRef<HashMap.HashMap<string, Test>>>(),
    current: null as SynchronizedRef.SynchronizedRef<HashMap.HashMap<string, Test>> | null,
  }),
  (testSuites, op) => Effect.flatMap(testSuites, op),
).pipe(
  Effect.flatMap(({ suites }) =>
    Effect.succeed(
      suites.pipe(
        HashMap.map((suite, suiteName) =>
          SynchronizedRef.get(suite).pipe(
            Effect.tap(() => {
              print(suiteName);
            }),
            Effect.flatMap((asdf) => HashMap.map(asdf, (a, testName) => a())),
          ),
        ),
      ),
    ),
  ),
);

console.log(Effect.runSync(program));

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
