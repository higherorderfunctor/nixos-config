{inputs, ...}: final: _: {
  neovim = inputs.neovim-nightly-overlay.packages.${final.system}.neovim.override (args: {
    tree-sitter = args.tree-sitter.override {
      rustPlatform =
        final.rustPlatform
        // {
          buildRustPackage = args:
            final.rustPlatform.buildRustPackage (
              args
              // {
                cargoHash = "sha256-mk3aw1aFu7N+b4AQL5kiaHuIAuJv24KonFeGKid427Q=";
              }
            );
        };
    };
  });
}
