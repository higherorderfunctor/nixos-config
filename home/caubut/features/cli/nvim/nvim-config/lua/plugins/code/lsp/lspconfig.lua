vim.lsp.set_log_level("debug")

return {
  "neovim/nvim-lspconfig",
  opts = {
    servers = {
      marksman = {},
      nil_ls = {},
      nixd = {},
    },
  },
  init = function()
    local keys = require("lazyvim.plugins.lsp.keymaps").get()
    -- change a keymap
    -- keys[#keys + 1] = { "K", "<cmd>echo 'hello'<cr>" }
    -- disable a keymap
    -- keys[#keys + 1] = { "K", false }
    -- add a keymap
    keys[#keys + 1] = { "<leader>cz", "<cmd>LspRestart<cr>", desc = "Restart LSP" }
  end,
}
