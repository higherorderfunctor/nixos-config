{
  stdenvNoCC,
  lib,
  fetchFromGitHub,
  gtk3,
  gitUpdater,
}:
stdenvNoCC.mkDerivation {
  pname = "vivid-icon-themes";
  version = "2024-03-09-2";

  src = fetchFromGitHub {
    owner = "L4ki";
    repo = "Vivid-Plasma-Themes";
    rev = "8b5b05ceae56987048cb7d1b37c8052f937fc67a";
    sha256 = "sha256-U+jCoaPDV+iexk+ub0wwFRXI3tAQVrvbUZ+ZZPCxcxA=";
  };

  nativeBuildInputs = [
    gtk3
  ];

  # avoid the makefile which is only for the theme maintainers
  dontBuild = true;

  dontDropIconThemeCache = true;

  installPhase = ''
    runHook preInstall

    mkdir -p $out/share/icons
    ls -la
    mv 'Vivid Icons Themes/Vivid-Dark-Icons/' $out/share/icons/Vivid-Dark-Icons
    mv 'Vivid Icons Themes/Vivid-Glassy-Dark-Icons/' $out/share/icons/Vivid-Glassy-Dark-Icons

    for theme in $out/share/icons/*; do
      gtk-update-icon-cache --force $theme
    done

    runHook postInstall
  '';

  # TODO: make work
  passthru.updateScript = gitUpdater {};

  meta = with lib; {
    description = "Vivid Plasma Themes For Plasma Desktop";
    homepage = "https://github.com/L4ki/Vivid-Plasma-Themes";
    license = licenses.gpl3Only;
    platforms = platforms.linux;
    maintainers = with maintainers; [L4ki];
  };
}
