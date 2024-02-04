// import { handleErrnoException } from './error.js';
import '@girs/gjs';

import { Gio } from '@girs/gio-2.0';
import { GLib } from '@girs/glib-2.0';

import * as Error from '@effect/platform/Error';
import * as FileSystem from '@effect/platform/FileSystem';
import { ReadonlyArray } from 'effect';
import * as Effect from 'effect/Effect';
import { pipe } from 'effect/Function';
import * as Layer from 'effect/Layer';
import * as Option from 'effect/Option';

import { effectify } from '../Effectify.js';
import { handleIOErrorException } from './error.js';

// const handleBadArgument = (method: string) => (err: unknown) =>
//   Error.BadArgument({
//     module: 'FileSystem',
//     method,
//     message: (err as Error).message ?? String(err),
//   });

// == access

const access = (() => {
  Gio._promisify(Gio.File.prototype, 'query_info_async');
  const makeQuery = (attr: string) => (path: string) => ({
    query: attr,
    getAttribute: (fileInfo: Gio.FileInfo): Effect.Effect<never, Error.SystemError, void> => {
      if (!fileInfo.has_attribute(attr))
        return Effect.fail(
          Error.SystemError({
            module: 'FileSystem',
            method: 'access',
            reason: 'NotFound',
            pathOrDescriptor: path,
            message: `Attribute missing: ${attr}`,
          }),
        );
      if (!fileInfo.get_attribute_boolean(attr))
        return Effect.fail(
          Error.SystemError({
            module: 'FileSystem',
            method: 'access',
            reason: 'PermissionDenied',
            pathOrDescriptor: path,
            message: `Permission denied: ${attr}`,
          }),
        );
      return Effect.unit;
    },
  });
  const canRead = makeQuery(Gio.FILE_ATTRIBUTE_ACCESS_CAN_READ);
  const canWrite = makeQuery(Gio.FILE_ATTRIBUTE_ACCESS_CAN_WRITE);
  return (path: string, options?: FileSystem.AccessFileOptions) =>
    pipe(
      [
        options?.readable && options.readable ? Option.some(canRead(path)) : Option.none(),
        options?.writable && options.writable ? Option.some(canWrite(path)) : Option.none(),
      ],
      ReadonlyArray.getSomes,
      ReadonlyArray.reduce(
        {
          query: '',
          hasAttributes: (_: Gio.FileInfo) => Effect.unit as Effect.Effect<never, Error.SystemError, void>,
        },
        ({ hasAttributes, query }, attr) => ({
          query: `${query},${attr.query}`,
          hasAttributes: (fileInfo: Gio.FileInfo) =>
            hasAttributes(fileInfo).pipe(Effect.flatMap(() => attr.getAttribute(fileInfo))),
        }),
      ),
      ({ hasAttributes, query }) =>
        Effect.tryPromise({
          try: (signal) => {
            const cancellable = Gio.Cancellable.new();
            signal.addEventListener('abort', () => {
              cancellable.cancel();
            });
            return Gio.File.new_for_path(path).query_info_async(
              query,
              Gio.FileQueryInfoFlags.NONE,
              GLib.PRIORITY_DEFAULT,
              cancellable,
            );
          },
          catch: (error) => error, // TODO:
        }).pipe(Effect.flatMap(hasAttributes)),
    );
})();

// // == copy
//
// const copyDirectory = (srcDir, destDir) => {
//   const srcFile = Gio.File.new_for_path(srcDir);
//   const destFile = Gio.File.new_for_path(destDir);
//
//   try {
//     if (!destFile.query_exists(null)) {
//       destFile.make_directory_with_parents(null);
//     }
//
//     const enumerator = srcFile.enumerate_children('standard::name,standard::type', Gio.FileQueryInfoFlags.NONE, null);
//     let fileInfo;
//
//     while ((fileInfo = enumerator.next_file(null)) !== null) {
//       const childSrcFile = srcFile.get_child(fileInfo.get_name());
//       const childDestFile = destFile.get_child(fileInfo.get_name());
//
//       if (fileInfo.get_file_type() === Gio.FileType.DIRECTORY) {
//         copyDirectory(childSrcFile.get_path(), childDestFile.get_path());
//       } else {
//         childSrcFile.copy(childDestFile, Gio.FileCopyFlags.NONE, null, null);
//       }
//     }
//   } catch (e) {
//     print(`Failed to copy directory: ${e.message}`);
//   }
// };
// const copy = (() => {
//   Gio._promisify(Gio.File.prototype, 'copy');
//   return (fromPath: string, toPath: string, options?: FileSystem.CopyOptions) =>
//     Effect.tryPromise({
//       try: (signal) => {
//         const cancellable = Gio.Cancellable.new();
//         signal.addEventListener('abort', () => {
//           cancellable.cancel();
//         });
//         // TODO: error boolean
//         return Gio.File.new_for_path(fromPath).copy_async(
//           Gio.File.new_for_path(toPath),
//           (options?.overwrite ? Gio.FileCopyFlags.OVERWRITE : Gio.FileCopyFlags.NONE) |
//             (options?.preserveTimestamps ? Gio.FileCopyFlags.ALL_METADATA : Gio.FileCopyFlags.NONE), // TODO:
//           GLib.PRIORITY_DEFAULT,
//           cancellable,
//           null,
//         );
//       },
//       catch: (error) => error,
//     });
// })();
//
// // // == copyFile
// //
// // const copyFile = (() => {
// //   const nodeCopyFile = effectify(
// //     NFS.copyFile,
// //     handleErrnoException('FileSystem', 'copyFile'),
// //     handleBadArgument('copyFile'),
// //   );
// //   return (fromPath: string, toPath: string) => nodeCopyFile(fromPath, toPath);
// // })();

// == chmod

const chmod = (path: string, mode: number) => {
  const file = Gio.File.new_for_path(path);
  const cancellable = Gio.Cancellable.new();
  return Effect.tryPromise({
    try: (signal) => {
      signal.addEventListener('abort', () => {
        cancellable.cancel();
      });
      return file.query_info_async('unix::mode', Gio.FileQueryInfoFlags.NONE, GLib.PRIORITY_DEFAULT, cancellable);
    },
    catch: handleIOErrorException('FileSystem', 'readFile', path),
  }).pipe(
    Effect.map((info) => {
      info.set_attribute_uint32('unix::mode', mode);
      return info;
    }),
    Effect.flatMap((info) =>
      Effect.tryPromise({
        try: async (signal) => {
          signal.addEventListener('abort', () => {
            cancellable.cancel();
          });
          file.set_attributes_from_info(info, Gio.FileQueryInfoFlags.NONE, null);
        },
        catch: handleIOErrorException('FileSystem', 'readFile', path),
      }),
    ),
  );
};
// changePermissions('/path/to/file', 0o755);
// // const chmod = (() => {
// //   const nodeChmod = effectify(NFS.chmod, handleErrnoException('FileSystem', 'chmod'), handleBadArgument('chmod'));
// //   return (path: string, mode: number) => nodeChmod(path, mode);
// // })();
// //
// // // == chown
// //
// const changeOwnerGroup = (filePath, ownerId, groupId) => {
//   const file = Gio.File.new_for_path(filePath);
//
//   try {
//     const info = file.query_info('unix::uid,unix::gid', Gio.FileQueryInfoFlags.NONE, null);
//     info.set_attribute_uint32('unix::uid', ownerId);
//     info.set_attribute_uint32('unix::gid', groupId);
//     file.set_attributes_from_info(info, Gio.FileQueryInfoFlags.NONE, null);
//   } catch (e) {
//     print(`Failed to change owner/group: ${e.message}`);
//   }
// };
// const chown = (() => {
//   const nodeChown = effectify(NFS.chown, handleErrnoException('FileSystem', 'chown'), handleBadArgument('chown'));
//   return (path: string, uid: number, gid: number) => nodeChown(path, uid, gid);
// })();
//
// // == link
//
// const link = (() => {
//   const nodeLink = effectify(NFS.link, handleErrnoException('FileSystem', 'link'), handleBadArgument('link'));
//   return (existingPath: string, newPath: string) => nodeLink(existingPath, newPath);
// })();

// == makeDirectory

// const makeDirectory = (() => {
//   const nodeMkdir = effectify(
//     NFS.mkdir,
//     handleErrnoException('FileSystem', 'makeDirectory'),
//     handleBadArgument('makeDirectory'),
//   );
//   return (path: string, options?: FileSystem.MakeDirectoryOptions) =>
//     nodeMkdir(path, {
//       recursive: options?.recursive ?? false,
//       mode: options?.mode,
//     });
// })();
//
Gio._promisify(Gio.File.prototype, 'make_directory_async');

const makeDirectory = (path: string, options?: FileSystem.MakeDirectoryOptions) => {
  const file = Gio.File.new_for_path(path);
  file.make_directory_async(io_priority, cancellable, callback);
  if (options?.recursive) {
    const result = file.make_directory_with_parents(path, options.mode ?? 0o755);
    if (result === 0) {
      return Effect.unit;
    }
    const message = GLib.strerror(errno);
    const code = Gio.io_error_from_errno(errno);
    return Effect.fail(
      handleIOErrorException(
        'FileSystem',
        'makeDirectory',
        path,
      )(GLib.Error.new_literal(Gio.io_error_quark(), code, message)),
    );
  }
  return Effect.tryPromise({
    try: (signal) => {
      const cancellable = Gio.Cancellable.new();
      signal.addEventListener('abort', () => {
        cancellable.cancel();
      });
      return file.make_directory_async(GLib.PRIORITY_DEFAULT, cancellable);
    },
    catch: handleIOErrorException('FileSystem', 'makeDirectory', path),
  }).pipe(Effect.flatMap(() => (options?.mode ? chmod(path, options.mode) : Effect.unit)));
};

// == makeTempDirectory

const makeTempDirectoryFactory = (method: string) => (options?: FileSystem.MakeTempDirectoryOptions) => {
  const path = options?.directory ? options.directory : GLib.get_tmp_dir();
  const tmpDir = `${path}/${options?.prefix ?? ''}${GLib.random_int().toString(16)}`;

  // logError(new globalThis.Error(), tmpDir);
  return makeDirectory(tmpDir).pipe(
    Effect.mapBoth({
      onFailure: (error) =>
        Error.SystemError({
          reason: error.reason,
          module: error.module,
          method,
          pathOrDescriptor: tmpDir,
          message: error.message,
        }),
      onSuccess: () => tmpDir,
    }),
  );
};

const makeTempDirectory = makeTempDirectoryFactory('makeTempDirectory');

// == remove

Gio._promisify(Gio.FileEnumerator.prototype, 'next_files_async');
Gio._promisify(Gio.FileEnumerator.prototype, 'close_async');
Gio._promisify(Gio.File.prototype, 'enumerate_children_async');
Gio._promisify(Gio.File.prototype, 'delete_async');

const enumerateChildrenFactory =
  (method: string) =>
  (path: string, batchSize = 1) => {
    const cancellable = Gio.Cancellable.new();
    const dir = Gio.File.new_for_path(path);
    return Effect.tryPromise({
      try: (signal) => {
        signal.addEventListener('abort', () => {
          cancellable.cancel();
        });
        return dir.enumerate_children_async(
          'standard::*',
          Gio.FileQueryInfoFlags.NONE,
          GLib.PRIORITY_DEFAULT,
          cancellable,
        );
      },
      catch: handleIOErrorException('FileSystem', method, path),
    }).pipe(
      Effect.flatMap((enumerator) =>
        Effect.iterate(
          { enumerator, acc: [] as Gio.FileInfo[] },
          {
            while: ({ enumerator }) => enumerator !== null,
            body: ({ acc, enumerator }) => {
              if (enumerator === null) return Effect.succeed({ enumerator, acc });
              return Effect.tryPromise({
                try: (signal) => {
                  signal.addEventListener('abort', () => {
                    cancellable.cancel();
                  });
                  return enumerator.next_files_async(batchSize, GLib.PRIORITY_DEFAULT, cancellable);
                },
                catch: handleIOErrorException('FileSystem', method, path),
              }).pipe(
                Effect.flatMap((files) => {
                  if (files.length === 0)
                    return Effect.tryPromise({
                      try: (signal) => {
                        signal.addEventListener('abort', () => {
                          cancellable.cancel();
                        });
                        return enumerator.close_async(GLib.PRIORITY_DEFAULT, cancellable);
                      },
                      catch: handleIOErrorException('FileSystem', method, path),
                    }).pipe(Effect.map(() => ({ enumerator: null as Gio.FileEnumerator | null, acc })));
                  return Effect.succeed({ enumerator, acc: [...acc, ...files] });
                }),
              );
            },
          },
        ),
      ),
      Effect.map(({ acc }) => acc),
    );
  };

const removeFactory =
  (method: string) =>
  (path: string, options?: FileSystem.RemoveOptions): Effect.Effect<never, Error.SystemError, void> => {
    const file = Gio.File.new_for_path(path);
    const cancellable = Gio.Cancellable.new();
    return Effect.tryPromise({
      try: (signal) => {
        signal.addEventListener('abort', () => {
          cancellable.cancel();
        });
        return Gio.File.new_for_path(path).query_info_async(
          Gio.FILE_ATTRIBUTE_UNIX_MODE,
          Gio.FileQueryInfoFlags.NONE,
          GLib.PRIORITY_DEFAULT,
          cancellable,
        );
      },
      catch: handleIOErrorException('FileSystem', method, path),
    }).pipe(
      Effect.flatMap((fileInfo) => {
        const stMode = fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_MODE);
        const S_IFDIR = 0x4000;
        if (stMode & S_IFDIR) {
          return enumerateChildrenFactory(method)(path).pipe(
            Effect.flatMap((children) =>
              Effect.all(
                children.map((child) => {
                  const childPath = file.get_child(child.get_name()).get_path();
                  if (childPath) return removeFactory(method)(childPath, options);
                  return Effect.unit;
                }),
              ),
            ),
            Effect.flatMap(() =>
              Effect.tryPromise({
                try: (signal) => {
                  signal.addEventListener('abort', () => {
                    cancellable.cancel();
                  });
                  return file.delete_async(GLib.PRIORITY_DEFAULT, cancellable);
                },
                catch: handleIOErrorException('FileSystem', method, path),
              }),
            ),
          );
        }
        return Effect.tryPromise({
          try: (signal) => {
            signal.addEventListener('abort', () => {
              cancellable.cancel();
            });
            return file.delete_async(GLib.PRIORITY_DEFAULT, cancellable);
          },
          catch: handleIOErrorException('FileSystem', method, path),
        });
      }),
    );
  };

const remove = removeFactory('remove');

// == makeTempDirectoryScoped

const makeTempDirectoryScoped = (() => {
  const makeDirectory = makeTempDirectoryFactory('makeTempDirectoryScoped');
  // const removeDirectory = removeFactory('makeTempDirectoryScoped');
  return (options?: FileSystem.MakeTempDirectoryOptions) =>
    Effect.acquireRelease(
      makeDirectory(options),
      (directory) => Effect.unit, // Effect.orDie(removeDirectory(directory, { recursive: true })),
    );
})();
//
// // == open
//
// const openFactory = (method: string) => {
//   const nodeOpen = effectify(NFS.open, handleErrnoException('FileSystem', method), handleBadArgument(method));
//   const nodeClose = effectify(NFS.close, handleErrnoException('FileSystem', method), handleBadArgument(method));
//
//   return (path: string, options?: FileSystem.OpenFileOptions) =>
//     pipe(
//       Effect.acquireRelease(nodeOpen(path, options?.flag ?? 'r', options?.mode), (fd) => Effect.orDie(nodeClose(fd))),
//       Effect.map((fd) => makeFile(FileSystem.FileDescriptor(fd), options?.flag?.startsWith('a') ?? false)),
//     );
// };
// const open = openFactory('open');
//
// const makeFile = (() => {
//   const nodeReadFactory = (method: string) =>
//     effectify(NFS.read, handleErrnoException('FileSystem', method), handleBadArgument(method));
//   const nodeRead = nodeReadFactory('read');
//   const nodeReadAlloc = nodeReadFactory('readAlloc');
//   const nodeStat = effectify(NFS.fstat, handleErrnoException('FileSystem', 'stat'), handleBadArgument('stat'));
//   const nodeTruncate = effectify(
//     NFS.ftruncate,
//     handleErrnoException('FileSystem', 'truncate'),
//     handleBadArgument('truncate'),
//   );
//
//   const nodeWriteFactory = (method: string) =>
//     effectify(NFS.write, handleErrnoException('FileSystem', method), handleBadArgument(method));
//   const nodeWrite = nodeWriteFactory('write');
//   const nodeWriteAll = nodeWriteFactory('writeAll');
//
//   class FileImpl implements FileSystem.File {
//     readonly [FileSystem.FileTypeId]: FileSystem.FileTypeId;
//
//     private readonly semaphore = Effect.unsafeMakeSemaphore(1);
//     private position: bigint = 0n;
//
//     constructor(
//       readonly fd: FileSystem.File.Descriptor,
//       private readonly append: boolean,
//     ) {
//       this[FileSystem.FileTypeId] = FileSystem.FileTypeId;
//     }
//
//     get stat() {
//       return Effect.map(nodeStat(this.fd), makeFileInfo);
//     }
//
//     seek(offset: FileSystem.SizeInput, from: FileSystem.SeekMode) {
//       const offsetSize = FileSystem.Size(offset);
//       return this.semaphore.withPermits(1)(
//         Effect.sync(() => {
//           if (from === 'start') {
//             this.position = offsetSize;
//           } else if (from === 'current') {
//             this.position = this.position + offsetSize;
//           }
//
//           return this.position;
//         }),
//       );
//     }
//
//     read(buffer: Uint8Array) {
//       return this.semaphore.withPermits(1)(
//         Effect.map(
//           Effect.suspend(() =>
//             nodeRead(this.fd, {
//               buffer,
//               position: this.position,
//             }),
//           ),
//           (bytesRead) => {
//             const sizeRead = FileSystem.Size(bytesRead);
//             this.position = this.position + sizeRead;
//             return sizeRead;
//           },
//         ),
//       );
//     }
//
//     readAlloc(size: FileSystem.SizeInput) {
//       const sizeNumber = Number(size);
//       return this.semaphore.withPermits(1)(
//         Effect.flatMap(
//           Effect.sync(() => Buffer.allocUnsafeSlow(sizeNumber)),
//           (buffer) =>
//             Effect.map(
//               nodeReadAlloc(this.fd, {
//                 buffer,
//                 position: this.position,
//               }),
//               (bytesRead): Option.Option<Buffer> => {
//                 if (bytesRead === 0) {
//                   return Option.none();
//                 }
//
//                 this.position = this.position + BigInt(bytesRead);
//                 if (bytesRead === sizeNumber) {
//                   return Option.some(buffer);
//                 }
//
//                 const dst = Buffer.allocUnsafeSlow(bytesRead);
//                 buffer.copy(dst, 0, 0, bytesRead);
//                 return Option.some(dst);
//               },
//             ),
//         ),
//       );
//     }
//
//     truncate(length?: FileSystem.SizeInput) {
//       return this.semaphore.withPermits(1)(
//         Effect.map(nodeTruncate(this.fd, length ? Number(length) : undefined), () => {
//           if (!this.append) {
//             const len = BigInt(length ?? 0);
//             if (this.position > len) {
//               this.position = len;
//             }
//           }
//         }),
//       );
//     }
//
//     write(buffer: Uint8Array) {
//       return this.semaphore.withPermits(1)(
//         Effect.map(
//           Effect.suspend(() =>
//             nodeWrite(this.fd, buffer, undefined, undefined, this.append ? undefined : Number(this.position)),
//           ),
//           (bytesWritten) => {
//             const sizeWritten = FileSystem.Size(bytesWritten);
//             if (!this.append) {
//               this.position = this.position + sizeWritten;
//             }
//
//             return sizeWritten;
//           },
//         ),
//       );
//     }
//
//     private writeAllChunk(buffer: Uint8Array): Effect.Effect<never, Error.PlatformError, void> {
//       return Effect.flatMap(
//         Effect.suspend(() =>
//           nodeWriteAll(this.fd, buffer, undefined, undefined, this.append ? undefined : Number(this.position)),
//         ),
//         (bytesWritten) => {
//           if (bytesWritten === 0) {
//             return Effect.fail(
//               Error.SystemError({
//                 module: 'FileSystem',
//                 method: 'writeAll',
//                 reason: 'WriteZero',
//                 pathOrDescriptor: this.fd,
//                 message: 'write returned 0 bytes written',
//               }),
//             );
//           }
//
//           if (!this.append) {
//             this.position = this.position + BigInt(bytesWritten);
//           }
//
//           return bytesWritten < buffer.length ? this.writeAllChunk(buffer.subarray(bytesWritten)) : Effect.unit;
//         },
//       );
//     }
//
//     writeAll(buffer: Uint8Array) {
//       return this.semaphore.withPermits(1)(this.writeAllChunk(buffer));
//     }
//   }
//
//   return (fd: FileSystem.File.Descriptor, append: boolean): FileSystem.File => new FileImpl(fd, append);
// })();
//
// // == makeTempFile
//
// const makeTempFileFactory = (method: string) => {
//   const makeDirectory = makeTempDirectoryFactory(method);
//   const open = openFactory(method);
//   const randomHexString = (bytes: number) => Effect.sync(() => Crypto.randomBytes(bytes).toString('hex'));
//   return (options?: FileSystem.MakeTempFileOptions) =>
//     pipe(
//       Effect.zip(makeDirectory(options), randomHexString(6)),
//       Effect.map(([directory, random]) => Path.join(directory, random)),
//       Effect.tap((path) => Effect.scoped(open(path, { flag: 'w+' }))),
//     );
// };
// const makeTempFile = makeTempFileFactory('makeTempFile');
//
// // == makeTempFileScoped
//
// const makeTempFileScoped = (() => {
//   const makeFile = makeTempFileFactory('makeTempFileScoped');
//   const removeFile = removeFactory('makeTempFileScoped');
//   return (options?: FileSystem.MakeTempFileOptions) =>
//     Effect.acquireRelease(makeFile(options), (file) => Effect.orDie(removeFile(file)));
// })();
//
// // == readDirectory
//
// const readDirectory = (() => {
//   const nodeReadDirectory = effectify(
//     NFS.readdir,
//     handleErrnoException('FileSystem', 'readDirectory'),
//     handleBadArgument('readDirectory'),
//   );
//
//   return (path: string, options?: FileSystem.ReadDirectoryOptions) =>
//     nodeReadDirectory(path, options) as Effect.Effect<never, Error.PlatformError, ReadonlyArray<string>>;
// })();

// == readFile

// const readFile = (path: string) =>
//  Effect.async<never, Error.PlatformError, Uint8Array>((resume, signal) => {
//    try {
//      NFS.readFile(path, { signal }, (err, data) => {
//        if (err) {
//          resume(Effect.fail(handleErrnoException('FileSystem', 'readFile')(err, [path])));
//        } else {
//          resume(Effect.succeed(data));
//        }
//      });
//    } catch (err) {
//      resume(Effect.fail(handleBadArgument('readFile')(err)));
//    }
//  });

const readFile = (path: string) => {
  const file = Gio.File.new_for_path(path);
  const cancellable = Gio.Cancellable.new();
  const readFile = effectify(Gio.File, 'load_contents_async', handleIOErrorException('FileSystem', 'readFile', path));
  return readFile(file, cancellable).pipe(Effect.map(([contents]) => contents));
};

// == readLink
//
// const readLink = (() => {
//   const nodeReadLink = effectify(
//     NFS.readlink,
//     handleErrnoException('FileSystem', 'readLink'),
//     handleBadArgument('readLink'),
//   );
//   return (path: string) => nodeReadLink(path);
// })();
//
// // == realPath
//
// const realPath = (() => {
//   const nodeRealPath = effectify(
//     NFS.realpath,
//     handleErrnoException('FileSystem', 'realPath'),
//     handleBadArgument('realPath'),
//   );
//   return (path: string) => nodeRealPath(path);
// })();
//
// // == rename
//
// const rename = (() => {
//   const nodeRename = effectify(NFS.rename, handleErrnoException('FileSystem', 'rename'), handleBadArgument('rename'));
//   return (oldPath: string, newPath: string) => nodeRename(oldPath, newPath);
// })();

// == stat

const stat = (path: string) => {
  const file = Gio.File.new_for_path(path);
  return Effect.tryPromise({
    try: (signal) => {
      const cancellable = Gio.Cancellable.new();
      signal.addEventListener('abort', () => {
        cancellable.cancel();
      });
      return Gio.File.new_for_path(path).query_info_async(
        ['standard::*', Gio.FILE_ATTRIBUTE_UNIX_MODE].join(','),
        Gio.FileQueryInfoFlags.NONE,
        GLib.PRIORITY_DEFAULT,
        cancellable,
      );
    },
    catch: handleIOErrorException('FileSystem', 'stat', path),
  }).pipe(
    Effect.map(
      (fileInfo): FileSystem.File.Info => ({
        // type: Type fileInfo.
        type: (() => {
          const stMode = fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_MODE);
          const S_IFIFO = 0x1000;
          const S_IFCHR = 0x2000;
          const S_IFDIR = 0x4000;
          const S_IFBLK = 0x6000;
          const S_IFREG = 0x8000;
          const S_IFLNK = 0xa000;
          const S_IFSOCK = 0xc000;
          if (stMode & S_IFIFO) return 'FIFO';
          if (stMode & S_IFCHR) return 'CharacterDevice';
          if (stMode & S_IFDIR) return 'Directory';
          if (stMode & S_IFBLK) return 'BlockDevice';
          if (stMode & S_IFREG) return 'File';
          if (stMode & S_IFLNK) return 'SymbolicLink';
          if (stMode & S_IFSOCK) return 'Socket';
          return 'Unknown';
        })(),

        mtime: Option.fromNullable(fileInfo.get_modification_date_time()?.to_unix()).pipe(
          Option.map((epoch) => new Date(epoch)),
        ),
        atime: Option.fromNullable(fileInfo.get_access_date_time()?.to_unix()).pipe(
          Option.map((epoch) => new Date(epoch)),
        ),
        birthtime: Option.fromNullable(fileInfo.get_creation_date_time()?.to_unix()).pipe(
          Option.map((epoch) => new Date(epoch)),
        ),
        dev: fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_DEVICE),
        ino: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_INODE)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(uid))),
        ),
        mode: fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_MODE) & 0x777,
        nlink: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_NLINK)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(uid))),
        ),
        uid: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_UID)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(uid))),
        ),
        gid: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_GID)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(uid))),
        ),
        rdev: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_RDEV)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(uid))),
        ),
        size: FileSystem.Size(fileInfo.get_attribute_uint64(Gio.FILE_ATTRIBUTE_FILESYSTEM_SIZE)),
        blksize: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_BLOCK_SIZE)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(FileSystem.Size(uid)))),
        ),
        blocks: Option.some(fileInfo.get_attribute_uint32(Gio.FILE_ATTRIBUTE_UNIX_BLOCKS)).pipe(
          Option.flatMap((uid) => (uid === 0 ? Option.none() : Option.some(uid))),
        ),
      }),
    ),
  );
};
// const makeFileInfo = (stat: NFS.Stats): FileSystem.File.Info => ({
//   type: stat.isFile()
//     ? 'File'
//     : stat.isDirectory()
//       ? 'Directory'
//       : stat.isSymbolicLink()
//         ? 'SymbolicLink'
//         : stat.isBlockDevice()
//           ? 'BlockDevice'
//           : stat.isCharacterDevice()
//             ? 'CharacterDevice'
//             : stat.isFIFO()
//               ? 'FIFO'
//               : stat.isSocket()
//                 ? 'Socket'
//                 : 'Unknown',
//   mtime: Option.fromNullable(stat.mtime),
//   atime: Option.fromNullable(stat.atime),
//   birthtime: Option.fromNullable(stat.birthtime),
//   dev: stat.dev,
//   rdev: Option.fromNullable(stat.rdev),
//   ino: Option.fromNullable(stat.ino),
//   mode: stat.mode,
//   nlink: Option.fromNullable(stat.nlink),
//   uid: Option.fromNullable(stat.uid),
//   gid: Option.fromNullable(stat.gid),
//   size: FileSystem.Size(stat.size),
//   blksize: Option.fromNullable(FileSystem.Size(stat.blksize)),
//   blocks: Option.fromNullable(stat.blocks),
// });
// const stat = (() => {
//   const nodeStat = effectify(NFS.stat, handleErrnoException('FileSystem', 'stat'), handleBadArgument('stat'));
//   return (path: string) => Effect.map(nodeStat(path), makeFileInfo);
// })();
//
// // == symlink
//
// const symlink = (() => {
//   const nodeSymlink = effectify(
//     NFS.symlink,
//     handleErrnoException('FileSystem', 'symlink'),
//     handleBadArgument('symlink'),
//   );
//   return (target: string, path: string) => nodeSymlink(target, path);
// })();
//
// // == truncate
//
// const truncate = (() => {
//   const nodeTruncate = effectify(
//     NFS.truncate,
//     handleErrnoException('FileSystem', 'truncate'),
//     handleBadArgument('truncate'),
//   );
//   return (path: string, length?: FileSystem.SizeInput) =>
//     nodeTruncate(path, length !== undefined ? Number(length) : undefined);
// })();
//
// // == utimes
//
// const utimes = (() => {
//   const nodeUtimes = effectify(NFS.utimes, handleErrnoException('FileSystem', 'utime'), handleBadArgument('utime'));
//   return (path: string, atime: number | Date, mtime: number | Date) => nodeUtimes(path, atime, mtime);
// })();
//
// // == writeFile
//
// const writeFile = (path: string, data: Uint8Array, options?: FileSystem.WriteFileOptions) =>
//   Effect.async<never, Error.PlatformError, void>((resume, signal) => {
//     try {
//       NFS.writeFile(
//         path,
//         data,
//         {
//           signal,
//           flag: options?.flag,
//           mode: options?.mode,
//         },
//         (err) => {
//           if (err) {
//             resume(Effect.fail(handleErrnoException('FileSystem', 'writeFile')(err, [path])));
//           } else {
//             resume(Effect.unit);
//           }
//         },
//       );
//     } catch (err) {
//       resume(Effect.fail(handleBadArgument('writeFile')(err)));
//     }
//   });
//
const fileSystemImpl = FileSystem.make({
  access,
  chmod,
  //   chown,
  //   copy,
  //   copyFile,
  //   link,
  makeDirectory,
  makeTempDirectory,
  makeTempDirectoryScoped,
  //   makeTempFile,
  //   makeTempFileScoped,
  //   open,
  //   readDirectory,
  readFile,
  //   readLink,
  //   realPath,
  remove,
  //   rename,
  stat,
  //   symlink,
  //   truncate,
  //   utimes,
  //   writeFile,
});

/** @internal */
export const layer = Layer.succeed(FileSystem.FileSystem, fileSystemImpl);
