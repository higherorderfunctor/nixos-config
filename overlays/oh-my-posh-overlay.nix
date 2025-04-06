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
  buildGoModule =
    #let
    # nv = (import ./nvpkgs.nix).go;
    # go = final.go.overrideAttrs {
    #   inherit (nv) version;
    #   src = final.fetchurl {
    #     inherit (nv.src) url sha256;
    #   };
    # };
    # in
    final.buildGoModule.override {inherit (final) go;};
in {
  oh-my-posh =
    prev.oh-my-posh.override
    {
      buildGoModule = orig:
        buildGoModule (orig
          // {
            inherit version src vendorHash;

            ldflags = builtins.map replaceVersion orig.ldflags;

            postPatch = ''
              rm image/image_test.go \
                 config/migrate_glyphs_test.go \
                 segments/nba_test.go \
                 segments/upgrade_test.go \
                 upgrade/notice_test.go
            '';

            postInstall = ''
              mv $out/bin/{src,oh-my-posh}
              mkdir -p $out/share/oh-my-posh
              cp -r $src/themes $out/share/oh-my-posh/
            '';

            meta.changelog = "https://github.com/JanDeDobbeleer/oh-my-posh/releases/tag/v${nv.version}";
          });
    };
}
