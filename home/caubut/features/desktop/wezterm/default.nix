{
  config,
  lib,
  pkgs,
  ...
}: let
  wezterm = pkgs.rustPlatform.buildRustPackage rec {
    pname = "wezterm";
    version = "721fbdf5dc39aaeacc0517e0422d06f0cf81561b";

    src = pkgs.fetchFromGitHub {
      owner = "wez";
      repo = pname;
      rev = version;
      fetchSubmodules = true;
      hash = "sha256-S8i3EXUEChlf2Il3AAhfjIkqZO6PoB2PfLizOeubNnU=";
    };

    postPatch = ''
      echo ${version} > .tag

      # tests are failing with: Unable to exchange encryption keys
      rm -r wezterm-ssh/tests
    '';

    cargoLock = {
      lockFile = ./Cargo.lock;
      outputHashes = {
        "xcb-imdkit-0.2.0" = "sha256-L+NKD0rsCk9bFABQF4FZi9YoqBHr4VAZeKAWgsaAegw=";
        "xcb-1.2.1" = "sha256-zkuW5ATix3WXBAj2hzum1MJ5JTX3+uVQ01R1vL6F1rY=";
      };
    };

    nativeBuildInputs = with pkgs; [
      installShellFiles
      ncurses # tic for terminfo
      pkg-config
      python3
    ];

    buildInputs = with pkgs; [
      fontconfig
      zlib
      xorg.libX11
      xorg.libxcb
      libxkbcommon
      openssl
      wayland
      xorg.xcbutil
      xorg.xcbutilimage
      xorg.xcbutilkeysyms
      xorg.xcbutilwm # contains xcb-ewmh among others
    ];

    buildFeatures = ["distro-defaults"];

    postInstall = ''
      mkdir -p $out/nix-support
      echo "${passthru.terminfo}" >> $out/nix-support/propagated-user-env-packages

      install -Dm644 assets/icon/terminal.png $out/share/icons/hicolor/128x128/apps/org.wezfurlong.wezterm.png
      install -Dm644 assets/wezterm.desktop $out/share/applications/org.wezfurlong.wezterm.desktop
      install -Dm644 assets/wezterm.appdata.xml $out/share/metainfo/org.wezfurlong.wezterm.appdata.xml

      install -Dm644 assets/shell-integration/wezterm.sh -t $out/etc/profile.d
      installShellCompletion --cmd wezterm \
        --bash assets/shell-completion/bash \
        --fish assets/shell-completion/fish \
        --zsh assets/shell-completion/zsh

      install -Dm644 assets/wezterm-nautilus.py -t $out/share/nautilus-python/extensions
    '';

    preFixup = ''
      patchelf \
        --add-needed "${pkgs.libGL}/lib/libEGL.so.1" \
        --add-needed "${pkgs.vulkan-loader}/lib/libvulkan.so.1" \
        $out/bin/wezterm-gui
    '';

    passthru = {
      tests = {
        all-terminfo = pkgs.nixosTests.allTerminfo;
        terminal-emulators = pkgs.nixosTests.terminal-emulators.wezterm;
      };
      terminfo =
        pkgs.runCommand "wezterm-terminfo"
        {
          nativeBuildInputs = [pkgs.ncurses];
        } ''
          mkdir -p $out/share/terminfo $out/nix-support
          tic -x -o $out/share/terminfo ${src}/termwiz/data/wezterm.terminfo
        '';
    };

    meta = with lib; {
      description = "GPU-accelerated cross-platform terminal emulator and multiplexer written by @wez and implemented in Rust";
      homepage = "https://wezfurlong.org/wezterm";
      license = licenses.mit;
      maintainers = with maintainers; [SuperSandro2000 mimame];
    };
  };
in {
  programs.wezterm = {
    enable = true;
    package = wezterm;
    enableBashIntegration = config.programs.bash.enable;
    enableZshIntegration = config.programs.zsh.enable;
  };
}