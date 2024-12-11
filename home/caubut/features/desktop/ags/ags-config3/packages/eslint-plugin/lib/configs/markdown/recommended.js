import { pipe } from 'effect';
import codegenPlugin, { processors as codegenPluginProcessors } from 'eslint-plugin-codegen';
import markdownPlugin from 'eslint-plugin-markdown';
import tseslint from 'typescript-eslint';
import { overrideWith } from '../../overrideHelpers.js';
const plugins = {
    markdown: markdownPlugin,
    codegen: codegenPlugin,
};
const overrides = {
    plugins,
    processor: {
        ...codegenPluginProcessors.processor,
        meta: {
            name: 'eslint-plugin-codegen-md-processor',
            version: markdownPlugin.version,
        },
    },
    ignores: ['**/*.md/**'],
};
const eslintConfig = pipe(tseslint.config(...markdownPlugin.configs.recommended, {
    rules: { 'codegen/codegen': 'error' },
}), overrideWith(overrides));
export default eslintConfig;
//# sourceMappingURL=recommended.js.map