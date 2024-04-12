_: (final: prev: let
  nv = (import ./nvpkgs.nix)."standardnotes-desktop-deb-${final.system}";
in {
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
