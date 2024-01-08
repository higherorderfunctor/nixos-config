{
  lib,
  config,
  ...
}:
with lib; let
  cfg = config.colors;
in {
  options.colors = let
    mkColorOption = name: {
      inherit name;
      value = mkOption {
        type = types.strMatching "#[a-fA-F0-9]{6}";
        description = "Color ${name}.";
      };
    };
  in
    (listToAttrs (map mkColorOption [
      "black"
      "blue"
      "green"
      "red"
      "white"
    ]))
    // {
      highlights =
        {
          text = {
            fg = mkOption {
              type = types.strMatching "#[a-fA-F0-9]{6}";
              description = "Foreground color ${name}.";
            };
            bg = mkOption {
              type = types.nullOr (types.strMatching "#[a-fA-F0-9]{6}");
              description = "Background color ${name}.";
            };
          };
        }
        // (listToAttrs (map (name: {
            inherit name;
            value = {
              bg = mkOption {
                type = types.nullOr (types.strMatching "#[a-fA-F0-9]{6}");
                description = "Background color ${name}.";
              };
              fg = mkOption {
                type = types.nullOr (types.strMatching "#[a-fA-F0-9]{6}");
                description = "Foreground color ${name}.";
              };
            };
          }) [
            "error"
            "success"
          ]));
    };

  config.colors = {
    black = mkDefault "#000000";
    blue = mkDefault "#0000ff";
    green = mkDefault "#00ff00";
    red = mkDefault "#ff0000";
    white = mkDefault "#ffffff";
    highlights = {
      text = {
        fg = cfg.white;
        bg = null;
      };
      error = {
        fg =
          if cfg.red != null
          then cfg.red
          else cfg.highlights.text;
        bg = null;
      };
      success = {
        fg =
          if cfg.green != null
          then cfg.green
          else cfg.highlights.text;
        bg = null;
      };
    };
  };
}
