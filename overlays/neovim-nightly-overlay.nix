{inputs, ...}: final: _: let
  inherit (final) lib;
in {
  neovim = inputs.neovim-nightly-overlay.packages.${final.stdenv.hostPlatform.system}.neovim
      .override (args: {
    tree-sitter = args.tree-sitter.override {
      rustPlatform =
        final.rustPlatform
        // {
          buildRustPackage = args':
            final.rustPlatform.buildRustPackage (
              finalAttrs: let
                a = (lib.toFunction args') finalAttrs;
              in
                a
                // {
                  # If you need to pin it, set it here:
                  # cargoHash = "sha256-...";
                }
            );
        };
    };
  });
}
