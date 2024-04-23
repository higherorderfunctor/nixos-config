return {
  "akinsho/bufferline.nvim",
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
