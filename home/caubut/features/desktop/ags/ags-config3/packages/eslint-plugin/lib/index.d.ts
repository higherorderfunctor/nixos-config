declare const _default: {
    configs: {
        'json/recommended': import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray;
        'markdown/recommended': import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray;
        recommended: import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray;
        strict: import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray;
    };
    overrideWith: {
        (overrides: Partial<import("@typescript-eslint/utils/ts-eslint").FlatConfig.Config>): (configs: import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray) => import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray;
        (configs: import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray, overrides: Partial<import("@typescript-eslint/utils/ts-eslint").FlatConfig.Config>): import("@typescript-eslint/utils/ts-eslint").FlatConfig.ConfigArray;
    };
};
export default _default;
//# sourceMappingURL=index.d.ts.map