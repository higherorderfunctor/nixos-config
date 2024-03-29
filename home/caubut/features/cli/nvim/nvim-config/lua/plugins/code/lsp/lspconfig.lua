return {
  "neovim/nvim-lspconfig",
  opts = {
    servers = {
      bashls = { mason = false },
      docker_compose_language_service = { mason = false },
      dockerls = { mason = false },
      jsonls = {
        cmd = { "vscode-json-languageserver", "--stdio" },
        mason = false,
      },
      lua_ls = { mason = false },
      marksman = { mason = false },
      nil_ls = { mason = false },
      nixd = { mason = false },
      yamlls = { mason = false },
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
