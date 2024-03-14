_: let
  nv = (import ./nvpkgs.nix).oh-my-posh;
in
  final: prev: {
    oh-my-posh = let
      inherit (final) lib;
      inherit (nv) version;
      src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
      vendorHash = "sha256-WuPEoDmp/SSf3AqHtYTtMb56PnjZLWr3weZQXEF7pbg=";
      replaceVersion = flag:
        if lib.strings.hasInfix "build.Version" flag
        then
          lib.strings.concatStringsSep "=" [
            (builtins.head (lib.splitString "=" flag))
            nv.version
          ]
        else flag;
      # skip tests that require internet access
      postPatch = ''
        rm engine/image_test.go \
          engine/migrate_glyphs_test.go \
          segments/nba_test.go
      '';
    in
      prev.oh-my-posh.override
      (_: {
        buildGoModule = orig:
          final.buildGo122Module (orig
            // {
              inherit version src vendorHash postPatch;
              ldflags = builtins.map replaceVersion orig.ldflags;
              meta.changelog = "https://github.com/JanDeDobbeleer/oh-my-posh/releases/tag/${nv.version}";
            });
      });
  }
