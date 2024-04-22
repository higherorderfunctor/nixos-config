return {
  "akinsho/bufferline.nvim",
  commit = "f6f00d9ac1a51483ac78418f9e63126119a70709",
  dependencies = { "catppuccin/nvim" },
  opts = {
    options = {
      always_show_bufferline = true,
    },
    highlights = require("catppuccin.groups.integrations.bufferline").get(),
  },
  keys = {
    { "<S-Left>", "<Cmd>BufferLineMovePrev<CR>", desc = "Move Buffer Left" },
    { "<S-Right>", "<Cmd>BufferLineMoveNext<CR>", desc = "Move Buffer Right" },
  },
}
