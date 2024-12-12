local util = require("lspconfig.util")

local function custom_root_dir(fname)
  local root = util.root_pattern("tsconfig.json", "package.json", "jsconfig.json", ".git")(fname)
  require("lazyvim.util").info("Detected root directory: " .. (root or "none"))
  return root
end
require("lazyvim.util").info("test")

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
      -- vtsls = {
      --   cmd = { "bunx", "--bun", "vtsls", "--stdio" },
      --   -- cmd = { vim.fn.getcwd() .. "/bin/vtsls.sh", "--stdio" },
      --   root_dir = custom_root_dir,
      -- },
      eslint = {
        -- cmd = { "bunx", "--bun", "vscode-eslint-language-server", "--stdio" },
        cmd = { vim.fn.getcwd() .. "/bin/vscode-eslint-language-server", "--stdio" },
        flags = {
          unstable_ts_config = true,
        },
        settings = {
          cache = true,
          --debug = "*",
          useFlatConfig = true, -- set if using flat config
          options = {
            flags = { "unstable_ts_config" },
          },
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
