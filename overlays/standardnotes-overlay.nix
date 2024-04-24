_: (final: prev: let
  nv = (import ./nvpkgs.nix)."standardnotes-desktop-deb-${final.system}";
  electron = final.electron_27;
  rpath = final.lib.makeLibraryPath (with final; [
    libsecret
    stdenv.cc.cc.lib
  ]);
in {
  standardnotes =
    (prev.standardnotes.override {
      inherit electron;
    })
    .overrideAttrs (attrs: {
      inherit (nv) version;

      src = final.fetchurl {
        inherit (nv.src) url sha256;
      };

      unpackPhase = ''
        ${attrs.unpackPhase}
        mv opt/Standard\ Notes opt/standardnotes
      '';

      installPhase = ''
        runHook preInstall

        mkdir -p $out/bin $out/share/standardnotes
        cp -R usr/share/{applications,icons} $out/share
        cp -R opt/standardnotes/resources/app.asar $out/share/standardnotes/

        makeWrapper ${electron}/bin/electron $out/bin/standardnotes \
          --add-flags $out/share/standardnotes/app.asar \
          --prefix LD_LIBRARY_PATH : ${rpath}

        desktop-file-install --dir $out/share/applications \
          --set-key Exec --set-value standardnotes usr/share/applications/standard-notes.desktop

        runHook postInstall
      '';

      # installPhase =
      #   builtins.replaceStrings
      #   ["Standard\\ Notes"]
      #   ["standardnotes"]
      #   attrs.installPhase;
    });
})
