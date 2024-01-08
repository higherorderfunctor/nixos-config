{
  lib,
  config,
  ...
}:
with lib; let
  cfg = config.colors;
  highlights = [
    "text"
    "error"
    "success"
  ];
  sixteenColors = [
    "color0"
    "color1"
    "color2"
    "color3"
    "color4"
    "color5"
    "color6"
    "color7"
    "color8"
    "color9"
    "color10"
    "color11"
    "color12"
    "color13"
    "color14"
    "color15"
  ];
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
              fg = mkOption {
                type = types.strMatching "#[a-fA-F0-9]{6}";
                description = "Foreground color ${name}.";
              };
              bg = mkOption {
                type = types.nullOr (types.strMatching "#[a-fA-F0-9]{6}");
                description = "Background color ${name}.";
              };
            };
          })
          (highlights
            ++ sixteenColors)));
    };

  config.colors = {
    black = mkDefault "#000000";
    blue = mkDefault "#0000ff";
    green = mkDefault "#00ff00";
    red = mkDefault "#ff0000";
    white = mkDefault "#ffffff";
    highlights =
      {
        text = {
          fg = mkDefault cfg.white;
          bg = mkDefault null;
        };
        error = {
          fg = mkDefault cfg.red;
          bg = mkDefault null;
        };
        success = {
          fg = mkDefaut cfg.green;
          bg = mkDefault null;
        };
      }
      // (listToAttrs (map (name: {
          inherit name;
          value = mkDefault cfg.highlights.text;
        })
        sixteenColors));
  };
}
