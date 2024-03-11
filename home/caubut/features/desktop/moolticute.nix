{pkgs, ...}: {
  home.packages = [pkgs.moolticute];
  # TODO: system services.udev.packages = [pkgs.moolticute.udev];
  # udev/lib/udev/rules.d/50-mooltipass.rules
  # # udev rules for allowing console user(s) and libusb access to Mooltipass Mini devices
  # ACTION!="add|change", GOTO="mooltipass_end"
  #
  # sudo vim /etc/udev/rules.d/50-mooltipass.rules
  #
  # # console user
  # SUBSYSTEM=="hidraw", ATTRS{idVendor}=="16d0", ATTRS{idProduct}=="09a0", MODE="0660", SYMLINK+="mooltipass_keyboard", TAG+="uaccess", TAG+="udev-acl"
  # SUBSYSTEM=="hidraw", ATTRS{idVendor}=="1209", ATTRS{idProduct}=="4321", MODE="0660", SYMLINK+="mooltipass_keyboard", TAG+="uaccess", TAG+="udev-acl"
  # # libusb
  # SUBSYSTEM=="usb", ATTRS{idVendor}=="16d0", ATTRS{idProduct}=="09a0", MODE="0660", SYMLINK+="mooltipass_device", TAG+="uaccess"
  # SUBSYSTEM=="usb", ATTRS{idVendor}=="1209", ATTRS{idProduct}=="4321", MODE="0660", SYMLINK+="mooltipass_device", TAG+="uaccess"
  #
  # # required for newer versions of bluez
  # SUBSYSTEM=="hidraw", KERNELS=="*1209:4321*", MODE="0660", SYMLINK+="mooltipass_keyboard", TAG+="uaccess", TAG+="udev-acl"
  #
  # LABEL="mooltipass_end"
  #
  # sudo udevadm control --reload-rules
}
