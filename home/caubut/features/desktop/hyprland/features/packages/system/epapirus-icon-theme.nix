{pkgs, ...}: {
  home.packages = [
    pkgs.papirus-icon-theme
    #(pkgs.epapirus-icon-theme.override
    #  {
    #    withElementary = true;
    #  })
  ];
}
