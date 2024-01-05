return {
  {
    "nvim-treesitter/playground",
    keys = {
      { "<leader>uP", "<cmd>TSPlaygroundToggle<cr>", desc = "Toggle Treesitter Playground" },
    },
    dependencies = { "nvim-treesitter/nvim-treesitter" },
  },
}
