_: let
  nv = (import ./nvpkgs.nix).mcp-server-fetch;
in
  final: prev: {
    mcp-server-fetch = final.python313Packages.buildPythonApplication {
      pname = nv.name;
      version = nv.version;
      pyproject = true;

      src = final.fetchurl {
        inherit (nv.src) url sha256;
      };

      build-system = with final.python313Packages; [hatchling];

      dependencies = with final.python313Packages; [
        httpx
        markdownify
        mcp
        protego
        pydantic
        readabilipy
        requests
      ];

      postPatch = ''
        substituteInPlace src/mcp_server_fetch/server.py \
          --replace-fail 'AsyncClient(proxies=' 'AsyncClient(proxy='
      '';

      pythonRelaxDeps = ["httpx"];

      # No tests in sdist
      doCheck = false;
    };
  }
