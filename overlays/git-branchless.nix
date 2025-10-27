{inputs, ...}: (
  final: prev: (
    inputs.git-branchless.overlays.default final (
      prev
      // {
        git-branchless = prev.git-branchless.overrideAttrs (
          _: {
            postPatch = null;
          }
        );
      }
    )
  )
)
