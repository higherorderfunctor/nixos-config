import { Args, Command, Options } from "@effect/cli"
import { NodeContext, NodeRuntime } from "@effect/platform-node"
import { Config, ConfigProvider, Console, Effect, Option, ReadonlyArray } from "effect"

// minigit [--version] [-h | --help] [-c <name>=<value>]
const configs = Options.keyValueMap("c").pipe(Options.optional)
const minigit = Command.make("minigit", { configs }, ({ configs }) =>
  Option.match(configs, {
    onNone: () => Console.log("Running 'minigit'"),
    onSome: (configs) => {
      const keyValuePairs = Array.from(configs)
        .map(([key, value]) => `${key}=${value}`)
        .join(", ")
      return Console.log(`Running 'minigit' with the following configs: ${keyValuePairs}`)
    }
  }))

const command = minigit

const cli = Command.run(command, {
  name: "Effect Gnome Shell",
  version: "v1.0.0"
})

Effect.suspend(() => cli(process.argv)).pipe(
  Effect.withConfigProvider(ConfigProvider.nested(ConfigProvider.fromEnv(), "GIT")),
  Effect.provide(NodeContext.layer),
  NodeRuntime.runMain
)
