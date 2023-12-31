{
  description = "NixOS Configuration";

  # dependency injection
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    home-manager.url = "github:nix-community/home-manager";
    nixos-hardware.url = "github:NixOS/nixos-hardware";
    disko = {
      url = "github:nix-community/disko";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  # implemenetation
  outputs = {
    # injected dependencies that should match inputs
    self,
    nixpkgs,
    home-manager,
    nixos-hardware,
    disko,
    # packs dependencies into a single object
  } @ inputs:
  # do-notation
  let
    inherit (self) outputs; # unpacks inputs into local scope
    lib = nixpkgs.lib // home-manager.lib; # { ...nixpkgs.lib, ...home-manager.lib }
    # static binding of supported systems
    systems = [
      "aarch64-linux"
      "x86_64-linux"
    ];
    # forEachSystem =     define named function
    #
    # f:                  arg to forEachSystem, higher-order function argument
    #
    # lib.genAttrs        keys.map((key) => { key: value }).reduce((acc, { k, v }) => { ...acc, k: v })
    # systems             keys arg to lib.genAttrs
    # (system:            start of map function with key as arg
    # f                   calls higher-order function argument
    # pkgsFor.${system}   passes pkgsFor[system] to f
    #
    # returns             { x86_64-linux: f(pkgsFor('x86_64-linux')), ... }
    forEachSystem = f: lib.genAttrs systems (system: f pkgsFor.${system});
    # for each system, generate a set of packages by importing nixpkgs and applying the configurated system and allowed
    # unfree packages
    #
    # looks like this is used to inject a semi-configured repo of pkgs to other modules
    pkgsFor = lib.genAttrs systems (system:
      import nixpkgs {
        # configures package set for current system key
        inherit system;
        # allows unfree packages
        config.allowUnfree = true;
      });
  in {
    # define system specific configurations
    nixosConfigurations = {
      # mini-pc
      boolink-ser7 = lib.nixosSystem {
        # add system specific module to this configuration
        modules = [./hosts/beelink-ser7];
        # passes { inputs, outputs } as extra args to next stage
        specialArgs = {inherit inputs outputs;};
      };
    };
  };
}
# formatter = forAllSystems (system: nixpkgs.legacyPackages.${system}.alejandra);
# export NIX_CONFIG="experimental-features = nix-command flakes"
