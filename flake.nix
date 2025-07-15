{
  description = "NixOS Configuration";
  inputs = {
    nixos.url = "github:nixos/nixpkgs/nixos-unstable";
    # nixpkgs-master.url = "github:NixOS/nixpkgs";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    # nixpkgs-91594d11.url = "github:Nixos/nixpkgs?rev=91594d11a2248ebe00f45f6b9be63fe264bb74e1";
    home-manager = {
      url = "github:nix-community/home-manager";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    ags = {
      url = "github:Aylur/ags";
      inputs.nixpkgs.follows = "nixpkgs";
      inputs.astal.follows = "astal";
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
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-compat.follows = "flake-compat";
        lib-aggregate.follows = "lib-aggregate";
      };
    };
    flake-compat = {
      url = "github:nix-community/flake-compat";
    };
    flake-parts = {
      url = "github:hercules-ci/flake-parts";
      inputs = {
        nixpkgs-lib.follows = "nixpkgs-lib";
      };
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs = {
        systems.follows = "systems";
      };
    };
    git-branchless = {
      url = "github:arxanas/git-branchless";
      inputs = {
        nixpkgs.follows = "nixpkgs";
      };
    };
    git-hooks = {
      url = "github:cachix/git-hooks.nix";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-compat.follows = "flake-compat";
      };
    };
    hercules-ci-effects = {
      url = "github:hercules-ci/hercules-ci-effects";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-parts.follows = "flake-parts";
      };
    };
    hyprland = {
      url = "github:hyprwm/Hyprland";
      # inputs = {
      #   pre-commit-hooks.follows = "git-hooks";
      #   # nixpkgs.follows = "hyprland/nixpkgs";
      #   # systems.follows = "hyprland/systems";
      #   # hyprutils.follows = "hyprland/hyprutils";
      #   # hyprlang.follows = "hyprland/hyprlang";
      #   # hyprgraphics.follows = "hyprland/hyprgraphics";
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
        hyprland-protocols.follows = "hyprland/hyprland-protocols";
        hyprlang.follows = "hyprland/hyprlang";
        hyprutils.follows = "hyprland/hyprutils";
        hyprwayland-scanner.follows = "hyprland/hyprwayland-scanner";
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
    systems = {
      url = "github:nix-systems/default";
    };
    isd = {
      url = "github:isd-project/isd";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        # nix-appimage.follows = "nix-appimage";
        systems.follows = "systems";
      };
    };
    impermanence = {
      url = "github:nix-community/impermanence";
    };
    lib-aggregate = {
      url = "github:nix-community/lib-aggregate";
      inputs = {
        nixpkgs-lib.follows = "nixpkgs-lib";
        flake-utils.follows = "flake-utils";
      };
    };
    # nix-appimage = {
    #   url = "github:ralismark/nix-appimage";
    #   inputs = {
    #     nixpkgs.follows = "nixpkgs";
    #     flake-compat.follows = "flake-compat";
    #     flake-utils.follows = "flake-utils";
    #   };
    # };
    nix-gl-host = {
      url = "github:numtide/nix-gl-host";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nix-index-database = {
      url = "github:mic92/nix-index-database";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    nixd = {
      url = "github:nix-community/nixd";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-parts.follows = "flake-parts";
        treefmt-nix.follows = "treefmt-nix";
      };
    };
    nixos-hardware = {
      url = "github:nixos/nixos-hardware";
    };
    neovim-src = {
      url = "github:neovim/neovim";
      flake = false;
    };
    neovim-nightly-overlay = {
      url = "github:nix-community/neovim-nightly-overlay";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-compat.follows = "flake-compat";
        flake-parts.follows = "flake-parts";
        git-hooks.follows = "git-hooks";
        hercules-ci-effects.follows = "hercules-ci-effects";
        neovim-src.follows = "neovim-src";
        treefmt-nix.follows = "treefmt-nix";
      };
    };
    nixpkgs-lib = {
      url = "github:nix-community/nixpkgs.lib";
    };
    nvfetcher = {
      url = "github:berberman/nvfetcher";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        flake-compat.follows = "flake-compat";
        flake-utils.follows = "flake-utils";
      };
    };
    rust-overlay = {
      url = "github:oxalica/rust-overlay";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    sops-nix = {
      url = "github:mic92/sops-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    treefmt-nix = {
      url = "github:numtide/treefmt-nix";
      inputs = {
        nixpkgs.follows = "nixpkgs";
      };
    };
    wezterm = {
      url = "github:wez/wezterm?dir=nix";
      # cachix
      # inputs.nixpkgs.follows = "nixpkgs";
      # inputs.rust-overlay.follows = "rust-overlay";
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
