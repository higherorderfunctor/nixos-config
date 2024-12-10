import jsonRecommended from './configs/json/recommended.js';
import markdownRecommended from './configs/markdown/recommended.js';
import recommended from './configs/recommended.js';
import strict from './configs/strict.js';
import { overrideWith } from './overrideHelpers.js';
export default {
    configs: {
        recommended,
        strict,
        ...{
            'json/recommended': jsonRecommended,
            'markdown/recommended': markdownRecommended,
        },
    },
    overrideWith,
};
//# sourceMappingURL=index.js.map