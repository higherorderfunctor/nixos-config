{
  description = "NixOS Configuration";

  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    hardware.url = "github:nixos/nixos-hardware";
    impermanence.url = "github:nix-community/impermanence";
    home-manager = {
      url = "github:nix-community/home-manager";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    neovim-nightly-overlay = {
      url = "github:nix-community/neovim-nightly-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    disko = {
      url = "github:nix-community/disko";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    sops-nix = {
      url = "github:mic92/sops-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nix-index-database = {
      url = "github:Mic92/nix-index-database";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    hyprland.url = "github:hyprwm/Hyprland";
    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    ags = {
      url = "github:Aylur/ags";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    firefox-nightly = {
      url = "github:nix-community/flake-firefox-nightly";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    home-manager,
    neovim-nightly-overlay,
    rust-overlay,
    ...
  } @ inputs: let
    inherit (self) outputs;
    lib = nixpkgs.lib // home-manager.lib;
    systems = ["x86_64-linux" "aarch64-linux"];
    forAllSystems = f: lib.genAttrs systems (system: f pkgsFor.${system});
    pkgsFor = lib.genAttrs systems (system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
        overlays = [
          neovim-nightly-overlay.overlays.default
          rust-overlay.overlays.default
        ];
      });
  in {
    # set formmatter for this flake
    formatter = forAllSystems (pkgs: pkgs.alejandra);

    # system configurations
    nixosConfigurations = {
      live-cd-minimal-x86_64-linux = lib.nixosSystem {
        modules = [./hosts/live-cd-minimal];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor.x86_64-linux;
      };
      live-cd-graphical-x86_64-linux = lib.nixosSystem {
        modules = [./hosts/live-cd-graphical];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor.x86_64-linux;
      };
      beelink-ser7 = lib.nixosSystem {
        modules = [./hosts/beelink-ser7];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor.x86_64-linux;
      };
      vm = lib.nixosSystem {
        modules = [./hosts/vm];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor.x86_64-linux;
      };
    };
  };
}
