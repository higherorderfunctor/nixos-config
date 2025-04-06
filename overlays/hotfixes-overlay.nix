{
  lib,
  inputs,
  ...
}: (final: prev: {
  # FIXME: https://hydra.nixos.org/build/265233452
  # nix run nixpkgs#hydra-check webkitgtk_6_0
  # inherit
  #   (inputs.nixpkgs-91594d11.legacyPackages.${final.system})
  #   ungoogled-chromium
  #   webkitgtk_6_0
  #   webkitgtk_4_1
  #   ;
  # evolution-data-server
  # evolution
  # networkmanager-openconnect
  # gnome-calendar
  # gnome-calculator

  # FIXME: https://github.com/NixOS/nixpkgs/pull/307505
  # https://github.com/NixOS/nixpkgs/pull/307476

  # inherit (inputs.nixpkgs-master.legacyPackages.${final.system}) rocmPackages rocmPackages_5;
  vpn-slice = final.python3Packages.buildPythonApplication rec {
    inherit
      (prev.vpn-slice)
      pname
      version
      src
      postPatch
      # build-system
      # dependencies
      doCheck
      passthru
      meta
      ;
    pyproject = true;
    build-system = [
      final.python3Packages.setuptools
    ];

    dependencies = [
      final.python3Packages.setuptools # can be removed with next package update, upstream no longer has a dependency on distutils
      final.python3Packages.setproctitle
      final.python3Packages.dnspython
    ];
  };
  #   prev.vpn-slice.override
  #     (
  #       attrs:
  #       # Add new parameters and remove ```python3Packages```
  #         lib.removeAttrs (attrs
  #           // {
  #             inherit
  #               (attrs.python3Packages)
  #               setuptool
  #               setproctitle
  #               dnspython
  #               ;
  #           }) ["python3Packages"]
  #     ))
  #   .overrideAttrs (oldAttrs: let
  #     # Access the new parameters added in ```.override```
  #     pythonDeps = [oldAttrs.setuptool oldAttrs.setproctitle oldAttrs.dnspython];
  #   in {
  #     build-system = [
  #       oldAttrs.setuptools
  #     ];

  #     dependencies =
  #       pythonDeps
  #       ++ [
  #         oldAttrs.setuptools # Can be removed with the next package update
  #       ];
  #   });
  #buildPythonApplication rec {
  #  pname = "vpn-slice";
  #  version = "0.16.1";
  #  pyproject = true;
  #
  #  src = fetchFromGitHub {
  #    owner = "dlenski";
  #    repo = "vpn-slice";
  #    rev = "v${version}";
  #    sha256 = "sha256-T6VULLNRLWO4OcAsuTmhty6H4EhinyxQSg0dfv2DUJs=";
  #  };
  #
  #  postPatch =
  #    lib.optionalString stdenv.hostPlatform.isDarwin ''
  #      substituteInPlace vpn_slice/mac.py \
  #        --replace-fail "'/sbin/route'" "'${unixtools.route}/bin/route'"
  #    ''
  #    + lib.optionalString stdenv.hostPlatform.isLinux ''
  #      substituteInPlace vpn_slice/linux.py \
  #        --replace-fail "'/sbin/ip'" "'${iproute2}/bin/ip'" \
  #        --replace-fail "'/sbin/iptables'" "'${iptables}/bin/iptables'"
  #    '';
  #
  #  build-system = with python3Packages; [
  #    setuptools
  #  ];
  #
  #  dependencies = with python3Packages; [
  #    setuptools # can be removed with next package update, upstream no longer has a dependency on distutils
  #    setproctitle
  #    dnspython
  #  ];
  #
  #  doCheck = false;
  #
  #  passthru = {
  #    updateScript = nix-update-script { };
  #  };
  #
  #  meta = with lib; {
  #    homepage = "https://github.com/dlenski/vpn-slice";
  #    description = "vpnc-script replacement for easy and secure split-tunnel VPN setup";
  #    mainProgram = "vpn-slice";
  #    license = licenses.gpl3;
  #    maintainers = [ ];
  #  };
  #}
  # poetry = prev.poetry.overrideAttrs (attrs: {
  #   poetry = attrs.poetry.override {
  #     inherit (inputs.nixpkgs-master.legacyPackages.${final.system}.python312Packages) dulwich;
  #   };
  # });

  # poetry = prev.poetry.overrideAttrs (attrs: {
  #   propagatedBuildInputs = let
  #     dulwich = inputs.nixpkgs-master.legacyPackages.${final.system}.python312Packages.dulwich;
  #     filtered = final.lib.filter (pkg: pkg.pname or null != "dulwich") attrs.propagatedBuildInputs;
  #   in
  #     filtered ++ [(builtins.trace dulwich dulwich)];
  # });
  # inherit (inputs.nixpkgs-master.legacyPackages.${final.system}) spamassassin;
})
