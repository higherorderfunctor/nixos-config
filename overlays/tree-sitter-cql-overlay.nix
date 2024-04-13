_: (final: prev: let
  nv = (import ./nvpkgs.nix).tree-sitter-cql;
in {
  # https://github.com/shotover/tree-sitter-cql/tree/main
  # https://github.com/nix-community/nixvim/discussions/540
  tree-sitter-grammars.tree-sitter-cql = final.tree-sitter.buildGrammar {
    inherit (nv) version;
    language = "cql";
    src = final.fetchFromGitHub {
      inherit (nv.src) owner repo rev sha256;
    };
  };
  # tree-sitter = prev.tree-sitter.override {
  #   extraGrammars.tree-sitter-cql = final.tree-sitter-grammars.tree-sitter-cql;
  # };
})
