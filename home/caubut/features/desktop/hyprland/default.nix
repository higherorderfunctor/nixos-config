{
  config,
  inputs,
  lib,
  pkgs,
  ...
}: {
  imports = [
    inputs.hyprland.homeManagerModules.default
    ./theme.nix
    ./features
    ./hypridle.nix
    ./hyprlock.nix
  ];

  # xdg.portal = {
  #   enable = true;
  #   # extraPortals = [
  #   #   pkgs.xdg-desktop-portal-hyprland
  #   #   pkgs.xdg-desktop-portal-gtk
  #   # ];
  #   configPackages = [pkgs.hyprland];
  #   xdgOpenUsePortal = true;
  # };

  home = {
    sessionVariables = {
      NIXOS_OZONE_WL = 1; # fixes some apps in wayland
    };
    packages = with pkgs; [hyprshot];
  };

  # TODO: X11
  # services.xsettingsd = {
  #   enable = true;
  #   settings = {
  #     "Net/ThemeName" = "Catppuccin-Macchiato-Compact-Sky-Dark";
  #     "Net/IconThemeName" = "Vivid-Glassy-Dark-Icons";
  #   };
  # };

  # cat $XDG_RUNTIME_DIR/hypr/$(ls -t $XDG_RUNTIME_DIR/hypr/ | head -n 1)/hyprland.log

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      (lib.strings.removePrefix "${config.home.homeDirectory}/" "${config.xdg.cacheHome}/hyprland")
    ];
  };

  # TODO: DISPLAY=:0 ags -b hypr
  wayland.windowManager.hyprland = {
    enable = true;
    package = null; # use nixos module
    portalPackage = null; # use nixos module
    # xwayland.enable = true;

    systemd = {
      enable = true;
      # Same as default, but stop graphical-session too
      # TODO:need this? see xsession
      # https://github.com/nix-community/home-manager/blob/master/modules/xsession.nix
      extraCommands = lib.mkBefore [
        "systemctl --user stop graphical-session.target"
        "systemctl --user start hyprland-session.target"
      ];
    };

    plugins = with pkgs.hyprlandPlugins; [hyprbars hyprexpo];

    settings = {
      source = [
        "${pkgs.catppuccin-hyprland}/mocha.conf"
      ];

      debug = {
        disable_logs = false;
        enable_stdout_logs = true;
        colored_stdout_logs = true;
      };

      # startup applications
      exec-once = [
        # fixes issues with plugin disaptchers
        # https://github.com/hyprwm/hyprland-plugins/issues/204
        "hyprpm reload -n"
        # gnome-keyring + other fixes
        # https://wiki.hyprland.org/Useful-Utilities/Hyprland-desktop-portal/
        # https://github.com/NixOS/nixpkgs/issues/174099
        "${pkgs.dbus}/bin/dbus-update-activation-environment --systemd --all"
        "ags run"
      ];

      # keybinds
      "$mod" = "SUPER";
      bind = let
        ags = "exec, ags";
      in [
        "$mod,     T,      exec,           wezterm"
        "$mod,     Y,      exec,           kitty"
        "$mod,     F,      exec,           firefox-nightly"
        "$mod,     D,      exec,           discord"
        "$mod,     L,      exec,           ${lib.getExe config.programs.hyprlock.package}"

        "CTRL ALT, Delete, exit"

        # movement keybinds
        "$mod,     right,   workspace,     +1"
        "$mod,     left,    workspace,     -1"
        "$mod,     C,       hyprexpo:expo, toggle" # can be: toggle, off/disable or on/enable

        # ags # TODO: merge if
        "$mod,     R,       ${ags} quit; ags run" # reload ags
        "$mod,     SPACE,   ${ags} toggle launcher" # app launcher
        # "$mod,     P,       ${ags} -f ${config.xdg.configHome}/ags/iconbrowser.js" # icon browser
      ];

      monitor = [
        # "eDP-1, 1920x1080, 0x0, 1"
        # "HDMI-A-1, 2560x1440, 1920x0, 1"
        ",preferred,auto,1"
      ];

      general = {
        layout = "dwindle";
        resize_on_border = true; # resize windows by dragging their borders
        "col.active_border" = "$mauve"; # active window border color
        "col.inactive_border" = "$crust"; # active window border color
      };

      dwindle = {
        pseudotile = "yes"; # retain floating window size when tiled
        preserve_split = "yes"; # preserve split ratio when resizing
      };

      windowrule = [
        "float, class:^(org.gnome.Calculator)$"
        "float, class:^(org.gnome.Nautilus)$" # FIXME: check
        "float, class:^(org.gnome.font-viewer)$" # FIXME: check
        "float, class:^(pavucontrol)$" # FIXME: check
        "float, class:^(nm-connection-editor)$" # FIXME: check
        "float, class:^(blueberry.py)$" # FIXME: check
        "float, class:^(org.gnome.Settings)$" # FIXME: check
        "float, class:^(org.gnome.design.Palette)$" # FIXME: check
        "float, class:^(Color Picker)$" # FIXME: check
        "float, class:^(xdg-desktop-portal)$" # FIXME: check
        "float, class:^(xdg-desktop-portal-gnome)$" # FIXME: check
        "float, class:^(transmission-gtk)$" # FIXME: check
        "float, class:^(com.github.Aylur.ags)$"
        # https://github.com/mentalAdventurer/config/blob/97782801b168dc4fb08d423053368956dece9606/hypr/windowrules.conf#L37
        ### Webex"
        "noborder, class:^(CiscoCollabHost), title: ^(PopupWidgetTitle)"
        "float, class:^(CiscoCollabHost), title: ^(PopupWidgetTitle)"
        "noinitialfocus, class:^(CiscoCollabHost), title: ^(PopupWidgetTitle)"
        "noborder, title: ^(PopupWidgetTitle), xwayland: 1" # x11 - no class set
        "float, title: ^(PopupWidgetTitle), xwayland: 1" # x11 - no class set
        # Device Connection
        "stayfocused,title:^(PopupDeviceConnectionFrame), xwayland: 1"

        # Messages
        "unset, title: (Form), xwayland: 1" # does not work"
        "center, title: (Form), xwayland: 1" # does not work"

        # Call Window (x11), Can't be seperated from the rest of the windows
        #"size 3965 667, title: ^(Webex), xwayland: 1
        #"float, title: ^(Webex), class: ^(Webex), xwayland: 1

        "unset, class:^(CiscoCollabHost), title: ^(Webex), floating: 1"
        "noborder, class:^(CiscoCollabHost), title: ^(Webex), floating: 1"
        "noinitialfocus, class:^(CiscoCollabHost), title: ^(Webex), floating: 1"
      ];

      input = {
        #   kb_layout = "hu";
        #   kb_model = "pc104";
        follow_mouse = 2; # cursor focus will be detached from keyboard focus
        #   touchpad = {
        #     natural_scroll = "yes";
        #     disable_while_typing = true;
        #     drag_lock = true;
        #   };
        #   sensitivity = 0;
        #   float_switch_override_focus = 2;
      };

      misc = {
        layers_hog_keyboard_focus = true; # keyboard-interactive layers keep their focus on mouse move
        disable_splash_rendering = true; # disable startup splash screen
        force_default_wallpaper = 0; # use the default non-anime wallpaper
      };

      plugin = {
        hyprbars = {
          bar_color = "$surface0";
          bar_height = 28;
          col_text = "$text";
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
            "$red,12,x,${closeAction}"
            "$green,12,+,${maximizeAction}"
            "$yellow,12,-,${minimizeAction}"
          ];
        };
        hyprexpo = {
          columns = 3;
          gap_size = 5;
          bg_col = "$crust";
          workspace_method = "center current"; # [center/first] [workspace] e.g. first 1 or center m+1
          # enable_gesture = true # laptop touchpad
          # gesture_fingers = 3  # 3 or 4
          # gesture_distance = 300 # how far is the "max"
          # gesture_positive = true # positive = swipe down. Negative = swipe up.
        };
      };

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
  };
}
