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
    systems = ["x86_64-linux" "aarch64-linux"];
    forEachSystem = f: lib.genAttrs systems (system: f pkgsFor.${system});
    pkgsFor = lib.genAttrs systems (system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      });
    mkApp = scriptName: system: {
      type = "app";
      program = "${(pkgsFor.${system}.writeShellScriptBin scriptName ''
        #!/usr/bin/env bash
        exec ${self}/apps/${system}/${scriptName}
      '')}/bin/${scriptName}";
    };
    mkApp2 = scriptName: system: {
      type = "app";
      program = "${(pkgsFor.${system}.writeShellScriptBin scriptName ''
        #!/usr/bin/env bash
        exec ${self}/apps/${system}/${scriptName}
      '')}/bin/${scriptName}";
    };
  in {
    # add custom packages
    packages = forEachSystem (pkgs: import ./pkgs {inherit pkgs;});

    # add custom apps
    apps = lib.genAttrs systems (system: {
      nvme-lbaf = flake-utils.lib.mkApp {drv = pkgsFor.${system}.nvme-cli;};
    });
    # apps = lib.genAttrs systems (system: {
    #   nvme-lbaf = mkApp "nvme-lbaf" system;
    # });

    # set formmatter for this flake
    formatter = forEachSystem (pkgs: pkgs.alejandra);

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
