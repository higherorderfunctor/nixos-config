{pkgs, ...}: {
  home.packages = [
    (pkgs.python314.withPackages (ps: with ps; [
      ollama  # For kiro interaction-analysis skill
    ]))
  ];
}
