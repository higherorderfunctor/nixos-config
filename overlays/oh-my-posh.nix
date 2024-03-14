_: (final: prev: {
  oh-my-posh = let
    version = "19.16.0";
    src = final.fetchFromGitHub {
      owner = "jandedobbeleer";
      repo = "oh-my-posh";
      rev = "refs/tags/v${version}";
      # sha256 = lib.fakeHash; # TODO: last tested correct, hash not getting
      # check last update
      sha256 = "sha256-+8AKxbrLZOOML79P8BS4xTqrsXOqceGJyrZ39NL6zRo=";
    };
    # fix version hash
    vendorHash = "sha256-WuPEoDmp/SSf3AqHtYTtMb56PnjZLWr3weZQXEF7pbg=";
    # vendorHash = lib.fakeHash;
    # fix build.Version; ${version} doesn't seem to re-evaluate
    ldflags = [
      "-s"
      "-w"
      "-X github.com/jandedobbeleer/oh-my-posh/src/build.Version=${version}"
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
            # fix version
            meta.changelog = "https://github.com/JanDeDobbeleer/oh-my-posh/releases/tag/v${version}";
          });
    });
})
