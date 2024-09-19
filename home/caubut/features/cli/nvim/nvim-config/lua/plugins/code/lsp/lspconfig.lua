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
      -- eslint = { cmd = { "bunx", "--bun", "vscode-eslint-language-server", "--stdio" } },
      eslint = {
        -- cmd = { "bun", "--bun", "vscode-eslint-language-server", "--stdio" },
        settings = {
          cache = true,
          --debug = "*",
          useFlatConfig = true, -- set if using flat config
          --overrideConfigFile = vim.fn.getcwd() .. "/eslint.config.ts",
          experimental = {
            useFlatConfig = nil, -- option not in the latest eslint-lsp
          },
        },
      },
      lua_ls = {
        cmd = { "/etc/profiles/per-user/caubut/bin/lua-language-server", "--stdio" },
        mason = false,
      },
      marksman = { mason = false },
      nil_ls = { mason = false },
      nixd = { mason = false },
      yamlls = {
        cmd = { "/etc/profiles/per-user/caubut/bin/yaml-language-server", "--stdio" },
        mason = false,
      },
      -- tsserver = {
      --   cmd = {
      --     "bunx",
      --     "typescript-language-server",
      --     "--stdio",
      --   },
      -- },
    },
    format = { timeout_ms = 60000 },
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
