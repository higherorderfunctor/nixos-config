import { GLib } from '@girs/glib-2.0';

try {
  const loop = new GLib.MainLoop(null, false);
  import('vitest/config')
    .then(({ defineConfig }) => import('vitest/node').then(({ startVitest }) => ({ defineConfig, startVitest })))
    .then(({ defineConfig, startVitest }) => {
      const vitestConfig = defineConfig({
        test: {
          // environment: './vitest.gjs-env.ts',
          // runner: './vitest.gjs-runner.ts',
          includeSource: ['tests/**/*.test.ts'],
        },
      });
      return startVitest('test', undefined, undefined, vitestConfig);
    })
    .then((vitest) => vitest?.close())
    .then(() => {
      loop.quit();
    })
    .catch(console.error);

  loop.run();
} catch (error) {
  console.error(error);
}
