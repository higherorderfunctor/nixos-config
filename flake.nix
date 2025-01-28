{
  description = "NixOS Configuration";
  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    nixpkgs-master.url = "github:NixOS/nixpkgs";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    # nixpkgs-91594d11.url = "github:Nixos/nixpkgs?rev=91594d11a2248ebe00f45f6b9be63fe264bb74e1";
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
      url = "github:hyprwm/Hyprland";
      # inputs = {
      #   nixpkgs.follows = "hyprland/nixpkgs";
      #   systems.follows = "hyprland/systems";
      #   hyprutils.follows = "hyprland/hyprutils";
      #   hyprlang.follows = "hyprland/hyprlang";
      #   hyprgraphics.follows = "hyprland/hyprgraphics";
      #   # hyprwayland-scanner.follows = "hyprland/hyprwayland-scanner";
      # };
    };
    # hyprwayland-scanner = {
    #   url = "github:hyprwm/hyprwayland-scanner";
    #   # inputs = {
    #   #   nixpkgs.follows = "hyprland/nixpkgs";
    #   #   systems.follows = "hyprland/systems";
    #   # };
    # };
    # hyprgraphics.follows = "hyprgraphics";
    # url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    # url = "git+https://github.com/hyprwm/Hyprland?submodules=1&rev=6e5804b53de753f24953d9d647940df66bc68f6d";
    # hyprgraphics = {
    #   # url = "git+file:///home/caubut/Documents/projects/hyprland-plugins";
    #   url = "github:hyprwm/hyprgraphics";
    #   inputs = {
    #     # hyprland.follows = "hyprland";
    #     nixpkgs.follows = "hyprland/nixpkgs";
    #     systems.follows = "hyprland/systems";
    #     hyprutils.follows = "hyprland/hyprutils";
    #   };
    # };
    hyprland-plugins = {
      # url = "git+file:///home/caubut/Documents/projects/hyprland-plugins";
      url = "github:hyprwm/hyprland-plugins";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprland.follows = "hyprland";
      };
    };
    hyprlock = {
      url = "github:hyprwm/hyprlock";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprlang.follows = "hyprland/hyprlang";
        hyprutils.follows = "hyprland/hyprutils";
        hyprgraphics.follows = "hyprland/hyprgraphics";
        # FIXME: pinned 4.4 but hyprland is only pinned to 4.2
        hyprwayland-scanner.follows = "hyprland/hyprwayland-scanner";
        # hyprwayland-scanner.follows = "hyprwayland-scanner";
      };
    };
    hypridle = {
      url = "github:hyprwm/hypridle";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprlang.follows = "hyprland/hyprlang";
        hyprutils.follows = "hyprland/hyprutils";
      };
    };
    hyprpicker = {
      url = "github:hyprwm/hyprpicker";
      inputs = {
        nixpkgs.follows = "hyprland/nixpkgs";
        systems.follows = "hyprland/systems";
        hyprutils.follows = "hyprland/hyprutils";
        hyprwayland-scanner.follows = "hyprland/hyprwayland-scanner";
      };
    };
    isd.url = "github:isd-project/isd";
    impermanence = {
      url = "github:nix-community/impermanence";
    };
    neovim-src = {
      url = "github:neovim/neovim";
      flake = false;
    };
    neovim-nightly-overlay = {
      url = "github:nix-community/neovim-nightly-overlay";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        # neovim-src.follows = "neovim-src";
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
    # nix flake lock --update-input nixpkgs --update-input tmux-which-key
    tmux-which-key = {
      url = "github:higherorderfunctor/tmux-which-key?ref=feat/adds-nix-flake";
      # url = "git+file:///home/caubut/Documents/projects/tmux-which-key";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    wezterm = {
      url = "github:wez/wezterm?dir=nix";
      # cachix
      # inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    home-manager,
    ...
  } @ inputs: let
    inherit (self) outputs;
    lib = (nixpkgs.lib.extend (import ./lib {inherit inputs;})) // home-manager.lib;
    forAllSystems = f: nixpkgs.lib.genAttrs nixpkgs.lib.systems.flakeExposed (system: f (pkgsFor system));
    pkgsFor = system:
      import nixpkgs {
        inherit system;
        overlays = import ./overlays {inherit inputs lib;};
        config = {
          allowUnfree = true;
          permittedInsecurePackages = [
            "electron-31.7.7" # standard notes
            #   "olm-3.2.16" # ???
          ];
        };
      };
  in {
    nixosModules = import ./modules/nixos;
    # TODO: tuck someplace else to remove the warning
    homeManagerModules = import ./modules/home-manager;

    formatter = forAllSystems (pkgs: pkgs.alejandra);

    nixosConfigurations = {
      live-cd-minimal-x86_64-linux = lib.nixosSystem {
        modules = [./hosts/live-cd-minimal];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor "x86_64-linux";
      };
      live-cd-graphical-x86_64-linux = lib.nixosSystem {
        modules = [./hosts/live-cd-graphical];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor "x86_64-linux";
      };
      beelink-ser7 = lib.nixosSystem {
        modules = [./hosts/beelink-ser7];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor "x86_64-linux";
      };
      vm = lib.nixosSystem {
        modules = [./hosts/vm];
        specialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor "x86_64-linux";
      };
    };

    homeConfigurations = {
      "caubut@z690-ud-ddr4" = lib.homeManagerConfiguration {
        modules = [./home/caubut/hosts/z690-ud-ddr4];
        extraSpecialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor "x86_64-linux";
      };
      "caubut@precision-7760" = lib.homeManagerConfiguration {
        modules = [./home/caubut/hosts/precision-7760];
        extraSpecialArgs = {inherit inputs outputs;};
        pkgs = pkgsFor "x86_64-linux";
      };
    };
  };
}
