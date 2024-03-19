{
  config,
  lib,
  pkgs,
  ...
}: {
  # Run in xserver to login since webview is hidden
  # WAYLAND_DISPLAY= GDK_BACKEND=x11 webex
  home = {
    packages = [pkgs.webex];
    # (pkgs.webex.overrideAttrs
    #   {
    #     postPatch = ''
    #       substituteInPlace opt/Webex/bin/webex.desktop --replace-fail /opt "env WAYLAND_DISPLAY= GDK_BACKEND=x11 $out/opt"
    #     '';
    #   })

    # persistence
    persistence = {
      "/persist${config.home.homeDirectory}".directories = [
        (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/Webex")
        (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/WebexLauncher")
      ];
    };
  };
}
