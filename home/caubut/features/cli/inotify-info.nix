{pkgs, ...}: {
  # find inodes by process name: inotify-info node
  # it will be black on black
  #
  # find the path
  # find $pwd -xdev -inum <inode number>
  #
  # pstree -p
  home.packages = with pkgs; [inotify-tools inotify-info lsof pstree time];
}
