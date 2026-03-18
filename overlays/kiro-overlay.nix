_: (final: prev: let
  nvAll = (import ./.nvfetcher/generated.nix) {
    inherit (final) fetchgit fetchurl fetchFromGitHub dockerTools;
  };
  nvCli = nvAll."kiro-cli";
  nvGateway = nvAll."kiro-gateway";
  python = final.python314;
in {
  kiro-cli = prev.kiro-cli.overrideAttrs (attrs: {
    inherit (nvCli) src version;

    nativeBuildInputs = (attrs.nativeBuildInputs or []) ++ [final.makeWrapper];

    postFixup =
      (attrs.postFixup or "")
      + ''
        wrapProgram $out/bin/kiro-cli --set TERM xterm-256color
        wrapProgram $out/bin/kiro-cli-chat \
          --set TERM xterm-256color
      '';

    meta =
      prev.kiro-cli.meta
      // {
        changelog = builtins.replaceStrings [prev.kiro-cli.version] [nvCli.version] prev.kiro-cli.meta.changelog;
      };
  });
  kiro-gateway = let
    pythonEnv = python.withPackages (ps:
      with ps; [
        fastapi
        uvicorn
        httpx
        loguru
        python-dotenv
        tiktoken
      ]);
  in
    final.stdenvNoCC.mkDerivation {
      pname = "kiro-gateway";
      inherit (nvGateway) src version;

      dontBuild = true;

      installPhase = ''
        runHook preInstall

        mkdir -p $out/share/kiro-gateway
        cp -R . $out/share/kiro-gateway

        mkdir -p $out/bin
        cat > $out/bin/kiro-gateway <<EOF
        #!${final.bash}/bin/bash
        set -euo pipefail
        exec ${pythonEnv}/bin/python "$out/share/kiro-gateway/main.py" "\$@"
        EOF
        chmod +x $out/bin/kiro-gateway

        runHook postInstall
      '';

      meta = {
        description = "Proxy API gateway for Kiro IDE & CLI";
        mainProgram = "kiro-gateway";
      };
    };
})
