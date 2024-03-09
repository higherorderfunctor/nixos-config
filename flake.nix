{
  description = "NixOS Configuration";

  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    home-manager = {
      url = "github:nix-community/home-manager";
    };
    ags = {
      url = "github:Aylur/ags";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    disko = {
      url = "github:nix-community/disko";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    firefox-nightly = {
      url = "github:nix-community/flake-firefox-nightly";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    hardware = {
      url = "github:nixos/nixos-hardware";
    };
    hyprland = {
      url = "github:hyprwm/Hyprland";
    };
    impermanence = {
      url = "github:nix-community/impermanence";
    };
    neovim-nightly-overlay = {
      url = "github:nix-community/neovim-nightly-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nix-index-database = {
      url = "github:Mic92/nix-index-database";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nix-gl-host = {
      url = "github:numtide/nix-gl-host";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    rust-overlay = {
      url = "github:oxalica/rust-overlay";
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
    neovim-nightly-overlay,
    nix-gl-host,
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
          (_: _: {firefox-nightly = inputs.firefox-nightly.packages.${system}.firefox-nightly-bin;})
          (_: _: {nix-gl-host = nix-gl-host.defaultPackage.${system};})
        ];
      });
  in {
    homeManagerModules = import ./modules/home-manager;

    formatter = forAllSystems (pkgs: pkgs.alejandra);

    nixosConfigurations = {
      #   live-cd-minimal-x86_64-linux = lib.nixosSystem {
      #     modules = [./hosts/live-cd-minimal];
      #     specialArgs = {inherit inputs outputs;};
      #     pkgs = pkgsFor.x86_64-linux;
      #   };
      #   live-cd-graphical-x86_64-linux = lib.nixosSystem {
      #     modules = [./hosts/live-cd-graphical];
      #     specialArgs = {inherit inputs outputs;};
      #     pkgs = pkgsFor.x86_64-linux;
      #   };
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

    homeConfigurations = {
      "caubut@z690-ud-ddr4" = lib.homeManagerConfiguration {
        pkgs = pkgsFor.x86_64-linux;
        extraSpecialArgs = {inherit inputs outputs;};
        modules = [
          ./home/caubut/hosts/z690-ud-ddr4
        ];
      };
      "caubut@precision-7760" = lib.homeManagerConfiguration {
        pkgs = pkgsFor.x86_64-linux;
        extraSpecialArgs = {inherit inputs outputs;};
        modules = [
          ./home/caubut/hosts/precision-7760
        ];
      };
    };
  };
}
