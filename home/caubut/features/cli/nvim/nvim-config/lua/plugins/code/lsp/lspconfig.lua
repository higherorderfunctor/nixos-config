local util = require("lspconfig.util")

-- local function custom_root_dir(fname)
--   local root = util.root_pattern("tsconfig.json", "package.json", "jsconfig.json", ".git")(fname)
--   require("lazyvim.util").info("Detected root directory: " .. (root or "none"))
--   return root
-- end

local eslint_lsp_path = vim.fn.getcwd()
  .. "/node_modules/vscode-langservers-extracted/lib/eslint-language-server/eslintServer.js"

local eslint_lsp = { "vscode-eslint-language-server" }
-- local eslint_lsp = { vim.fn.getcwd() .. "/bin/vscode-eslint-language-server" }
-- local eslint_lsp = { "vscode-eslint-language-server" }
if vim.loop.fs_stat(eslint_lsp_path) then
  eslint_lsp = { "pnpm", eslint_lsp_path }
end

-- require("lazyvim.util").info(eslint_lsp)

return {
  {
    "esmuellert/nvim-eslint",
    opts = function(_, opts)
      local opts = vim.tbl_deep_extend("force", opts or {}, {
        cmd = {
          "node",
          "--enable-source-maps",
          require("nvim-eslint").get_plugin_root() .. "/vscode-eslint/server/out/eslintServer.js",
          "--stdio",
        },
        handlers = {
          ["eslint/noConfig"] = function(_, result)
            require("lazyvim.util").warn(result.message)
            return {}
          end,
          ["workspace/diagnostic/refresh"] = function(_, _, ctx)
            local ns = vim.lsp.diagnostic.get_namespace(ctx.client_id)
            local bufnr = vim.api.nvim_get_current_buf()
            vim.diagnostic.reset(ns, bufnr)
            return true
          end,
        },
        settings = {
          format = true,
          useFlatConfig = true,
          workingDirectory = nil,
          workingDirectories = { mode = "auto" },
          options = {
            flags = { "unstable_ts_config" },
          },
        },
      })
      return opts
    end,
    config = function(_, opts)
      require("nvim-eslint").setup(opts)
      require("lazyvim.util").info(
        "ESLint post-setup-opts: " .. vim.inspect(require("nvim-eslint").make_settings(vim.api.nvim_get_current_buf()))
      )
    end,
  },
  {
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
          enabled = false,
          --   -- cmd = { "bun", eslint_lsp_path, "--stdio" },
          --   -- NOTE: useful for getting logs
          --   -- cmd = vim.list_extend(eslint_lsp, { "--stdio" }),
          --   flags = {
          --     unstable_ts_config = true,
          --   },
          --   settings = {
          --     --cache = true,
          --     -- debug = "*",
          --     -- useFlatConfig = true, -- set if using flat config
          --     options = {
          --       flags = { "unstable_ts_config" },
          --       cache = false,
          --     },
          --     --overrideConfigFile = vim.fn.getcwd() .. "/eslint.config.ts",
          --     -- experimental = {
          --     --   useFlatConfig = nil, -- option not in the latest eslint-lsp
          --     -- },
          --   },
        },
        lua_ls = {
          cmd = { "lua-language-server" },
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
  },
}
