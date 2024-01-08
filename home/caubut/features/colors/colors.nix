{lib, ...}:
with lib; {
  options.colors = let
    mkColorOption = name: {
      inherit name;
      value = mkOption {
        type = types.strMatching "#[a-fA-F0-9]{6}";
        description = "Color ${name}.";
      };
    };
  in
    listToAttrs (map mkColorOption [
      "blue"
      "red"
    ])
    // listToAttrs (map
      (name: [mkColorOption "${name}.fg" mkColorOption "${name}.fg"])
      [
        "error"
        "success"
      ]);
  config.colors = {
    blue = mkDefault "#0000ff";
    green = mkDefault "#00ff00";
    red = mkDefault "#ff0000";
    error = {fg = config.colors.red;};
  };
}
