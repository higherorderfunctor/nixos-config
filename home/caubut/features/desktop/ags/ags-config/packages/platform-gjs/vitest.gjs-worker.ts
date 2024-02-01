import { pathToFileURL } from 'node:url';
import { workerId as poolId } from 'tinypool';
import { ModuleCacheMap } from 'vite-node/client';
import type { ContextRPC, WorkerGlobalState } from 'vitest';

if (isChildProcess()) setProcessTitle(`vitest ${poolId}`);

// this is what every pool executes when running tests
export const run = async (ctx: ContextRPC) => {
  const prepareStart = performance.now();

  const inspectorCleanup = setupInspect(ctx.config);

  process.env.VITEST_WORKER_ID = String(ctx.workerId);
  process.env.VITEST_POOL_ID = String(poolId);

  let state: WorkerGlobalState | null = null;

  try {
    // worker is a filepath or URL to a file that exposes a default export with "getRpcOptions" and "runTests" methods
    if (ctx.worker.startsWith('.'))
      throw new Error(`Path to the test runner cannot be relative, received "${ctx.worker}"`);

    const file = ctx.worker.startsWith('file:') ? ctx.worker : pathToFileURL(ctx.worker).toString();
    const testRunnerModule = await import(file);

    if (!testRunnerModule.default || typeof testRunnerModule.default !== 'object')
      throw new TypeError(
        `Test worker object should be exposed as a default export. Received "${typeof testRunnerModule.default}"`,
      );

    const worker = testRunnerModule.default as VitestWorker;
    if (!worker.getRpcOptions || typeof worker.getRpcOptions !== 'function')
      throw new TypeError(
        `Test worker should expose "getRpcOptions" method. Received "${typeof worker.getRpcOptions}".`,
      );

    // RPC is used to communicate between worker (be it a thread worker or child process or a custom implementation) and the main thread
    const { onCancel, rpc } = createRuntimeRpc(worker.getRpcOptions(ctx));

    const beforeEnvironmentTime = performance.now();
    const environment = await loadEnvironment(ctx, rpc);
    if (ctx.environment.transformMode) environment.transformMode = ctx.environment.transformMode;

    state = {
      ctx,
      // here we create a new one, workers can reassign this if they need to keep it non-isolated
      moduleCache: new ModuleCacheMap(),
      mockMap: new Map(),
      config: ctx.config,
      onCancel,
      environment,
      durations: {
        environment: beforeEnvironmentTime,
        prepare: prepareStart,
      },
      rpc,
      providedContext: ctx.providedContext,
    };

    if (!worker.runTests || typeof worker.runTests !== 'function')
      throw new TypeError(`Test worker should expose "runTests" method. Received "${typeof worker.runTests}".`);

    await worker.runTests(state);
  } finally {
    await rpcDone().catch(() => {});
    inspectorCleanup();
    if (state) {
      state.environment = null as any;
      state = null;
    }
  }
};
