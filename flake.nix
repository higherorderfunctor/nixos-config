{
  description = "NixOS Configuration";

  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    nixpkgs-master.url = "github:Nixos/nixpkgs?rev=07f3a13157c65b871e701ecf1eefaa00cb34187a";
    home-manager = {
      url = "github:nix-community/home-manager";
    };
    ags = {
      url = "github:Aylur/ags";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    astal = {
      url = "github:Aylur/astal";
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
    hyprland = {
      # url = "github:hyprwm/Hyprland";
      url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
      # url = "git+https://github.com/andresilva/Hyprland?ref=nix-build-improvements&submodules=1";
    };
    hyprland-plugins = {
      url = "github:hyprwm/hyprland-plugins";
      inputs.hyprland.follows = "hyprland";
    };
    hyprlock = {
      url = "github:hyprwm/hyprlock";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprlang.follows = "hyprland/hyprlang";
      };
    };
    hypridle = {
      url = "github:hyprwm/hypridle";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprlang.follows = "hyprland/hyprlang";
      };
    };
    hyprpicker = {
      url = "github:hyprwm/hyprpicker";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
      };
    };
    impermanence = {
      url = "github:nix-community/impermanence";
    };
    neovim-nightly-overlay = {
      url = "github:nix-community/neovim-nightly-overlay";
      inputs = {
        nixpkgs.follows = "nixpkgs";
      };
    };
    nixd = {
      url = "github:nix-community/nixd";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nix-index-database = {
      url = "github:mic92/nix-index-database";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nix-gl-host = {
      url = "github:numtide/nix-gl-host";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nixos-hardware = {
      url = "github:nixos/nixos-hardware";
    };
    nvfetcher = {
      url = "github:berberman/nvfetcher";
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
    ...
  } @ inputs: let
    inherit (self) outputs;
    lib = (nixpkgs.lib.extend (import ./lib self)) // home-manager.lib;
    systems = ["x86_64-linux" "aarch64-linux"];
    forAllSystems = f: lib.genAttrs systems (system: f pkgsFor.${system});
    pkgsFor = lib.genAttrs systems (system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
        overlays = import ./overlays {inherit inputs lib;};
      });
  in {
    nixosModules = import ./modules/nixos;
    # TODO: tuck someplace else to remove the warning
    homeManagerModules = import ./modules/home-manager;

    formatter = forAllSystems (pkgs: pkgs.alejandra);

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

    homeConfigurations = {
      "caubut@z690-ud-ddr4" = lib.homeManagerConfiguration {
        modules = [./home/caubut/hosts/z690-ud-ddr4];
        extraSpecialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor.x86_64-linux;
      };
      "caubut@precision-7760" = lib.homeManagerConfiguration {
        modules = [./home/caubut/hosts/precision-7760];
        extraSpecialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor.x86_64-linux;
      };
    };
  };
}
