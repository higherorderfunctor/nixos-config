import '@girs/gio-2.0';
import '@girs/glib-2.0';

import Gio from 'gi://Gio';
import GLib from 'gi://GLib';

import type { PlatformError, SystemErrorReason } from '@effect/platform/Error';
import { SystemError } from '@effect/platform/Error';

/** @internal */
const isError = (err: unknown): err is GLib.Error => err instanceof GLib.Error;

const isIOError = (err: unknown): err is GLib.Error & { code: Gio.IOErrorEnum } =>
  isError(err) && err.domain === Gio.io_error_quark()

const
//e.message.match(/(?<=^Error when getting information for file “).*(?=”:)/)

export const handleIOErrorException =
  (module: SystemError['module'], method: string) =>
  (err: unknown, path: string): PlatformError => {
    let reason: SystemErrorReason = 'Unknown';

    if (isError(err)) {
      if (isIOError(err)) {
        err.message

        //     {
        //   reason,
        //   module,
        //   method,
        //   pathOrDescriptor: path,
        //   syscall: undefined, // TODO: err.syscall,
        //   message: '', // err.message
        // }
        switch (err.domain) {
          case Gio.IOErrorEnum.ADDRESS_IN_USE:
            reason = 'AlreadyExists';
            break;

          case Gio.IOErrorEnum.ALREADY_MOUNTED:
            reason = 'AlreadyExists';
            break;

          case Gio.IOErrorEnum.BROKEN_PIPE:
            reason = 'UnexpectedEof';
            break;

          case Gio.IOErrorEnum.BUSY:
            reason = 'Busy';
            break;

          case Gio.IOErrorEnum.CANCELLED:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.CANT_CREATE_BACKUP:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.CLOSED:
            reason = 'UnexpectedEof';
            break;

          case Gio.IOErrorEnum.CONNECTION_CLOSED:
            reason = 'UnexpectedEof';
            break;

          case Gio.IOErrorEnum.CONNECTION_REFUSED:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.DBUS_ERROR:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.EXISTS:
            reason = 'AlreadyExists';
            break;

          case Gio.IOErrorEnum.FAILED:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.FAILED_HANDLED:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.FILENAME_TOO_LONG:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.HOST_NOT_FOUND:
            reason = 'NotFound';
            break;

          case Gio.IOErrorEnum.HOST_UNREACHABLE:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.INVALID_ARGUMENT:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.INVALID_DATA:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.INVALID_FILENAME:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.IS_DIRECTORY:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.MESSAGE_TOO_LARGE:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.NETWORK_UNREACHABLE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NO_SPACE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NO_SUCH_DEVICE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NOT_CONNECTED:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NOT_DIRECTORY:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.NOT_EMPTY:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.NOT_FOUND:
            reason = 'NotFound';
            break;

          case Gio.IOErrorEnum.NOT_INITIALIZED:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NOT_MOUNTABLE_FILE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NOT_MOUNTED:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NOT_REGULAR_FILE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.NOT_SUPPORTED:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.NOT_SYMBOLIC_LINK:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.PARTIAL_INPUT:
            reason = 'InvalidData';
            break;

          case Gio.IOErrorEnum.PENDING:
            reason = 'Busy';
            break;

          case Gio.IOErrorEnum.PERMISSION_DENIED:
            reason = 'PermissionDenied';
            break;

          case Gio.IOErrorEnum.PROXY_AUTH_FAILED:
            reason = 'PermissionDenied';
            break;

          case Gio.IOErrorEnum.PROXY_FAILED:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.PROXY_NEED_AUTH:
            reason = 'PermissionDenied';
            break;

          case Gio.IOErrorEnum.PROXY_NOT_ALLOWED:
            reason = 'PermissionDenied';
            break;

          case Gio.IOErrorEnum.READ_ONLY:
            reason = 'PermissionDenied';
            break;

          case Gio.IOErrorEnum.TIMED_OUT:
            reason = 'TimedOut';
            break;

          case Gio.IOErrorEnum.TOO_MANY_LINKS:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.TOO_MANY_OPEN_FILES:
            reason = 'Unknown';
            break;

          case Gio.IOErrorEnum.WOULD_BLOCK:
            reason = 'WouldBlock';
            break;

          case Gio.IOErrorEnum.WOULD_MERGE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.WOULD_RECURSE:
            reason = 'BadResource';
            break;

          case Gio.IOErrorEnum.WRONG_ETAG:
            reason = 'BadResource';
            break;
        }
        err.
      }
    }

    /*
  readonly method: string
  readonly message: string
  readonly reason: SystemErrorReason
  readonly syscall?: string | undefined
  readonly pathOrDescriptor: string | number
     *
     * */
    return SystemError({
      reason,
      module,
      method,
      pathOrDescriptor: path,
      message: '', // err.message
    });
  };
