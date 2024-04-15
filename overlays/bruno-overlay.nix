_: (final: _: let
  nv = (import ./nvpkgs.nix)."bruno-deb-${final.system}";
  rpath = final.lib.makeLibraryPath (with final; [
    stdenv.cc.cc
    fontconfig
    freetype
    gdk-pixbuf
    udev
    alsa-lib
    at-spi2-atk
    at-spi2-core
    atk
    cairo
    cups
    dbus
    expat
    glib
    gtk3
    libdrm
    libxkbcommon
    mesa
    nspr
    nss
    pango
    xorg.libX11
    xorg.libXcomposite
    xorg.libXdamage
    xorg.libXext
    xorg.libXfixes
    xorg.libXrandr
    xorg.libxcb
    libglvnd
    xorg.libXScrnSaver
    xorg.libXcursor
    xorg.libXi
    xorg.libXrender
    xorg.libXtst
  ]);
in {
  # unfree version which supports golden edition
  bruno = final.stdenv.mkDerivation {
    pname = "bruno";
    inherit (nv) version;

    src = final.fetchurl {
      inherit (nv.src) url sha256;
    };

    dontConfigure = true;

    dontBuild = true;

    gtk_modules = map (x: x + x.gtkModule) (with final; [libcanberra-gtk3]);

    nativeBuildInputs = with final; [makeWrapper dpkg desktop-file-utils asar];

    unpackPhase = "dpkg-deb --fsys-tarfile $src | tar -x --no-same-permissions --no-same-owner";

    installPhase = ''
      runHook preInstall

      shopt -s extglob

      mkdir -p $out
      mkdir $out/{bin,share}

      # NOTE: libGLESv2.so seems to get loaded relative to the binary so leaving all next to binary
      mv opt/Bruno $out/share/Bruno

      # NOTE: fixes path for case sensitive filesystems
      asarBundle="$TMPDIR/app"
      asar e "$out/share/Bruno/resources/app.asar" "$asarBundle"
      mv "$asarBundle/web/static/diff2Html.min.css" "$asarBundle/web/static/diff2html.min.css"
      asar p "$asarBundle" "$out/share/Bruno/resources/app.asar"
      rm -rf "$asarBundle"

      cp -R usr/share/{applications,icons} $out/share

      patchelf \
        --set-interpreter $(cat $NIX_CC/nix-support/dynamic-linker) \
        --set-rpath ${rpath}:$out/share/Bruno \
        $out/share/Bruno/bruno

      wrapProgram $out/share/Bruno/bruno \
        --add-flags $out/share/Bruno/app.asar \
        --add-flags --no-sandbox \
        --suffix-each GTK_PATH : "$gtk_modules" \
        --prefix LD_LIBRARY_PATH : ${rpath}

      ln -s $out/share/Bruno/bruno $out/bin/bruno

      ${final.desktop-file-utils}/bin/desktop-file-install --dir $out/share/applications \
        --set-key Exec --set-value bruno usr/share/applications/bruno.desktop

      runHook postInstall
    '';

    meta = with final.lib; {
      description = "Open-source IDE For exploring and testing APIs.";
      homepage = "https://www.usebruno.com";
      platforms = [final.system];
      license = licenses.unfree;
      maintainers = with maintainers; [water-sucks lucasew kashw2 mattpolzin];
      mainProgram = "bruno";
    };
  };
})
