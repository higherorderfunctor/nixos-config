{lib, ...}: {
  options.home.persistence = lib.mkOption {
    type = lib.types.attrsOf lib.types.anything;
    default = {};
    description = "Shim for standalone Home Manager (non-NixOS) to ignore home.persistence.";
  };
}
