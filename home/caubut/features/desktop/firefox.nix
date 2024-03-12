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
    package = pkgs.firefox-nightly;
    profiles = {
      default = {
        id = 0;
        name = "Default";
        isDefault = true;
        settings =
          baseSettings
          // {
            "keyword.enabled" = false; # split url and search bars
            "browser.urlbar.update2.engineAliasRefresh" = true; # FIXME: expose GUI options
          };
        extraConfig = arkenfox;
        search = {
          default = "Kagi";
          order = [
            "Kagi"
            "Nix Packages"
            "Nix Options"
            "NixOS Wiki"
            "Home Manager Options"
            "Google"
            "Bing"
            "DuckDuckGo"
          ];
          engines = {
            "Kagi" = {
              urls = [{template = "https://kagi.com/search?q={searchTerms}";}];
              iconUpdateURL = "https://assets.kagi.com/v1/kagi_assets/logos/blue_1.svg";
              updateInterval = 24 * 60 * 60 * 1000; # every day
              definedAliases = ["@k"];
            };
            "Nix Packages" = {
              urls = [
                {
                  template = "https://search.nixos.org/packages";
                  params = [
                    {
                      name = "type";
                      value = "packages";
                    }
                    {
                      name = "query";
                      value = "{searchTerms}";
                    }
                  ];
                }
              ];
              icon = "${pkgs.nixos-icons}/share/icons/hicolor/scalable/apps/nix-snowflake.svg";
              definedAliases = ["@np"];
            };
            "Nix Options" = {
              urls = [
                {
                  template = "https://search.nixos.org/options";
                  params = [
                    {
                      name = "type";
                      value = "options";
                    }
                    {
                      name = "query";
                      value = "{searchTerms}";
                    }
                  ];
                }
              ];
              icon = "${pkgs.nixos-icons}/share/icons/hicolor/scalable/apps/nix-snowflake.svg";
              definedAliases = ["@no"];
            };
            "NixOS Wiki" = {
              urls = [{template = "https://nixos.wiki/index.php?search={searchTerms}";}];
              iconUpdateURL = "https://nixos.wiki/favicon.png";
              updateInterval = 24 * 60 * 60 * 1000; # every day
              definedAliases = ["@nw"];
            };
            "Home Manager Options" = {
              urls = [{template = "https://mipmip.github.io/home-manager-option-search?query={searchTerms}";}];
              icon = "${pkgs.nixos-icons}/share/icons/hicolor/scalable/apps/nix-snowflake.svg";
              definedAliases = ["@hm"];
            };
            "Google".metaData.alias = "@g";
            "eBay".metaData.hidden = true;
            "Amazon.com".metaData.hidden = true;
            "Wikipedia (en)".metaData.hidden = true;
          };
        };
      };
      unsafe = {
        id = 1;
        name = "Unsafe";
        isDefault = false;
        settings = baseSettings // {};
      };
    };
  };
  # alias 'firefox-nightly' to 'firefox'
  # home.packages = [
  #   (pkgs.linkFarm "firefox" [
  #     {
  #       name = "bin/firefox";
  #       path = "${inputs.firefox-nightly.packages.${pkgs.system}.firefox-nightly-bin}/bin/firefox-nightly";
  #     }
  #   ])
  # ];
}
# TODO ram disk
