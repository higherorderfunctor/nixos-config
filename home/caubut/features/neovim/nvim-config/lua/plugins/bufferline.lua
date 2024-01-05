return {
  "akinsho/bufferline.nvim",
  keys = {
    { "<S-Left>",  "<Cmd>BufferLineMovePrev<CR>", desc = "Move Buffer Left" },
    { "<S-Right>", "<Cmd>BufferLineMoveNext<CR>", desc = "Move Buffer Right" },
  },
  opts = {
    options = {
      always_show_bufferline = true,
    },
  },
}
