_: (final: prev: let
  systemMap = {
    x86_64-linux = "linux-amd64";
    aarch64-linux = "linux-arm64";
  };
  nv = (import ./nvpkgs.nix)."standardnotes-${systemMap.${final.system}}-deb";
in {
  standardnotes = (prev.standardnotes.override {electron = final.electron_27;}).overrideAttrs (attrs: {
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
