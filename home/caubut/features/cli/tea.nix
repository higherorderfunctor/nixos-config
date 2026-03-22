{
  config,
  pkgs,
  ...
}: let
  username = "${config.home.username}";
  teaWrapped = pkgs.writeShellScriptBin "tea" ''
    TOKEN=$(cat ${config.sops.secrets."${username}-codeberg-token".path})
    export XDG_CONFIG_HOME="''${XDG_CONFIG_HOME:-$HOME/.config}"
    mkdir -p "$XDG_CONFIG_HOME/tea"
    cat > "$XDG_CONFIG_HOME/tea/config.yml" <<EOF
    logins:
    - name: codeberg
      url: https://codeberg.org
      token: $TOKEN
      default: true
      ssh_host: codeberg.org
    EOF
    exec ${pkgs.tea}/bin/tea "$@"
  '';
in {
  home.packages = [teaWrapped];
  sops.secrets = {
    "${username}-codeberg-token" = {
      mode = "400";
    };
  };
}
