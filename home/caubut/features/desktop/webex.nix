{
  config,
  lib,
  pkgs,
  ...
}: {
  # Run in xserver to login since webview is hidden for initial setup
  # WAYLAND_DISPLAY= GDK_BACKEND=x11 webex
  home = {
    # packages = [pkgs.webex];
    packages = [
      (pkgs.webex.overrideAttrs
        {
          # substituteInPlace opt/Webex/bin/webex.desktop --replace /opt $out/opt
          postPatch = ''
            substituteInPlace opt/Webex/bin/webex.desktop \
              --replace-fail /opt $out/opt \
              --replace-fail CiscoCollabHost "CiscoCollabHost $out/opt/Webex/lib/ libWebexAppLoader.so /Start"
          '';
        })
    ];

    # WAYLAND_DISPLAY=:0 webex "$(readlink -f $(dirname $(readlink -f $(which webex)))/../lib)/" libWebexAppLoader.so /Start &

    # persistence
    persistence = {
      "/persist${config.home.homeDirectory}".directories = [
        (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/Webex")
        (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.dataHome}/WebexLauncher")
      ];
    };
  };
}
