# @effect-gtk

```sh
gjs -m dist/esm/index.js
apt-get install gjs libgjs-dev

pnpm --filter @egs/egs build
gjs -m packages/egs/dist/esm/index.js

pnpm run build
gjs -m packages/egs/dist/esm/index.js
```
