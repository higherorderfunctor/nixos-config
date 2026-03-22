local util = require("lspconfig.util")

local function custom_root_dir(fname)
  local root = util.root_pattern("tsconfig.json", "package.json", "jsconfig.json", ".git")(fname)
  require("lazyvim.util").info("Detected root directory: " .. (root or "none"))
  return root
end

local eslint_lsp_path = vim.fn.getcwd()
  .. "/node_modules/vscode-langservers-extracted/lib/eslint-language-server/eslintServer.js"

local eslint_lsp = { "vscode-eslint-language-server" }
-- local eslint_lsp = { vim.fn.getcwd() .. "/bin/vscode-eslint-language-server" }
-- local eslint_lsp = { "vscode-eslint-language-server" }
if vim.loop.fs_stat(eslint_lsp_path) then
  eslint_lsp = { "pnpm", eslint_lsp_path }
end

-- require("lazyvim.util").info(eslint_lsp)

local vue_plugin = {
  name = "@vue/typescript-plugin",
  --  location = vim.fn.getcwd() .. "/usr/local/lib/node_modules",
  configNamespace = "typescript",
  enableForWorkspaceTypeScriptVersions = true,
  location = custom_root_dir() .. "/node_modules/@vue/language-server",
  languages = { "vue", "typescript" },
}

--                   languages = { "vue" },
--                   configNamespace = "typescript",
--                   enableForWorkspaceTypeScriptVersions = true,
--                 },

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
          -- ["workspace/diagnostic/refresh"] = function(_, _, ctx)
          --   local ns = vim.lsp.diagnostic.get_namespace(ctx.client_id)
          --   local bufnr = vim.api.nvim_get_current_buf()
          --   vim.diagnostic.reset(ns, bufnr)
          --   return true
          -- end,
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
      Snacks.util.lsp.on(function(client_id)
        local client = vim.lsp.get_client_by_id(client_id)
        if client then
          if client.name == "eslint" then
            client.server_capabilities.documentFormattingProvider = true
          elseif client.name == "tsserver" or client.name == "vtsls" or client.name == "volar" then
            client.server_capabilities.documentFormattingProvider = false
          end
        end
      end)
      require("nvim-eslint").setup(opts)
    end,
  },
  {
    "neovim/nvim-lspconfig",
    opts = {
      diagnostics = {
        underline = true,
        update_in_insert = true,
      },
    },
  },
  {
    "neovim/nvim-lspconfig",
    opts = {
      servers = {
        ["*"] = {
          keys = {
            { "<leader>cz", "<cmd>LspRestart<cr>", desc = "Restart LSP" },
          },
        },
        bashls = { mason = false },
        docker_compose_language_service = { mason = false },
        dockerls = { mason = false },
        jsonls = {
          cmd = { "vscode-json-languageserver", "--stdio" },
          mason = false,
        },
        eslint = {
          enabled = false,
        },
        lua_ls = {
          cmd = { "lua-language-server" },
          mason = false,
        },
        dprint = {
          mason = false,
          filetypes = {
            "javascript",
            "javascriptreact",
            "typescript",
            "typescriptreact",
            "json",
            "json5",
            "jsonc",
            "markdown",
            "python",
            "toml",
            "rust",
            "roslyn",
            "graphql",
          },
        },
        marksman = { mason = false },
        nil_ls = { mason = false },
        nixd = { mason = false },
        yamlls = {
          cmd = { "/etc/profiles/per-user/caubut/bin/yaml-language-server", "--stdio" },
          mason = false,
        },
      },
    },

    -- init = function()
    --   local keys = require("lazyvim.plugins.lsp.keymaps").get()
    --   -- change a keymap
    --   -- keys[#keys + 1] = { "K", "<cmd>echo 'hello'<cr>" }
    --   -- disable a keymap
    --   -- keys[#keys + 1] = { "K", false }
    --   -- add a keymap
    --   keys[#keys + 1] = { "<leader>cz", "<cmd>LspRestart<cr>", desc = "Restart LSP" }
    -- end,
  },
  {
    "neovim/nvim-lspconfig",
    opts = {
      servers = {
        vtsls = {
          settings = {
            complete_function_calls = true,
            vtsls = {
              enableMoveToFileCodeAction = true,
              autoUseWorkspaceTsdk = true,
              experimental = {
                maxInlayHintLength = 30,
                completion = {
                  -- PERF: vtsls sends a large number of completions
                  -- reducing this number makes blink.cmp fast again
                  enableServerSideFuzzyMatch = true,
                  entriesLimit = 20,
                },
              },
            },
            typescript = {
              preferences = { importModuleSpecifier = "non-relative" },
              updateImportsOnFileMove = { enabled = "always" },
              suggest = {
                completeFunctionCalls = true,
              },
              inlayHints = {
                enumMemberValues = { enabled = true },
                functionLikeReturnTypes = { enabled = false },
                parameterNames = { enabled = "all" },
                parameterTypes = { enabled = false },
                propertyDeclarationTypes = { enabled = true },
                variableTypes = { enabled = false },
              },
              tsserver = {
                maxTsServerMemory = 8192,
                -- log = "verbose",
                --     pluginPaths = { "./node_modules" },
              },
            },
          },
          flags = {
            debounce_text_changes = 250,
          },
        },
      },
    },
  },
  -- {
  --   "neovim/nvim-lspconfig",
  --   opts = {
  --     servers = {
  --       --     format = { timeout_ms = 60000 },
  --     },
  --   },
  -- },
  {
    "yioneko/nvim-vtsls",
  },
}

--{
--  "neovim/nvim-lspconfig",
--  opts = function(_, opts)
--    local plugins = opts.servers.vtsls.settings.vtsls.tsserver.globalPlugins
--    for _, plugin in ipairs(plugins) do
--      if plugin.name == "@vue/typescript-plugin" then
--        plugin.languages = { "vue", "typescript" }
--        plugin.location = LazyVim.root() .. "/node_modules/@vue/language-server"
--        break
--      end
--    end
--    return opts
--  end,
--},
-- opts = function(_, opts)
--   table.insert(opts.servers.vtsls.filetypes, "vue")
--   LazyVim.extend(opts.servers.vtsls, "settings.vtsls.tsserver.globalPlugins", {
--     {
--       name = "@vue/typescript-plugin",
--       location = LazyVim.get_pkg_path("vue-language-server", "/node_modules/@vue/language-server"),
--       languages = { "vue" },
--       configNamespace = "typescript",
--       enableForWorkspaceTypeScriptVersions = true,
--     },
--   })
-- end
