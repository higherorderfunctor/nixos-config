_: {
  disko.devices.lvm_vg.cryptlvm.lvs.root.content.subvolumes."/swap".swap.swapfile.size = "8G";
  boot.kernel.sysctl = {
    vm.swapiness = 1;
    vm.vfs_cache_pressure = 50;
  };
}
