{
  lib,
  config,
  ...
}:
with lib; let
  cfg = config.colors;
  highlights = [
    "text"
    "prompt0"
    "prompt1"
    "prompt2"
    "username"
    "hostname"
    "directory"
    "git"
    "error"
    "success"
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
      "cyan"
      "green"
      "magenta"
      "red"
      "white"
      "yellow"
    ]))
    // {
      highlights = listToAttrs (map (name: {
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
        highlights);
    };

  config.colors = {
    black = mkDefault "#000000";
    blue = mkDefault "#0000ff";
    cyan = mkDefault "#00ffff";
    green = mkDefault "#00ff00";
    magenta = mkDefault "#ff00ff";
    red = mkDefault "#ff0000";
    white = mkDefault "#ffffff";
    yellow = mkDefault "#ffff00";
    highlights =
      (listToAttrs (map (name: {
          inherit name;
          value = {
            fg = mkDefault cfg.white;
            bg = mkDefault null;
          };
        }) (filter (item: item != "error" && item != "success")
          highlights)))
      // {
        error = {
          fg = mkDefault cfg.red;
          bg = mkDefault null;
        };
        success = {
          fg = mkDefault cfg.green;
          bg = mkDefault null;
        };
      };
  };
}
