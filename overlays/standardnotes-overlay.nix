{inputs, ...}: (final: _: let
  systemMap = {
    x86_64-linux = "linux-amd64";
    aarch64-linux = "linux-arm64";
  };
  nv = (import ./nvpkgs.nix)."standardnotes-${systemMap.${final.system}}-deb";
in {
  standardnotes = final.stdenvNoCC.mkDerivation {
    inherit (nv) version;

    pname = nv.name;

    src = final.fetchurl {
      inherit (nv.src) url sha256;
      name = "${nv.name}-${nv.version}.deb";
    };

    dontConfigure = true;

    dontBuild = true;

    nativeBuildInputs = with final; [makeWrapper dpkg desktop-file-utils];

    unpackPhase = "dpkg-deb --fsys-tarfile $src | tar -x --no-same-permissions --no-same-owner";

    installPhase = ''
      runHook preInstall

      mkdir -p $out/bin $out/share/standardnotes
      cp -R usr/share/{applications,icons} $out/share
      cp -R opt/Standard\ Notes/resources/app.asar $out/share/standardnotes/

      makeWrapper ${final.electron}/bin/electron $out/bin/standardnotes \
        --add-flags $out/share/standardnotes/app.asar \
        --prefix LD_LIBRARY_PATH : ${final.lib.makeLibraryPath (with final; [libsecret stdenv.cc.cc.lib])}

      ${final.desktop-file-utils}/bin/desktop-file-install --dir $out/share/applications \
        --set-key Exec --set-value standardnotes usr/share/applications/standard-notes.desktop

      runHook postInstall
    '';

    passthru.updateScript = final.callPackage ./update.nix {};
  };
})
