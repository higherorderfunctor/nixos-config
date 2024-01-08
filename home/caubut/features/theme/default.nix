{
  config,
  lib,
  ...
}:
with lib; let
  cfg = cfg.theme;
in {
  options.theme = {
    theme = mkOption {
      type = type.str;
    };
    blue = mkOption {
      type = types.str;
      default = "#0000ff";
    };
  };

  config = mkIf cfg.theme {
    imports = [./${cfg.theme}.nix];
  };
}
