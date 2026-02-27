{inputs, ...}: final: _: {
  neovim = inputs.neovim-nightly-overlay.packages.${final.stdenv.hostPlatform.system}.neovim
      .override (args: {
    tree-sitter = args.tree-sitter.overrideAttrs (attrs: let
      cargoHash = "sha256-u6RmwNR4QVwyuij5RlHTLC5lNNQpWMVrlQwfwF78pYc=";
    in {
      inherit cargoHash;
      cargoDeps = final.rustPlatform.fetchCargoVendor {
        inherit (attrs) src;
        name = "${attrs.pname}-cargo-deps";
        hash = cargoHash;
      };
    });
  });
}
