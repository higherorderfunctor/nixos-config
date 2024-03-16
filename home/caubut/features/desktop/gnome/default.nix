{pkgs, ...}: {
  imports = [
    ./gnome-keyring.nix
    ./gnome-secrets.nix
  ];
  home.packages = with pkgs; [
    # glib may break stuff forget what its for
  ];
  # TODO: portal errors in journal
}
