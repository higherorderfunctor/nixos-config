{
  config,
  lib,
  pkgs,
  ...
}:
with lib; let
  cfg = config.programs.firefox;
  isArkenfoxEnabled = filterAttrs (profile: profiles.arkenfox.enable);
  arkenFoxProfiles = attrNames isArkenfoxEnabled cfg.profiles;
  configureArkenfox = name: {
    name = {
      extraConfig =
        lib.mkDefault ''
        '';
    };
  };

  numProfiles = builtins.length (builtins.attrNames cfq.profiles);
  enumeratedProfiles = builtins.map (index: {
    idx = index;
    val = arkenFoxProfiles.index;
  }) (builtins.genList (i: i) (builtins.length numProfiles));

  foo =
    mapAttrsRecursiveCond (attr: attr.idx < numProfiles) (name: profile: {
      inherit name;
      value = profile.arkenfox.enable;
    })
    enumeratedProfiles;
  # modifyProfiles = profiles:
  #   lib.mapAttrs (name: profile: {
  #     inherit (profile) foo; # Carry over the original `foo` attribute
  #     bar =
  #       if profile.foo
  #       then ""
  #       else profile.bar; # Conditionally modify `bar`
  #   })
  #   profiles;
in {
  ${cfg}.profiles = lib.mkOption {
    type = types.attrsOf (types.submodule {
      options.arkenfox.enable = lib.mkEnableOption "Enable Arkenfox user.js for the profile";
    });
    default = lib.mkDefault options.programs.firefox.profiles.default;
  };

  programs.firefox.profiles = foo;
}
#   config = lib.mkIf (lib.length (lib.attrNames config.programs.firefox.profiles) > 0) {
#   programs.firefox.profiles = lib.mapAttrs' (name: profile: {
#     inherit name;
#     value = profile.value // {
#       # Conditionally modify the profile here
#       # Example: Add `bar` attribute if `foo` is true
#       bar = if profile.value.foo or false then "your-modification" else profile.value.bar or "default";
#     };
#   }) config.programs.firefox.profiles;
# };
#   { lib, ... }:
#
# {
#   # Assuming the rest of your configuration is defined elsewhere
#
#   config = {
#     programs.firefox.profiles = let
#       # Original profiles definition
#       originalProfiles = config.programs.firefox.profiles;
#     in
#     # Map over the profiles to potentially modify them
#     lib.mapAttrs' (name: profile: let
#       # Check if arkenfox is enabled for this profile
#       arkenfoxEnabled = profile.arkenfox.enable or false; # Default to false if not set
#     in
#     {
#       # Return the profile name and potentially modified profile
#       name = name;
#       value = profile // {
#         # Conditionally modify extraConfig if arkenfox is enabled
#         extraConfig = if arkenfoxEnabled then
#           # Modify extraConfig here, e.g., append something
#           "${profile.extraConfig or ""} some-modification"
#         else
#           # Leave extraConfig unchanged if arkenfox is not enabled
#           profile.extraConfig or "";
#       };
#     }) originalProfiles;
#   };
# }
#
# ${cfg}.profiles =
#   lib.mkIf cfg.enable
#   (lib.mapAttrs (_: profile: {}) cfg.profiles);
# lib.mkIf profile.arkenfox.enable {
#  {name = profile;}
#      extraConfig = let
#        arkenfoxConfig = "${pkgs.arkenfox}/user.js";
#      in
#        if profile ? extraConfig && profile.extraConfig != "" then
#          lib.strings.concatStringsSep "\n" [profile.extraConfig arkenfoxConfig]
#        else
#          arkenfoxConfig;
#)
#c);
#config = mkIf cfg.enable {
# programs.firefox.profiles = lib.mapAttrs (name: profile: profile);
# lib.mapAttrs (name: profile: {})
# lib.mkIf profile.arkenfox.enable {
#   extraConfig = let
#     arkenfoxConfig = "${pkgs.arkenfox}/user.js";
#   in {};
#   # lib.mkIf (profile ? extraConfig && profile.extraConfig != "")
#   # # if extraConfig exists and is not empty, append
#   # lib.strings.concatStringsSep "\n" [
#   #   profile.extraConfig
#   #   arkenfoxConfig
#   # ]
#   # # else, just set to arkenfox user.js
#   # arkenfoxConfig;
# })
# cfg.profiles;
#};
#  options.programs.firefox = {
#    arkenfox = {
#      enable = lib.mkEnableOption "arkenfox support in profiles";
#      version = lib.mkOption {
#        description = "The version of arkenfox user.js used";
#        type = types.enum versions;
#        default = "master";
#      };
#    };
#    profiles = lib.mkOption {
#      type = types.attrsOf (types.submodule ({config, ...}: {
#        options.arkenfox = lib.mkOption {
#          description = "Setup arkenfox user.js in profile";
#          type = import ./type.nix {
#            extracted = ext;
#            inherit lib;
#          };
#          default = {};
#        };
#        config = lib.mkIf cfg.arkenfox.enable {
#          settings = config.arkenfox.flatSettings;
#        };
#      }));
#    };
#  };
