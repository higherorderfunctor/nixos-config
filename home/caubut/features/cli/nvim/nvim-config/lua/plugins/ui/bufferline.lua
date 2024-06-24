return {
  "akinsho/bufferline.nvim",
  dependencies = { "catppuccin" },
  opts = function(_, opts)
    local highlights = require("catppuccin.groups.integrations.bufferline").get()(opts.highlights or {})
    opts.options.always_show_bufferline = true
    return vim.list_extend(opts or {}, {
      options = {
        always_show_bufferline = true,
        style_preset = {
          require("bufferline").style_preset.no_italic,
        },
      },
      --- require("catppuccin.groups.integrations.bufferline").get()
      highlights = vim.list_extend(highlights, {}),
    })
  end,
  keys = {
    { "<S-Left>", "<Cmd>BufferLineMovePrev<CR>", desc = "Move Buffer Left" },
    { "<S-Right>", "<Cmd>BufferLineMoveNext<CR>", desc = "Move Buffer Right" },
  },
}
