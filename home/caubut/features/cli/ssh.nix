{
  config,
  ...
}: {
  services = {
    ssh-agent.enable = true;
  };

  # TODO: possible fix for known hosts? https://nixos.wiki/wiki/Home_Manager#Workaround_with_home_on_tmpfs_and_standalone_installation
  programs = {
    ssh = {
      enable = true;
      enableDefaultConfig = false;
      matchBlocks = {
        "*" = {
          addKeysToAgent = "yes";
        };
      };
    };
  };

  # persistence
  home.persistence = {
    "/persist${config.home.homeDirectory}".directories = [
      ".ssh"
    ];
  };
}
