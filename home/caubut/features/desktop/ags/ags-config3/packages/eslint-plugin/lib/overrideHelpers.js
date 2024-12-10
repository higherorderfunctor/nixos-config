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
exports.declareGlobals = exports.overrideWith = void 0;
var effect_1 = require("effect");
var Function_1 = require("effect/Function");
exports.overrideWith = (0, Function_1.dual)(2, function (configs, overrides) {
    return configs.map(function (config) {
        var _a;
        return (__assign(__assign(__assign({}, config), overrides), { plugins: __assign(__assign({}, overrides.plugins), ((_a = config.plugins) !== null && _a !== void 0 ? _a : {})) }));
    });
});
var declareGlobals = function (globals) {
    if (effect_1.Array.isEmptyReadonlyArray(globals)) {
        return [];
    }
    return [
        {
            filter: {
                match: true,
                regex: "^(".concat(globals.join('|'), ")$"),
            },
            format: [],
            modifiers: ['const'], // global doesn't work in a `declare global` block
            selector: 'variable',
        },
    ];
};
exports.declareGlobals = declareGlobals;
