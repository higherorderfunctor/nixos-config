_: final: prev: let
  inherit (final) lib;
  nv = (import ./nvpkgs.nix).oh-my-posh;
  dropFirstChar = s: builtins.substring 1 (builtins.stringLength s) s;
  replaceVersion = flag:
    if lib.strings.hasInfix "build.Version" flag
    then
      lib.strings.concatStringsSep "=" [
        (builtins.head (lib.splitString "=" flag))
        version
      ]
    else flag;
  version = dropFirstChar nv.version;
  src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
  vendorHash =
    if lib.hasAttr "vendorHash" nv
    then nv.vendorHash
    else lib.fakeHash;
in {
  oh-my-posh =
    prev.oh-my-posh.override
    (_: {
      buildGoModule = orig:
        final.buildGo122Module (orig
          // {
            inherit version src vendorHash;

            ldflags = builtins.map replaceVersion orig.ldflags;

            postPatch = ''
              rm engine/image_test.go \
                engine/migrate_glyphs_test.go \
                segments/nba_test.go
            '';

            meta.changelog = "https://github.com/JanDeDobbeleer/oh-my-posh/releases/tag/v${nv.version}";
          });
    });
}
