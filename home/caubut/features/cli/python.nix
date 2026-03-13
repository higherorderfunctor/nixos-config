{pkgs, ...}: {
  home.packages = [
    (pkgs.python314.withPackages (ps: with ps; [
      ollama      # For kiro interaction-analysis skill
      psycopg2    # For kiro-cortex database migrations
    ]))
  ];
}
