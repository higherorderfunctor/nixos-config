#! /nix/store/a1s263pmsci9zykm5xcdf7x9rv26w6d5-bash-5.2p26/bin/bash -e
GTK_PATH=${GTK_PATH:+':'$GTK_PATH':'}
if [[ $GTK_PATH != *':''/nix/store/vlakm0775d8k0s5zh3n989pdidhnnnbz-libcanberra-0.30/lib/gtk-3.0/'':'* ]]; then
	GTK_PATH=$GTK_PATH'/nix/store/vlakm0775d8k0s5zh3n989pdidhnnnbz-libcanberra-0.30/lib/gtk-3.0/'
fi
GTK_PATH=${GTK_PATH#':'}
GTK_PATH=${GTK_PATH%':'}
export GTK_PATH
export FONTCONFIG_FILE=${FONTCONFIG_FILE-'/nix/store/s9gfad385if5ga57hrnbzha7kj87d9al-fonts.conf'}
export NIXOS_OZONE_WL=${NIXOS_OZONE_WL:-${WAYLAND_DISPLAY:+1}}
gdb --args "/nix/store/7al0l5k1lclgpkb1ip5k0czqick46hjs-bruno-1.13.0/share/Bruno/.bruno-wrapped" --no-sandbox "${NIXOS_OZONE_WL:+${WAYLAND_DISPLAY:+--enable-features=UseOzonePlatform --ozone-platform=wayland}}" "$@"

# #! /nix/store/a1s263pmsci9zykm5xcdf7x9rv26w6d5-bash-5.2p26/bin/bash -e
# GTK_PATH=${GTK_PATH:+':'$GTK_PATH':'}
# if [[ $GTK_PATH != *':''/nix/store/vlakm0775d8k0s5zh3n989pdidhnnnbz-libcanberra-0.30/lib/gtk-3.0/'':'* ]]; then
# 	GTK_PATH=$GTK_PATH'/nix/store/vlakm0775d8k0s5zh3n989pdidhnnnbz-libcanberra-0.30/lib/gtk-3.0/'
# fi
# GTK_PATH=${GTK_PATH#':'}
# GTK_PATH=${GTK_PATH%':'}
# export GTK_PATH
# export FONTCONFIG_FILE=${FONTCONFIG_FILE-'/nix/store/s9gfad385if5ga57hrnbzha7kj87d9al-fonts.conf'}
# export NIXOS_OZONE_WL=${NIXOS_OZONE_WL:-${WAYLAND_DISPLAY:+1}}
# export LD_LIBRARY_PATH=/nix/store/ncwrra4bx8rl39f4bcs4ykav3y98m2lp-libglvnd-1.7.0/lib:/nix/store/2aiiq43d68mvxqig2g6limqrzaqcadzi-bruno-1.13.0/lib
# env | grep -E '^(GTK_PATH|FONTCONFIG_FILE|NIXOS_OZONE_WL|LD_LIBRARY_PATH)='
# #echo "$0" "/nix/store/2aiiq43d68mvxqig2g6limqrzaqcadzi-bruno-1.13.0/share/Bruno/.bruno-wrapped" --no-sandbox "${NIXOS_OZONE_WL:+${WAYLAND_DISPLAY:+--enable-features=UseOzonePlatform --ozone-platform=wayland}}" "$@"
#
# gdb --args "/nix/store/2aiiq43d68mvxqig2g6limqrzaqcadzi-bruno-1.13.0/share/Bruno/.bruno-wrapped" --no-sandbox --enable-features=UseOzonePlatform --ozone-platform=wayland
#
# # [2063888:0415/154123.088545:ERROR:egl_util.cc(44)] Failed to load GLES library: libGLESv2.so.2: libGLESv2.so.2: cannot open shared object file: No such file or directory
