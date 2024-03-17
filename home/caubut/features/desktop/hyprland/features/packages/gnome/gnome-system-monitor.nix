{pkgs, ...}: {
  # shows you what programs are running and how much processor time, memory, and disk space are being used
  home.packages = [pkgs.gnome.gnome-system-monitor];
}
