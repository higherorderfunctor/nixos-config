{inputs, ...}: inputs.neovim-nightly-overlay.overlays.default

# {inputs, ...}: final: _: {
#   neovim = inputs.neovim-nightly-overlay.packages.${final.system}.neovim.override (args: {
#     tree-sitter = args.tree-sitter.override {
#       rustPlatform =
#         final.rustPlatform
#         // {
#           buildRustPackage = args:
#             final.rustPlatform.buildRustPackage (
#               args
#               // {
#                 cargoHash = "sha256-wrMqeJxOj9Jp3luy6ir6UzNQClRglqP8pfoqWk+Ky+w=";
#               }
#             );
#         };
#     };
#   });
# }
