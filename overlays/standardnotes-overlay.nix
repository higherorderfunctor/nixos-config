{inputs}: (final: prev: let
  nv = (import ./nvpkgs.nix)."standardnotes-desktop-deb-${final.system}";
in {
  # FIXME: https://github.com/NixOS/nixpkgs/issues/302457
  # temporary patch pulled in from master
  inherit
    (inputs.nixpkgs-master.legacyPackages.${final.system})
    electron_27
    electron_28 # 27 in standardnotes builds 27 & 28 for some reason
    ;
  standardnotes =
    (prev.standardnotes.override {
      electron = final.electron_27;
    })
    .overrideAttrs (attrs: {
      inherit (nv) version;

      src = final.fetchurl {
        inherit (nv.src) url sha256;
      };

      unpackPhase = ''
        ${attrs.unpackPhase}
        mv opt/Standard\ Notes opt/standardnotes
      '';

      installPhase =
        builtins.replaceStrings
        ["Standard\\ Notes"]
        ["standardnotes"]
        attrs.installPhase;
    });
})
