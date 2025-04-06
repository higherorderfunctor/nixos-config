_: final: prev: let
  nv = (import ./nvpkgs.nix).amdvlk;
in {
  amdvlk = prev.amdvlk.overrideAttrs (attrs: {
    inherit (nv) version;
    src = final.fetchRepoProject {
      inherit (attrs.src) name;
      inherit (nv.src) rev;
      sha256 = "sha256-kNGJWuWN2B4hEyRz2JFGSE8TiIdxujBOxF/T6nNek0A=";
      manifest = "https://github.com/GPUOpen-Drivers/AMDVLK.git";
    };
  });
}
