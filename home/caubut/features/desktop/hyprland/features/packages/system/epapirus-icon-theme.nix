{pkgs, ...}: {
  home.packages = [
    (pkgs.epapirus-icon-theme.override
      {
        withElementary = true;
      })
  ];
}
