import * as Fs from '@effect/platform-gjs/FileSystem.js';
import * as Effect from 'effect/Effect';

import { assert, describe, expect, it } from './unit.js';

const runPromise = <E, A>(self: Effect.Effect<Fs.FileSystem, E, A>) =>
  Effect.runPromise(Effect.provide(self, Fs.layer));

describe('FileSystem', async () => {
  it('readFile', () =>
    runPromise(
      Effect.gen(function* (_) {
        const fs = yield* _(Fs.FileSystem);
        const data = yield* _(fs.readFile(`${__dirname}/fixtures/text.txt`));
        const text = new TextDecoder().decode(data);
        expect(text.trim()).toEqual('lorem ipsum dolar sit amet');
      }),
    ));
});
