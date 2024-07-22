_: let
  nv = (import ./nvpkgs.nix).vivid-plasma-themes;
in
  final: _: let
    vivid-icons-themes = final.callPackage final.stdenvNoCC.mkDerivation {
      pname = "vivid-icon-themes";
      inherit (nv) version;

      src = final.fetchFromGitHub {
        inherit (nv.src) rev sha256;
        owner = "L4ki";
        repo = "Vivid-Plasma-Themes";
      };

      nativeBuildInputs = [
        final.gtk3
      ];

      dontBuild = true;

      dontDropIconThemeCache = true;

      installPhase = ''
        runHook preInstall

        set -x
        mkdir -p $out/share/icons
        ls -la
        mv 'Vivid Icons Themes/Vivid-Dark-Icons/' $out/share/icons/Vivid-Dark-Icons
        mv 'Vivid Icons Themes/Vivid-Glassy-Dark-Icons/' $out/share/icons/Vivid-Glassy-Dark-Icons

        # for theme in $out/share/icons/*; do
        #   gtk-update-icon-cache --force $theme
        # done

        runHook postInstall
      '';

      meta = with final.lib; {
        description = "Vivid Plasma Icon Themes";
        homepage = "https://github.com/L4ki/Vivid-Plasma-Themes";
        license = licenses.gpl3Only;
        platforms = platforms.linux;
        maintainers = with maintainers; [L4ki];
      };
    };
  in {
    inherit vivid-icons-themes;
  }
