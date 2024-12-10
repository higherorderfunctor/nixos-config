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
Object.defineProperty(exports, "__esModule", { value: true });
var recommended_js_1 = require("./configs/json/recommended.js");
var recommended_js_2 = require("./configs/markdown/recommended.js");
var recommended_js_3 = require("./configs/recommended.js");
var strict_js_1 = require("./configs/strict.js");
var overrideHelpers_js_1 = require("./overrideHelpers.js");
exports.default = {
    configs: __assign({ recommended: recommended_js_3.default, strict: strict_js_1.default }, {
        'json/recommended': recommended_js_1.default,
        'markdown/recommended': recommended_js_2.default,
    }),
    overrideWith: overrideHelpers_js_1.overrideWith,
};
