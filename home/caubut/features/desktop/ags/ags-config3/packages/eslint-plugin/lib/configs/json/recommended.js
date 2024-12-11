import { pipe } from 'effect';
import jsoncPlugin from 'eslint-plugin-jsonc';
import prettierPlugin from 'eslint-plugin-prettier';
import prettierRecommended from 'eslint-plugin-prettier/recommended';
import jsoncParser from 'jsonc-eslint-parser';
import tseslint from 'typescript-eslint';
import { overrideWith } from '../../overrideHelpers.js';
const plugins = {
    jsonc: jsoncPlugin,
    prettier: prettierPlugin,
};
const overrides = {
    plugins,
    languageOptions: {
        parser: jsoncParser,
    },
};
const eslintConfig = pipe(tseslint.config(prettierRecommended, ...jsoncPlugin.configs['flat/prettier'], ...jsoncPlugin.configs['flat/recommended-with-jsonc']), overrideWith(overrides));
export default eslintConfig;
//# sourceMappingURL=recommended.js.map