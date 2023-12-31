{
  description = "NixOS Configuration";

  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    hardware.url = "github:nixos/nixos-hardware";
    home-manager.url = "github:nix-community/home-manager";
    impermanence.url = "github:nix-community/impermanence";
    neovim-nightly-overlay.url = "github:nix-community/neovim-nightly-overlay";
    disko = {
      url = "github:nix-community/disko";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    sops-nix = {
      url = "github:mic92/sops-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    home-manager,
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
  in {
    # add custom packages
    packages = forEachSystem (pkgs: import ./pkgs {inherit pkgs;});

    # set formmatter for this flake
    formatter = forEachSystem (pkgs: pkgs.alejandra);

    # system configurations
    nixosConfigurations = {
      live-cd-minimal-x86_64-linux = lib.nixosSystem {
        modules = [
          ./hosts/live-cd-minimal
          ./hosts/common/optional/minimal-x86_64-linux-hardware-configuration.nix
        ];
        specialArgs = {inherit inputs outputs;};
      };
      live-cd-graphical-x86_64-linux = lib.nixosSystem {
        modules = [
          ./hosts/live-cd-graphical
          ./hosts/common/optional/minimal-x86_64-linux-hardware-configuration.nix
        ];
        specialArgs = {inherit inputs outputs;};
      };
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
