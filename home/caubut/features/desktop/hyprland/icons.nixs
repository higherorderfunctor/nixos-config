{
  stdenvNoCC,
  lib,
  fetchFromGitHub,
  gtk3,
}:
stdenvNoCC.mkDerivation rec {
  pname = "vivid-icon-themes";
  version = "8b5b05ceae56987048cb7d1b37c8052f937fc67a";

  # TODO: git updater https://github.com/NixOS/nixpkgs/blob/master/pkgs/data/icons/papirus-icon-theme/default.nix

  src = fetchFromGitHub {
    owner = "L4ki";
    repo = "Vivid-Plasma-Themes";
    rev = "8b5b05ceae56987048cb7d1b37c8052f937fc67a";
    sha256 = "0q74wjyrsjyym770i3sqs071bvanwmm727xzv50wk6kzvpyqgi67";
  };

  nativeBuildInputs = [
    gtk3
  ];

  # avoid the makefile which is only for the theme maintainers
  dontBuild = true;

  installPhase = ''
    runHook preInstall

    mkdir -p $out/share/icons
    l
    mv 'Vivid Icons Themes/Vivid-Dark-Icons/' $out/share/icons/vivid-dark-icons
    mv 'Vivid Icons Themes/Vivid-Glassy-Dark-Icons/' $out/share/icons/vivid-glassy-dark-icons

    for theme in $out/share/icons/*; do
      gtk-update-icon-cache $theme
    done

    runHook postInstall
  '';

  meta = with lib; {
    description = "Vivid Plasma Themes For Plasma Desktop";
    homepage = "https://github.com/L4ki/Vivid-Plasma-Themes";
    license = licenses.gpl3Only;
    platforms = platforms.linux;
    maintainers = with maintainers; [L4ki];
  };
}
