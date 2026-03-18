_: let
  nv = (import ./nvpkgs.nix).sympy-mcp;
in
  final: _: {
    sympy-mcp = let
      python = final.python313.withPackages (ps:
        with ps; [
          mcp
          typer
          python-dotenv
          sympy
        ]);

      src = final.fetchFromGitHub {
        owner = "sdiehl";
        repo = "sympy-mcp";
        rev = nv.version;
        inherit (nv.src) sha256;
      };
    in
      final.writeShellApplication {
        name = "sympy-mcp";
        runtimeInputs = [python];
        text = ''
          exec mcp run "${src}/server.py" "$@"
        '';
      };
  }
