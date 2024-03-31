
{inputs, ...}: (final: _: let

  srcjson = {
    "version" = "3.181.23";
    "deb" = {
      "x86_64-linux" = {
        "url" = "https://github.com/standardnotes/app/releases/download/%40standardnotes/desktop%403.181.23/standard-notes-3.181.23-linux-amd64.deb";
        "hash" = "sha512-zWjST3guI0qifvZIwSLJ0nIpU12Mu3+m25Xdoqv0BQC7tscChEdCGUAJRUKHEf0b8l4uvp8qBGHiBOfbrIi//w==";
      };
      "aarch64-linux" = {
        "url" = "https://github.com/standardnotes/app/releases/download/%40standardnotes/desktop%403.181.23/standard-notes-3.181.23-linux-arm64.deb";
        "hash" = "sha512-7R5Ym44mrVgUiqdt6NL8F9uUUOroQRxwn30xKThyIQm2HGRUJivRfOws98El9zV8bKG1khk4DZaMiLQSMjrtaQ==";
      };
    };
  }; in {
    standardnotes = 
  }

# (final: _: {
#   nix-gl-host = inputs.nix-gl-host.defaultPackage.${final.system};
# })
# {
#   inputs,
#   pkgs,
#   ...
# }:
# # : let
# #   srcjson = {
# #     "version" = "3.181.23";
# #     "deb" = {
# #       "x86_64-linux" = {
# #         "url" = "https://github.com/standardnotes/app/releases/download/%40standardnotes/desktop%403.181.23/standard-notes-3.181.23-linux-amd64.deb";
# #         "hash" = "sha512-zWjST3guI0qifvZIwSLJ0nIpU12Mu3+m25Xdoqv0BQC7tscChEdCGUAJRUKHEf0b8l4uvp8qBGHiBOfbrIi//w==";
# #       };
# #       "aarch64-linux" = {
# #         "url" = "https://github.com/standardnotes/app/releases/download/%40standardnotes/desktop%403.181.23/standard-notes-3.181.23-linux-arm64.deb";
# #         "hash" = "sha512-7R5Ym44mrVgUiqdt6NL8F9uUUOroQRxwn30xKThyIQm2HGRUJivRfOws98El9zV8bKG1khk4DZaMiLQSMjrtaQ==";
# #       };
# #     };
# #   };
# #   standardnotes =
# #     pkgs.standardnotes.override (_: {
# #
# #
# #       });
# # in {
# {
#   home.packages = [
#     pkgs.standardnotes
#     # inputs.nix-gl-host.defaultPackage.x86_64-linux
#     # pkgs.libcanberra-gtk3
#     # pkgs.mesa
#   ];
# }
# FIXME: https://discourse.nixos.org/t/standardnotes-3-191-4-fails-to-build/40934
#
# building the system configuration...
# error: builder for '/nix/store/flm9h14rq9msa0lxdbm5ci9hkxz61v16-standardnotes-3.191.4.drv' failed with exit code 1;
#        last 6 log lines:
#        > Running phase: unpackPhase
#        > Running phase: patchPhase
#        > Running phase: updateAutotoolsGnuConfigScriptsPhase
#        > Updating Autotools / GNU config script to a newer upstream version: ./opt/Standard
#        > Updating Autotools / GNU config script to a newer upstream version: Notes/resources/app.asar.unpacked/node_modules/sqlite3/build/Release/obj/gen/sqlite-autoconf-3410100/config.sub
#        > cp: cannot create regular file 'Notes/resources/app.asar.unpacked/node_modules/sqlite3/build/Release/obj/gen/sqlite-autoconf-3410100/config.sub': No such file or directory
#        For full logs, run 'nix log /nix/store/flm9h14rq9msa0lxdbm5ci9hkxz61v16-standardnotes-3.191.4.drv'.
#
# Here is my derivation.nix file, I based it on the derivation in nixpkgs (here 1) which wraps the .deb build.
#
# { lib, stdenv, fetchurl, dpkg, makeWrapper, electron, libsecret
# , desktop-file-utils , callPackage }:
#
# let
#
#   srcjson = builtins.fromJSON (builtins.readFile ./src.json);
#
#   throwSystem = throw "Unsupported system: ${stdenv.hostPlatform.system}";
#
# in
#
# stdenv.mkDerivation rec {
#
#   pname = "standardnotes";
#
#   src = fetchurl (srcjson.deb.${stdenv.hostPlatform.system} or throwSystem);
#
#   inherit (srcjson) version;
#
#   dontConfigure = true;
#
#   dontBuild = true;
#
#   nativeBuildInputs = [ makeWrapper dpkg desktop-file-utils ];
#
#   unpackPhase = "dpkg-deb --fsys-tarfile $src | tar -x --no-same-permissions --no-same-owner";
#
#   installPhase = ''
#     runHook preInstall
#
#     mkdir -p $out/bin $out/share/standardnotes
#
#     cp -R usr/share/{applications,icons} $out/share
#     cp -R opt/Standard\ Notes/resources/app.asar $out/share/standardnotes/
#
#     makeWrapper ${electron}/bin/electron $out/bin/standardnotes \
#       --add-flags $out/share/standardnotes/app.asar \
#       --prefix LD_LIBRARY_PATH : ${lib.makeLibraryPath [ libsecret stdenv.cc.cc.lib ]}
#
#     ${desktop-file-utils}/bin/desktop-file-install --dir $out/share/applications \
#       --set-key Exec --set-value standardnotes usr/share/applications/standard-notes.desktop
#
#     runHook postInstall
#   '';
#
#   meta = with lib; {
#     description = "A simple and private notes app";
#     longDescription = ''
#       Standard Notes is a private notes app that features unmatched simplicity,
#       end-to-end encryption, powerful extensions, and open-source applications.
#     '';
#     homepage = "https://standardnotes.org";
#     license = licenses.agpl3;
#     maintainers = with maintainers; [ mgregoire chuangzhu squalus ];
#     sourceProvenance = [ sourceTypes.binaryNativeCode ];
#     platforms = builtins.attrNames srcjson.deb;
#     mainProgram = "standardnotes";
#   };
# }
