{
  inputs,
  lib,
  pkgs,
  ...
}: {
  imports = [
    inputs.hyprland.homeManagerModules.default
    ./theme.nix
    ./features
  ];

  xdg.portal = {
    enable = true;
    extraPortals = [
      pkgs.xdg-desktop-portal-hyprland
      pkgs.xdg-desktop-portal-gtk
    ];
    configPackages = [pkgs.hyprland];
    xdgOpenUsePortal = true;
  };

  home = {
    sessionVariables = {
      NIXOS_OZONE_WL = 1; # fixes some apps in wayland
    };
  };

  # TODO: X11
  # services.xsettingsd = {
  #   enable = true;
  #   settings = {
  #     "Net/ThemeName" = "Catppuccin-Macchiato-Compact-Sky-Dark";
  #     "Net/IconThemeName" = "Vivid-Glassy-Dark-Icons";
  #   };
  # };

  # TODO: DISPLAY=:0 ags -b hypr
  wayland.windowManager.hyprland = {
    enable = true;
    package = pkgs.hyprland;
    xwayland.enable = true;

    systemd = {
      enable = true;
      # Same as default, but stop graphical-session too
      extraCommands = lib.mkBefore [
        "systemctl --user stop graphical-session.target"
        "systemctl --user start hyprland-session.target"
      ];
    };

    plugins = [pkgs.hyprbars];

    settings = {
      # startup applications
      exec-once = [
        "ags -b hypr"
      ];

      # keybinds
      "$mod" = "SUPER";
      bind = let
        ags = "exec, ags -b hypr";
      in [
        "$mod, T,     exec,   WAYLAND_DEBUG=1 WEZTERM_LOG=debug wezterm"
        "$mod, Y,     exec,   kitty"
        "$mod, F,     exec,   firefox-nightly"
        "$mod, D,     exec,   discord"
        "CTRL ALT, Delete,    exit"

        # movement keybinds
        "$mod, right, workspace, +1"
        "$mod, left, workspace, -1"

        # ags # TODO: merge if
        "$mod, R,             ${ags} quit; ags -b hypr" # reload ags
        "$mod, SPACE,         ${ags} -t applauncher" # app launcher
        "$mod, P,         ${ags} -t iconbrowser" # app launcher
      ];

      monitor = [
        # "eDP-1, 1920x1080, 0x0, 1"
        # "HDMI-A-1, 2560x1440, 1920x0, 1"
        ",preferred,auto,1"
      ];

      general = {
        layout = "dwindle";
        resize_on_border = true; # resize windows by dragging their borders
        "col.active_border" = "0x00000000"; # active window border color
      };

      dwindle = {
        pseudotile = "yes"; # retain floating window size when tiled
        preserve_split = "yes"; # preserve split ratio when resizing
      };

      windowrule = let
        f = regex: "float, ^(${regex})$";
      in [
        (f "org.gnome.Calculator")
        (f "org.gnome.Nautilus") # FIXME: check
        (f "org.gnome.font-viewer") # FIXME: check
        (f "pavucontrol") # FIXME: check
        (f "nm-connection-editor") # FIXME: check
        (f "blueberry.py") # FIXME: check
        (f "org.gnome.Settings") # FIXME: check
        (f "org.gnome.design.Palette") # FIXME: check
        (f "Color Picker") # FIXME: check
        (f "xdg-desktop-portal") # FIXME: check
        (f "xdg-desktop-portal-gnome") # FIXME: check
        (f "transmission-gtk") # FIXME: check
        (f "com.github.Aylur.ags")
      ];

      windowrulev2 = [
        # "float,class:(CiscoCollabHost)"
      ];

      misc = {
        layers_hog_keyboard_focus = true; # keyboard-interactive layers keep their focus on mouse move
        disable_splash_rendering = true; # disable startup splash screen
        force_default_wallpaper = 0; # use the default non-anime wallpaper
      };

      plugin = {
        hyprbars = {
          bar_color = "rgb(2a2a2a)";
          bar_height = 28;
          col_text = "rgba(ffffffdd)";
          bar_text_size = 11;
          bar_text_font = "Ubuntu Nerd Font";
          hyprbars-button = let
            closeAction = "hyprctl dispatch killactive";

            isOnSpecial = ''hyprctl activewindow -j | jq -re 'select(.workspace.name == "special")' >/dev/null'';
            moveToSpecial = "hyprctl dispatch movetoworkspacesilent special";
            moveToActive = "hyprctl dispatch movetoworkspacesilent name:$(hyprctl -j activeworkspace | jq -re '.name')";
            minimizeAction = "${isOnSpecial} && ${moveToActive} || ${moveToSpecial}";

            maximizeAction = "hyprctl dispatch togglefloating";
          in [
            "rgb(f38ba8),12,,${closeAction}"
            "rgb(a6e3a1),12,,${maximizeAction}"
            "rgb(f9e2af),12,,${minimizeAction}"
          ];
        };
      };

      # # input = {
      # #   kb_layout = "hu";
      # #   kb_model = "pc104";
      # #   follow_mouse = 1;
      # #   touchpad = {
      # #     natural_scroll = "yes";
      # #     disable_while_typing = true;
      # #     drag_lock = true;
      # #   };
      # #   sensitivity = 0;
      # #   float_switch_override_focus = 2;
      # # };

      #  binds = {
      #   allow_workspace_cycles = true;
      # };

      # gestures = {
      #   workspace_swipe = true;
      #   workspace_swipe_forever = true;
      #   workspace_swipe_numbered = true;
      # };

      #   windowrule = let
      #     f = regex: "float, ^(${regex})$";
      #   in [
      #     (f "org.gnome.Calculator")
      #     (f "org.gnome.Nautilus")
      #     (f "pavucontrol")
      #     (f "nm-connection-editor")
      #     (f "blueberry.py")
      #     (f "org.gnome.Settings")
      #     (f "org.gnome.design.Palette")
      #     (f "Color Picker")
      #     (f "xdg-desktop-portal")
      #     (f "xdg-desktop-portal-gnome")
      #     (f "transmission-gtk")
      #     (f "com.github.Aylur.ags")
      #     "workspace 7, title:Spotify"
      #   ];
      #   bind = let
      #     binding = mod: cmd: key: arg: "${mod}, ${key}, ${cmd}, ${arg}";
      #     mvfocus = binding "SUPER" "movefocus";
      #     ws = binding "SUPER" "workspace";
      #     resizeactive = binding "SUPER CTRL" "resizeactive";
      #     mvactive = binding "SUPER ALT" "moveactive";
      #     mvtows = binding "SUPER SHIFT" "movetoworkspace";hype
      #     #   e = "exec, ags -b hypr";
      #     # ags = "exec, ags -b hypr";
      #     #   arr = [1 2 3 4 5 6 7 8 9];
      #     #   yt = pkgs.writeShellScriptBin "yt" ''
      #     #     notify-send "Opening video" "$(wl-paste)"
      #     #     mpv "$(wl-paste)"
      #     #   '';
      #   in [
      #     # ", XF86PowerOff, ${e} -t powermenu"
      #     # "SUPER, Tab,     ${e} -t overview"
      #     # ", XF86Launch4,  ${e} -r 'recorder.start()'"
      #     # ",Print,         ${e} -r 'recorder.screenshot()'"
      #     # "SHIFT,Print,    ${e} -r 'recorder.screenshot(true)'"
      #     # "SUPER, Return, exec, xterm" # xterm is a symlink, not actually xterm
      #     "SUPER, W, exec, firefox"
      #     "SUPER, E, exec, wezterm"

      #     # # youtube
      #     # ", XF86Launch1,  exec, ${yt}/bin/yt"

      #     # "ALT, Tab, focuscurrentorlast"
      #     # "CTRL ALT, Delete, exit"
      #     # "ALT, Q, killactive"
      #     # "SUPER, F, togglefloating"
      #     # "SUPER, G, fullscreen"
      #     # "SUPER, O, fakefullscreen"
      #     # "SUPER, P, togglesplit"

      #     # (mvfocus "k" "u")
      #     # (mvfocus "j" "d")
      #     # (mvfocus "l" "r")
      #     # (mvfocus "h" "l")
      #     # (ws "left" "e-1")
      #     # (ws "right" "e+1")
      #     # (mvtows "left" "e-1")
      #     # (mvtows "right" "e+1")
      #     # (resizeactive "k" "0 -20")
      #     # (resizeactive "j" "0 20")
      #     # (resizeactive "l" "20 0")
      #     # (resizeactive "h" "-20 0")
      #     # (mvactive "k" "0 -20")
      #     # (mvactive "j" "0 20")
      #     # (mvactive "l" "20 0")
      #     # (mvactive "h" "-20 0")
      #   ];
      #   # ++ (map (i: ws (toString i) (toString i)) arr)
      #   # ++ (map (i: mvtows (toString i) (toString i)) arr);

      #   # bindle = let
      #   #   e = "exec, ags -b hypr -r";
      #   # in [
      #   #   ",XF86MonBrightnessUp,   ${e} 'brightness.screen += 0.05; indicator.display()'"
      #   #   ",XF86MonBrightnessDown, ${e} 'brightness.screen -= 0.05; indicator.display()'"
      #   #   ",XF86KbdBrightnessUp,   ${e} 'brightness.kbd++; indicator.kbd()'"
      #   #   ",XF86KbdBrightnessDown, ${e} 'brightness.kbd--; indicator.kbd()'"
      #   #   ",XF86AudioRaiseVolume,  ${e} 'audio.speaker.volume += 0.05; indicator.speaker()'"
      #   #   ",XF86AudioLowerVolume,  ${e} 'audio.speaker.volume -= 0.05; indicator.speaker()'"
      #   # ];

      #   # bindl = let
      #   #   e = "exec, ags -b hypr -r";
      #   # in [
      #   #   ",XF86AudioPlay,    ${e} 'mpris?.playPause()'"
      #   #   ",XF86AudioStop,    ${e} 'mpris?.stop()'"
      #   #   ",XF86AudioPause,   ${e} 'mpris?.pause()'"
      #   #   ",XF86AudioPrev,    ${e} 'mpris?.previous()'"
      #   #   ",XF86AudioNext,    ${e} 'mpris?.next()'"
      #   #   ",XF86AudioMicMute, ${e} 'audio.microphone.isMuted = !audio.microphone.isMuted'"
      #   # ];

      #   bindm = [
      #     "SUPER, mouse:273, resizewindow"
      #     "SUPER, mouse:272, movewindow"
      #   ];

      #   decoration = {
      #     drop_shadow = "yes";
      #     shadow_range = 8;
      #     shadow_render_power = 2;
      #     "col.shadow" = "rgba(00000044)";

      #     dim_inactive = false;

      #     blur = {
      #       enabled = true;
      #       size = 8;
      #       passes = 3;
      #       new_optimizations = "on";
      #       noise = 0.01;
      #       contrast = 0.9;
      #       brightness = 0.8;
      #     };
      #   };

      #   animations = {
      #     enabled = "yes";
      #     bezier = "myBezier, 0.05, 0.9, 0.1, 1.05";
      #     animation = [
      #       "windows, 1, 5, myBezier"
      #       "windowsOut, 1, 7, default, popin 80%"
      #       "border, 1, 10, default"
      #       "fade, 1, 7, default"
      #       "workspaces, 1, 6, default"
      #     ];
      #   };
    };
    # systemd = {
    #   enable = true;
    #   # Same as default, but stop graphical-session too
    #   # TODO:need this? see xsession
    #   # https://github.com/nix-community/home-manager/blob/master/modules/xsession.nix
    #   extraCommands = lib.mkBefore [
    #     "systemctl --user stop graphical-session.target"
    #     "systemctl --user start hyprland-session.target"
    #   ];
    # };
  };
}
