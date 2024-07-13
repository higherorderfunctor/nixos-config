{inputs, ...}: (final: prev: {
  # FIXME: https://github.com/NixOS/nixpkgs/issues/320247
  # ungoogled-chromium = inputs.nixpkgs-f7e10dc9.legacyPackages.${final.system}.ungoogled-chromium;

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
