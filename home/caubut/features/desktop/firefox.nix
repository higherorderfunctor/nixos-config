{
  config,
  pkgs,
  ...
}: let
  settings = {
    "browser.bookmarks.addedImportButton" = false; # don't include the default bookmark
    "browser.warnOnQuit" = false; # no prompt on quit
    "browser.warnOnQuitShortcut" = false; # no prompt on quit
    "extensions.activeThemeID" = "firefox-compact-dark@mozilla.org"; # set the theme
    "extensions.pocket.enabled" = false; # disable pocket
    "findbar.highlightAll" = true; # highlight all matches when searching in page text
    "keyword.enabled" = false; # split url and search bars / breaks alias searches
    "layout.css.prefers-color-scheme.content-override" = 0; # dark mode
    "privacy.clearOnShutdown.siteSettings" = true; # reset site settings (location, camera, etc)
    "signon.autofillForms" = false; # no auto-fill
    "signon.rememberSignons" = false; # disable passwords
    "browser.uiCustomization.state" = builtins.toJSON {
      placements = {
        widget-overflow-fixed-list = [];
        nav-bar = [
          "back-button"
          "forward-button"
          "stop-reload-button"
          "home-button"
          "urlbar-container"
          "search-container"
          "downloads-button"
          "ublock0_raymondhill_net-browser-action"
          "_446900e4-71c2-419f-a6a7-df9c091e268b_-browser-action" # bitwarden
        ];
        toolbar-menubar = ["menubar-items"];
        TabsToolbar = [
          "tabbrowser-tabs"
          "new-tab-button"
        ];
        PersonalToolbar = ["personal-bookmarks"];
      };
      seen = [
        "developer-button"
        "ublock0_raymondhill_net-browser-action" # uBlock Origin
        "_446900e4-71c2-419f-a6a7-df9c091e268b_-browser-action" # bitwarden
      ];
      dirtyAreaCache = [
        "nav-bar"
        "PersonalToolbar"
        "toolbar-menubar"
        "TabsToolbar"
        "widget-overflow-fixed-list"
      ];
      currentVersion = 18;
      newElementCount = 4;
    };
  };
  baseProfile = {
    inherit settings;
    bookmarks = {};
    search = {
      force = true;
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
        };
        "Nix Packages" = {
          urls = [
            {
              template = "https://search.nixos.org/packages";
              params = [
                {
                  name = "channel";
                  value = "unstable";
                }
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
        };
        "Nix Options" = {
          urls = [
            {
              template = "https://search.nixos.org/options";
              params = [
                {
                  name = "channel";
                  value = "unstable";
                }
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
        };
        "NixOS Wiki" = {
          urls = [{template = "https://nixos.wiki/index.php?search={searchTerms}";}];
          iconUpdateURL = "https://nixos.wiki/favicon.png";
          updateInterval = 24 * 60 * 60 * 1000; # every day
        };
        "Home Manager Options" = {
          urls = [{template = "https://home-manager-options.extranix.com/?query={searchTerms}";}];
          icon = "${pkgs.nixos-icons}/share/icons/hicolor/scalable/apps/nix-snowflake.svg";
        };
        "eBay".metaData.hidden = true;
        "Amazon.com".metaData.hidden = true;
        "Wikipedia (en)".metaData.hidden = true;
      };
    };
  };
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
  # TODO: active theme doesn't appear to apply, possible sync issue with mozilla, needs more testing
  programs.firefox = {
    enable = true;
    package = pkgs.firefox-nightly;
    profiles = {
      default =
        baseProfile
        // {
          id = 0;
          name = "Default";
          settings =
            settings
            // {
              "browser.toolbars.bookmarks.visibility" = "always"; # show bookmarks bar
            };
          extraConfig = pkgs.arkenfox;
        };
      unsafe =
        baseProfile
        // {
          inherit settings;
          id = 1;
          name = "Unsafe";
        };
    };
  };
  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      ".mozilla/firefox/default" # persist default profile
    ];
  };
}
