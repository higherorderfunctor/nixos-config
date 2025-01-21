_: _: prev: {
  # fetchurl = prev.fetchurl.override (args:
  #   args
  #   // {
  #     url = builtins.replaceStrings ["https://git.savannah.gnu.org"] ["mirror://savannah"] args.url;
  #   });
}
