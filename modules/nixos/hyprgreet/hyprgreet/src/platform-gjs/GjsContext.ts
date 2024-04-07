/**
 * @since 1.0.0
 */
// import * as NodeCommandExecutor from "@effect/platform-node-shared/NodeCommandExecutor"
// import * as NodePath from "@effect/platform-node-shared/NodePath"
// import * as NodeTerminal from "@effect/platform-node-shared/NodeTerminal"
// import type * as CommandExecutor from "@effect/platform/CommandExecutor"
import type * as FileSystem from '@effect/platform/FileSystem';
// import type * as Path from "@effect/platform/Path"
// import type * as Terminal from "@effect/platform/Terminal"
// import type * as Worker from "@effect/platform/Worker"
import { pipe } from 'effect/Function';
import type * as Layer from 'effect/Layer';

import * as GjsFileSystem from './GjsFileSystem.js';
// import * as NodeWorker from "./NodeWorker.js"

/**
 * @since 1.0.0
 * @category models
 */
export type GjsContext = //  | CommandExecutor.CommandExecutor
  FileSystem.FileSystem;
//  | Path.Path
//  | Terminal.Terminal
//  | Worker.WorkerManager

/**
 * @since 1.0.0
 * @category layer
 */
export const layer: Layer.Layer<GjsContext> = pipe(
  //  Layer.mergeAll(
  //    NodePath.layer,
  //    NodeCommandExecutor.layer,
  //    NodeTerminal.layer,
  //    NodeWorker.layerManager
  //  ),
  // Layer.provideMerge(NodeFileSystem.layer)
  GjsFileSystem.layer,
);
