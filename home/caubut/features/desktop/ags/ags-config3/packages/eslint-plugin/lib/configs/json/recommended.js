"use strict";
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
var eslint_plugin_jsonc_1 = require("eslint-plugin-jsonc");
var eslint_plugin_prettier_1 = require("eslint-plugin-prettier");
var recommended_1 = require("eslint-plugin-prettier/recommended");
var jsonc_eslint_parser_1 = require("jsonc-eslint-parser");
var typescript_eslint_1 = require("typescript-eslint");
var overrideHelpers_js_1 = require("../../overrideHelpers.js");
var plugins = {
    jsonc: eslint_plugin_jsonc_1.default,
    prettier: eslint_plugin_prettier_1.default,
};
var overrides = {
    plugins: plugins,
    languageOptions: {
        parser: jsonc_eslint_parser_1.default,
    },
};
var eslintConfig = (0, effect_1.pipe)(typescript_eslint_1.default.config.apply(typescript_eslint_1.default, __spreadArray(__spreadArray([recommended_1.default], eslint_plugin_jsonc_1.default.configs['flat/prettier'], false), eslint_plugin_jsonc_1.default.configs['flat/recommended-with-jsonc'], false)), (0, overrideHelpers_js_1.overrideWith)(overrides));
exports.default = eslintConfig;
