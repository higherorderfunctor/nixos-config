{inputs, ...}: (final: prev: {
  # FIXME: https://hydra.nixos.org/build/265233452
  inherit
    (inputs.nixpkgs-91594d11.legacyPackages.${final.system})
    ungoogled-chromium
    webkitgtk_6_0
    webkitgtk_4_1
    evolution-data-server
    evolution
    networkmanager-openconnect
    gnome-calendar
    gnome-calculator
    ;

  # FIXME: https://github.com/NixOS/nixpkgs/pull/307505
  # https://github.com/NixOS/nixpkgs/pull/307476

  # poetry = inputs.nixpkgs-master.legacyPackages.${final.system}.poetry;

  # poetry = prev.poetry.overrideAttrs (attrs: {
  #   poetry = attrs.poetry.override {
  #     inherit (inputs.nixpkgs-master.legacyPackages.${final.system}.python312Packages) dulwich;
  #   };
  # });

  # poetry = prev.poetry.overrideAttrs (attrs: {
  #   propagatedBuildInputs = let
  #     dulwich = inputs.nixpkgs-master.legacyPackages.${final.system}.python312Packages.dulwich;
  #     filtered = final.lib.filter (pkg: pkg.pname or null != "dulwich") attrs.propagatedBuildInputs;
  #   in
  #     filtered ++ [(builtins.trace dulwich dulwich)];
  # });
  # inherit (inputs.nixpkgs-master.legacyPackages.${final.system}) spamassassin;
})
