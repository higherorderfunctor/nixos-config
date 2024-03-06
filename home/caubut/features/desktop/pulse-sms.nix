{
  lib,
  pkgs,
  ...
}: let
  pname = "pulse-sms";
  version = "4.5.3";
  src = pkgs.fetchurl {
    url = "https://github.com/maplemedia/pulse-sms-desktop/releases/download/v${version}/pulse-sms-${version}-x86_64.AppImage";
    name = "${pname}-${version}.AppImage";
    hash = "sha256-1HJwy2DicWZIIrNXlzzTi/nDPs4Q08NTx3Bs5kV60nE=";
  };
  contents = pkgs.appimageTools.extractType2 {
    name = "${pname}-${version}";
    inherit src;
  };
  pulse-sms = pkgs.stdenv.mkDerivation {
    inherit pname version src contents;

    dontUnpack = true;
    dontConfigure = true;
    dontBuild = true;

    nativeBuildInputs = [pkgs.makeWrapper];

    installPhase = ''
      runHook preInstall
      mkdir -p $out/bin $out/share/${pname} $out/share/applications
      cp -a ${contents}/{locales,resources} $out/share/${pname}
      cp -a ${contents}/pulse-sms.desktop $out/share/applications/${pname}.desktop
      cp -a ${contents}/usr/share/icons $out/share
      substituteInPlace $out/share/applications/${pname}.desktop \
        --replace 'Exec=AppRun' 'Exec=${pname}'
      runHook postInstall
    '';

    postFixup = ''
      makeWrapper ${pkgs.electron}/bin/electron $out/bin/${pname} \
        --add-flags $out/share/${pname}/resources/app.asar \
        --prefix LD_LIBRARY_PATH : "${lib.makeLibraryPath [pkgs.stdenv.cc.cc]}"
    '';

    meta = {
      description = "A native desktop implementation of Pulse";
      homepage = "https://home.pulsesms.app/overview/index.html";
      platforms = ["x86_64-linux"];
    };
  };
in {
  home.packages = [pulse-sms];
}
