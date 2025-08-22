return {
  "akinsho/bufferline.nvim",
  dependencies = { "catppuccin" },
  -- TODO: Remove this once https://github.com/LazyVim/LazyVim/pull/6354 is merged
  init = function()
    local bufline = require("catppuccin.groups.integrations.bufferline")
    bufline.get = bufline.get_theme
  end,
  opts = function(_, opts)
    local highlights = require("catppuccin.groups.integrations.bufferline").get_theme()(opts.highlights or {})
    -- opts.options.always_show_bufferline = true
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
