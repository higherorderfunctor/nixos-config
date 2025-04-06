{pkgs, ...}: {
  environment.systemPackages = with pkgs; [
    oath-toolkit
    vpn-slice
  ];
  # networking.openconnect = {
  #   package = pkgs.openconnect_openssl;
  #   interfaces.openconnect0 = {
  #     gateway = "gateway.example.com";
  #     passwordFile = "/var/lib/secrets/openconnect-passwd";
  #     protocol = "anyconnect";
  #     user = "example-user";
  #   };
  # };
}
