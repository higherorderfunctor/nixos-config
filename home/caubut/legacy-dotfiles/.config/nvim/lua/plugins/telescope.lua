return {
  {
    "benfowler/telescope-luasnip.nvim",
    keys = {
      { "<leader>cS", "<cmd>Telescope luasnip<cr>", desc = "Snippets" },
    },
    dependencies = {
      "nvim-telescope/telescope.nvim",
      "L3MON4D3/LuaSnip",
    },
  },
  {
    "nvim-telescope/telescope-symbols.nvim",
    dependencies = {
      "nvim-telescope/telescope.nvim",
    },
  },
}
