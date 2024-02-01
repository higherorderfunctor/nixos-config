const global = globalThis as typeof globalThis & {
  process: { env: Record<string, string>; versions: { gjs: number } };
};

global.process = { versions: { gjs: imports.system.version }, env: {} };
