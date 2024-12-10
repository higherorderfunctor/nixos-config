"use strict";
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
Object.defineProperty(exports, "__esModule", { value: true });
var effect_1 = require("effect");
var eslint_plugin_codegen_1 = require("eslint-plugin-codegen");
var eslint_plugin_markdown_1 = require("eslint-plugin-markdown");
var typescript_eslint_1 = require("typescript-eslint");
var overrideHelpers_js_1 = require("../../overrideHelpers.js");
var plugins = {
    markdown: eslint_plugin_markdown_1.default,
    codegen: eslint_plugin_codegen_1.default,
};
var overrides = {
    plugins: plugins,
    processor: __assign(__assign({}, eslint_plugin_codegen_1.processors.processor), { 
        // hack for eslint --cache to work
        meta: {
            name: 'eslint-plugin-codegen-md-processor',
            version: eslint_plugin_markdown_1.default.version,
        } }),
    // TODO: code examples in markdown
    ignores: ['**/*.md/**'],
};
var eslintConfig = (0, effect_1.pipe)(typescript_eslint_1.default.config.apply(typescript_eslint_1.default, __spreadArray(__spreadArray([], eslint_plugin_markdown_1.default.configs.recommended, false), [{
        rules: { 'codegen/codegen': 'error' },
    }], false)), (0, overrideHelpers_js_1.overrideWith)(overrides));
exports.default = eslintConfig;
