_: let
  nv = (import ./nvpkgs.nix).oh-my-posh;
in
  final: prev: {
    oh-my-posh = let
      inherit (nv) version;
      src = final.fetchFromGitHub {inherit (nv.src) owner repo rev sha256;};
      vendorHash = "sha256-WuPEoDmp/SSf3AqHtYTtMb56PnjZLWr3weZQXEF7pbg=";
      ldflags = [
        "-s"
        "-w"
        "-X github.com/jandedobbeleer/oh-my-posh/src/build.Version=${nv.version}"
        "-X github.com/jandedobbeleer/oh-my-posh/src/build.Date=1970-01-01T00:00:00Z"
      ];
      # skip tests that require internet access
      postPatch = ''
        rm engine/image_test.go \
          engine/migrate_glyphs_test.go \
          segments/nba_test.go
      '';
    in
      prev.oh-my-posh.override
      (_: {
        buildGoModule = args:
          final.buildGo122Module (args
            // {
              inherit version src vendorHash ldflags postPatch;
              meta.changelog = "https://github.com/JanDeDobbeleer/oh-my-posh/releases/tag/${nv.version}";
            });
      });
  }
