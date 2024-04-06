import { AbortSignal } from './AbortSignal.js';

export class AbortController {
  readonly signal: AbortSignal;

  constructor() {
    this.signal = new AbortSignal();
  }

  abort(reason?: unknown) {
    this.signal.cancel(reason);
  }
}
