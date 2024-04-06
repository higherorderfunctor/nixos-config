{pkgs, ...}: {
  environment.systemPackages = with pkgs; [astalWithTypes];
  # FIXME: expose types in a consistent location for tsconfig, move into astal overlay
  environment.etc."astal/types".source = "${pkgs.astalWithTypes}/share/io.Aylur.Astal/types";
}
