{
  description = "NixOS Configuration";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    home-manager.url = "github:nix-community/home-manager";
    hardware.url = "github:nixos/nixos-hardware";
    flake-utils.url = "github:numtide/flake-utils";
    disko = {
      url = "github:nix-community/disko";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    home-manager,
    flake-utils,
    ...
  } @ inputs: let
    inherit (self) outputs;
    lib = nixpkgs.lib // home-manager.lib;
    systems = [
      "aarch64-linux"
      "x86_64-linux"
    ];
    forEachSystem = f: lib.genAttrs systems (system: f pkgsFor.${system});
    pkgsFor = lib.genAttrs systems (system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      });
    pkgs = flake-utils.lib.eachDefaultSystem (system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      });
  in {
    # add default packages
    packages = import ./pkgs {inherit pkgs;};

    # add custom scripts for this flake
    # PATH=${nixpkgs.legacyPackages.${system}.git}/bin:$PATH
    # echo "Running ${scriptName} for ${system}"
    apps = {
      nvme-lbaf = flake-utils.lib.mkApp {
        drv = "${(self.packages.writeShellScriptBin "nvme-lbaf" ''
          #!/usr/bin/env bash
          exec ${self}/apps/${self.system}/lvme-lbaf
        '')}/bin/lvme-lbaf";
      };
    };

    # set formmatter for this flake
    # formatter = pkgs.alejandra; TODO: uncomment after dev

    # system configurations
    nixosConfigurations = {
      beelink-ser7 = lib.nixosSystem {
        modules = [./hosts/beelink-ser7];
        specialArgs = {inherit inputs outputs;};
      };
      vm = lib.nixosSystem {
        modules = [./hosts/vm];
        specialArgs = {inherit inputs outputs;};
      };
    };
  };
}
