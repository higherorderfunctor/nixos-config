{
  inputs,
  lib,
  pkgs,
  ...
}: let
  baseSettings = {
    "browser.toolbars.bookmarks.visibility" = "always";
    "extensions.pocket.enabled" = false;
    "browser.warnOnQuit" = false;
    "browser.warnOnQuitShortcut" = false;
    "extensions.activeThemeID" = "firefox-compact-dark@mozilla.org";
    "layout.css.prefers-color-scheme.content-override" = 0;
    "extensions.formautofill.addresses.enabled" = false;
    "extensions.formautofill.creditCards.enabled" = false;
    "signon.rememberSignons" = false;
  };
  arkenfox = lib.readFile (pkgs.fetchurl {
    url = "https://raw.githubusercontent.com/arkenfox/user.js/master/user.js";
    name = "arkenfox";
    hash = "sha256-H3Nk5sDxSElGRgK+cyQpVyjtlMF2Okxbstu9A+eJtGk=";
  });
in {
  xdg.mimeApps = {
    enable = true;
    defaultApplications = {
      "text/html" = "firefox-nightly.desktop";
      "x-scheme-handler/http" = "firefox-nightly.desktop";
      "x-scheme-handler/https" = "firefox-nightly.desktop";
      "x-scheme-handler/about" = "firefox-nightly.desktop";
      "x-scheme-handler/unknown" = "firefox-nightly.desktop";
    };
  };
  programs.firefox = {
    enable = true;
    package = inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin;
    profiles = {
      default = {
        id = 0;
        name = "Default";
        isDefault = true;
        settings = baseSettings // {};
        extraConfig = arkenfox;
      };
      unsafe = {
        id = 1;
        name = "Unsafe";
        isDefault = false;
        settings = baseSettings // {};
      };
    };
  };
}
