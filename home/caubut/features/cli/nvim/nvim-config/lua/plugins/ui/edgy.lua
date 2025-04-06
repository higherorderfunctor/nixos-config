return {
  -- adds aerial to the list of files that don't replace the current buffer
  {
    "nvim-neo-tree/neo-tree.nvim",
    opts = function(_, opts)
      opts.open_files_do_not_replace_types = opts.open_files_do_not_replace_types
        or { "terminal", "Trouble", "qf", "Outline", "trouble", "aerial" }
      table.insert(opts.open_files_do_not_replace_types, "edgy")
    end,
  },
  {
    "folke/edgy.nvim",
  },
}
