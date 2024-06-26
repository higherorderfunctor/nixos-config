{
  description = "NixOS Configuration";

  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    nixpkgs-f7e10dc9.url = "github:Nixos/nixpkgs?rev=f7e10dc9f1e41773a2ba10969735633a876eb28f";
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
      url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
      # url = "git+https://github.com/hyprwm/Hyprland?submodules=1&rev=6e5804b53de753f24953d9d647940df66bc68f6d";
    };
    hyprland-plugins = {
      # url = "git+file:///home/caubut/Documents/projects/hyprland-plugins";
      url = "github:hyprwm/hyprland-plugins";
      inputs.hyprland.follows = "hyprland";
    };
    hyprlock = {
      url = "github:hyprwm/hyprlock";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprlang.follows = "hyprland/hyprlang";
        hyprutils.follows = "hyprland/hyprutils";
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
        overlays = import ./overlays {inherit inputs lib;};
        config = {
          allowUnfree = true;
          permittedInsecurePackages = [
            "electron-27.3.11" # standard notes
          ];
        };
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
