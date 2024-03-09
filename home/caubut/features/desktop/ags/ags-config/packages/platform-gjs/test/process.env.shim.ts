import { version } from '@girs/gjs/system';

globalThis.process = {
  versions: { gjs: version },
  env: {},
};
