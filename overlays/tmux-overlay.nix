_: (final: prev: let
  nv = (import ./nvpkgs.nix)."tmux-which-key";
  inherit (final) python3;
in {
  tmuxPlugins =
    prev.tmuxPlugins
    // {
      tmux-which-key = prev.tmuxPlugins.mkTmuxPlugin {
        pluginName = nv.name;
        inherit (nv) version;
        propagatedBuildInputs = [
          python3
        ];
        src = builtins.fetchGit {
          inherit (nv.src) url rev;
        };
        preInstall = ''
          rm -rf plugin/pyyaml
          cp -r ${python3.pkgs.pyyaml.src} plugin/pyyaml
        '';
        rtpFilePath = "plugin.sh.tmux";
      };
    };
})
