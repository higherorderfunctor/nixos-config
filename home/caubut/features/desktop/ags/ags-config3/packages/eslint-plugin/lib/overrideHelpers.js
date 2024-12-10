import { Array } from 'effect';
import { dual } from 'effect/Function';
export const overrideWith = dual(2, (configs, overrides) => configs.map((config) => ({
    ...config,
    ...overrides,
    plugins: { ...overrides.plugins, ...(config.plugins ?? {}) },
})));
export const declareGlobals = (globals) => {
    if (Array.isEmptyReadonlyArray(globals)) {
        return [];
    }
    return [
        {
            filter: {
                match: true,
                regex: `^(${globals.join('|')})$`,
            },
            format: [],
            modifiers: ['const'],
            selector: 'variable',
        },
    ];
};
//# sourceMappingURL=overrideHelpers.js.map