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
    dir = vim.fn.stdpath("config") .. "/lua/plugins/code/lsp/nvim-oxlint",
    -- "soulsam480/nvim-oxlint",
    opts = {
      bin_path = { "oxc_language_server", "--stdio" },
    },
    -- -- config = function(_, opts)
    -- --   require("nvim-oxlint").setup(opts)
    -- -- end,
  },
  {
    "esmuellert/nvim-eslint",
    opts = function(_, opts)
      local opts = vim.tbl_deep_extend("force", opts or {}, {
        cmd = {
          "node",
          "--enable-source-maps",
          eslint_lsp_path,
          -- require("nvim-eslint").get_plugin_root() .. "/vscode-eslint/server/out/eslintServer.js",
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
          -- ["typescript.tsdk"] = "<workspace>\\node_modules\\typescript\\lib",
          options = {
            cache = true,
            cacheLocation = ".lsp.eslintcache",
            -- flags = { "unstable_ts_config" },
          },
        },
      })
      return opts
    end,
    config = function(_, opts)
      require("lazyvim.util").lsp.on_attach(function(client)
        if client.name == "eslint" then
          client.server_capabilities.documentFormattingProvider = true
        elseif client.name == "tsserver" or client.name == "vtsls" or client.name == "volar" then
          client.server_capabilities.documentFormattingProvider = false
        end
      end)
      require("nvim-eslint").setup(opts)
      -- require("lazyvim.util").info(
      --   "ESLint post-setup-opts: " .. vim.inspect(require("nvim-eslint").make_settings(vim.api.nvim_get_current_buf()))
      -- )
    end,
  },
  {
    "neovim/nvim-lspconfig",
    opts = function(_, opts)
      return vim.tbl_deep_extend("force", opts or {}, {
        diagnostics = {
          underline = true,
          update_in_insert = false,
        },
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
          -- vtsls = {
          --   tsserver = {
          --     globalPlugins = {
          --       {
          --         configNamespace = "typescript",
          --         enableForWorkspaceTypeScriptVersions = true,
          --         languages = { "typescript", "vue" },
          --         location = "/home/caubut/.local/share/nvim/mason/packages/vue-language-server//node_modules/@vue/language-server",
          --         name = "@vue/typescript-plugin",
          --       },
          --     },
          --   },
          -- },
          -- tsserver = {
          --   cmd = {
          --     "bunx",
          --     "typescript-language-server",
          --     "--stdio",
          --   },
          -- },
        },
        format = { timeout_ms = 60000 },
      })
    end,
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
  {
    "neovim/nvim-lspconfig",
    opts = function(_, opts)
      local plugins = opts.servers.vtsls.settings.vtsls.tsserver.globalPlugins
      for _, plugin in ipairs(plugins) do
        if plugin.name == "@vue/typescript-plugin" then
          plugin.languages = { "vue", "typescript" }
          break
        end
      end
    end,
  },
}
