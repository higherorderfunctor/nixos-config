return {
  "stevearc/oil.nvim",
  keys = {
    { "<leader>fo", "<cmd>Oil --float<cr>", desc = "Oil" },
  },
  opts = {
    default_file_explorer = false,
    columns = { "size", highlight = "Special" },
  },
  dependencies = { "nvim-tree/nvim-web-devicons" },
}
