{pkgs, ...}: {
  home.packages = [pkgs.onlykey];
}
# {
#   lib,
#   pkgs,
#   ...
# }: {
#   home.packages = [
#     (pkgs.onlykey.overrideAttrs (attrs: let
#       # parse the version from package.json
#       version = let
#         packageJson = lib.importJSON "${pkgs.path}/pkgs/tools/security/onlykey/package.json";
#         splits = builtins.split "^.*#v(.*)$" (builtins.getAttr "onlykey" (builtins.head packageJson));
#         matches = builtins.elemAt splits 1;
#         elem = builtins.head matches;
#       in
#         elem;
#
#       # this must be updated anytime this package is updated.
#       onlykeyPkg = "onlykey-git+https://github.com/trustcrypto/OnlyKey-App.git#v${version}";
#
#       # define a shortcut to get to onlykey.
#       onlykey = self."${onlykeyPkg}";
#
#       super = import "${pkgs.path}/pkgs/tools/security/onlykey/onlykey.nix" {
#         inherit pkgs;
#         inherit (pkgs.stdenv.hostPlatform) system;
#       };
#
#       self =
#         super
#         // {
#           "${onlykeyPkg}" = super."${onlykeyPkg}".override (attrs: {
#             # when installing packages, nw tries to download nwjs in its postInstall
#             # script. There are currently no other postInstall scripts, so this
#             # should not break other things.
#             npmFlags = attrs.npmFlags or "" + " --ignore-scripts";
#
#             # this package requires to be built in order to become runnable.
#             postInstall = ''
#               cd $out/lib/node_modules/${attrs.packageName}
#               npm run build
#
#               echo "Patching OnlyKeyWizard.js..."
#               substituteInPlace $out/lib/node_modules/${attrs.packageName}/build/scripts/onlyKey/OnlyKeyWizard.js \
#                 --replace "passwords.forEach" "passwords && Array.isArray(passwords) && passwords.forEach"
#
#               substituteInPlace $out/lib/node_modules/${attrs.packageName}/build/scripts/onlyKey/OnlyKeyWizard.js \
#                 --replace "chrome.privacy.services.passwordSavingEnabled.set" \
#                 "chrome.privacy && chrome.privacy.services && chrome.privacy.services.passwordSavingEnabled && chrome.privacy.services.passwordSavingEnabled.set"
#             '';
#           });
#         };
#
#       script = pkgs.writeShellScript "${onlykey.packageName}-starter-${onlykey.version}" ''
#         ${pkgs.nwjs}/bin/nw ${onlykey}/lib/node_modules/${onlykey.packageName}/build
#       '';
#     in {
#       installPhase = ''
#         runHook preInstall
#
#         mkdir -p $out/bin
#         ln -s ${script} $out/bin/onlykey
#
#         runHook postInstall
#       '';
#     }))
#   ];
# }
# # /nix/store/w8av4vrmc5kvb5s4f7qzxbh83sc71j2x-OnlyKey-5.5.0/lib/node_modules/OnlyKey/app/scripts/onlyKey/OnlyKeyWizard.js
# # /nix/store/w8av4vrmc5kvb5s4f7qzxbh83sc71j2x-OnlyKey-5.5.0/lib/node_modules/OnlyKey/build/scripts/onlyKey/OnlyKeyWizard.js
# # /nix/store/w8av4vrmc5kvb5s4f7qzxbh83sc71j2x-OnlyKey-5.5.0/lib/node_modules/OnlyKey/build/scripts/onlyKey/OnlyKeyWizard.js.map
