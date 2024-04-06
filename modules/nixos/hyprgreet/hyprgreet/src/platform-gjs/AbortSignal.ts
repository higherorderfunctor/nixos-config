import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';
import { HashMap, Option, pipe, ReadonlyArray } from 'effect';

// TODO: https://github.com/DefinitelyTyped/DefinitelyTyped/blob/3dbe8163b4b989f62b85ea671b23f59b2f78cd39/types/node/dom-events.d.ts#L11
interface Event {
  type: string;
}

type EventListener = (evt: Event) => void;

interface EventListenerObject {
  handleEvent(object: Event): void;
}

interface EventListenerOptions {
  capture?: boolean; // not used
}

interface AddEventListenerOptions extends EventListenerOptions {
  once?: boolean;
  passive?: boolean;
  signal?: AbortSignal;
}

const isEventListenerObject = (listener: EventListener | EventListenerObject): listener is EventListenerObject =>
  Object.hasOwn(listener, 'handleEvent');

export class AbortSignal {
  private readonly cancellable: Gio.Cancellable;

  private listeners: HashMap.HashMap<
    EventListener | EventListenerObject,
    HashMap.HashMap<string, { options: AddEventListenerOptions | boolean | undefined }>
  >;

  private throwOnAbort = false;

  reason: unknown = undefined;

  constructor() {
    this.cancellable = Gio.Cancellable.new();
    this.listeners = HashMap.empty();
    this.cancellable.connect(() => {
      const event = { type: 'abort' };
      this.dispatchEvent(event);
      if (this.throwOnAbort) throw new Error('AbortSignal', { cause: this.reason });
    });
  }

  cancel(reason?: unknown) {
    this.reason = reason;
    this.cancellable.cancel();
  }

  get aborted(): boolean {
    return this.cancellable.is_cancelled();
  }

  // TODO: implement
  readonly onabort: null | ((this: AbortSignal, event: Event) => unknown) = null;

  throwIfAborted(): void {
    this.throwOnAbort = true;
  }

  addEventListener(
    type: string,
    listener: EventListener | EventListenerObject,
    options?: AddEventListenerOptions | boolean,
  ): void {
    this.listeners = this.listeners.pipe(
      HashMap.get(listener),
      Option.getOrElse(() =>
        HashMap.empty<
          HashMap.HashMap.Key<HashMap.HashMap.Value<typeof this.listeners>>,
          HashMap.HashMap.Value<HashMap.HashMap.Value<typeof this.listeners>>
        >(),
      ),
      HashMap.set(type, { options }),
      (listeners) => HashMap.set(this.listeners, listener, listeners),
    );
  }

  dispatchEvent(event: Event): boolean {
    if (this.aborted) return false;
    HashMap.forEach(this.listeners, (optionsByEventType, listener) => {
      HashMap.forEach(optionsByEventType, (_, eventType) => {
        if (eventType === event.type)
          if (isEventListenerObject(listener)) listener.handleEvent(event);
          else listener(event);
      });
    });
    return true;
  }

  removeEventListener(
    type: string,
    listener: EventListener | EventListenerObject,
    // options?: EventListenerOptions | boolean,
  ): void {
    this.listeners = HashMap.get(this.listeners, listener).pipe(
      Option.map((optionsByEventType) => HashMap.remove(optionsByEventType, type)),
      Option.map((optionsByEventType) => {
        if (HashMap.isEmpty(optionsByEventType)) return HashMap.remove(this.listeners, listener);
        return HashMap.set(this.listeners, listener, optionsByEventType);
      }),
      Option.getOrElse(() => this.listeners),
    );
  }

  static abort = () => {
    const signal = new AbortSignal();
    signal.cancellable.cancel();
    return signal;
  };

  static any = (iterable: Iterable<AbortSignal>) => {
    const signal = new AbortSignal();
    pipe(
      ReadonlyArray.fromIterable(iterable),
      ReadonlyArray.forEach((sig) => {
        signal.addEventListener('abort', () => {
          sig.cancellable.cancel();
        });
      }),
    );
  };

  static timeout = (time: number) => {
    const signal = new AbortSignal();
    return GLib.timeout_add(GLib.PRIORITY_DEFAULT, time, () => {
      signal.cancellable.cancel();
      return GLib.SOURCE_REMOVE;
    });
  };
}
