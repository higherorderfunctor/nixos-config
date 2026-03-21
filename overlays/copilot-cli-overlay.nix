_: (final: prev: let
  nvAll = (import ./.nvfetcher/generated.nix) {
    inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
  };
  nv = nvAll."github-copilot-cli";
in {
  github-copilot-cli = prev.github-copilot-cli.overrideAttrs (_: {
    version = nv.version;
    src = final.fetchurl {
      url = "https://github.com/github/copilot-cli/releases/download/v${nv.version}/copilot-linux-x64.tar.gz";
      hash = nv.src.outputHash;
    };

    # Workaround: copilot checks its own filename and breaks when
    # wrapProgram renames it to .copilot-wrapped.
    # Use makeWrapper to preserve the "copilot" filename.
    # https://github.com/NixOS/nixpkgs/issues/500198
    nativeBuildInputs = [final.makeBinaryWrapper];
    doInstallCheck = false;
    postInstall = ''
      mkdir -p $out/libexec
      mv $out/bin/copilot $out/libexec/copilot
      makeWrapper $out/libexec/copilot $out/bin/copilot \
        --argv0 copilot \
        --add-flags "--no-auto-update"
    '';
  });
})
