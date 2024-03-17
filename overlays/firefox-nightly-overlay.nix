{inputs, ...}: (final: prev: {
  firefox-bin-unwrapped = prev.firefox-bin-unwrapped.overrideAttrs (attrs: {
    postInstall = ''
      echo '${(builtins.toJSON {
        policies = {
          DisableTelemetry = true;
          DisableFirefoxStudies = true;
          EnableTrackingProtection = {
            Value = true;
            Locked = true;
            Cryptomining = true;
            Fingerprinting = true;
          };
          DisablePocket = true;
          OverrideFirstRunPage = "";
          OverridePostUpdatePage = "";
          DontCheckDefaultBrowser = true;
          DisplayMenuBar = "default-off";
          SearchBar = "separate";
          ExtensionSettings = {
            # uBlock Origin:
            "uBlock0@raymondhill.net" = {
              install_url = "https://addons.mozilla.org/firefox/downloads/latest/ublock-origin/latest.xpi";
              installation_mode = "force_installed";
            };
          };
        };
      })}' > "$out/lib/firefox-bin-${attrs.version}/distribution/policies.json"
    '';
  });
  firefox-nightly =
    inputs
    .firefox-nightly
    .packages
    .${final.system}
    .firefox-nightly-bin
    .override (_: {
      # FIXME: not working
      # system-wide policies
      extraPolicies = {
        DisableTelemetry = true;
        DisableFirefoxStudies = true;
        EnableTrackingProtection = {
          Value = true;
          Locked = true;
          Cryptomining = true;
          Fingerprinting = true;
        };
        DisablePocket = true;
        OverrideFirstRunPage = "";
        OverridePostUpdatePage = "";
        DontCheckDefaultBrowser = true;
        DisplayMenuBar = "default-off";
        SearchBar = "separate";
        ExtensionSettings = {
          # uBlock Origin:
          "uBlock0@raymondhill.net" = {
            install_url = "https://addons.mozilla.org/firefox/downloads/latest/ublock-origin/latest.xpi";
            installation_mode = "force_installed";
          };
        };
      };
    });
})
