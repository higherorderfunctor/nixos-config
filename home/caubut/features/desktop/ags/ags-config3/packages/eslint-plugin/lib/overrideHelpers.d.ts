import type { TSESLint } from '@typescript-eslint/utils';
export declare const overrideWith: {
    (overrides: Partial<TSESLint.FlatConfig.Config>): (configs: TSESLint.FlatConfig.ConfigArray) => TSESLint.FlatConfig.ConfigArray;
    (configs: TSESLint.FlatConfig.ConfigArray, overrides: Partial<TSESLint.FlatConfig.Config>): TSESLint.FlatConfig.ConfigArray;
};
export declare const declareGlobals: (globals: readonly string[]) => {
    filter: {
        match: boolean;
        regex: string;
    };
    format: never[];
    modifiers: string[];
    selector: string;
}[];
//# sourceMappingURL=overrideHelpers.d.ts.map