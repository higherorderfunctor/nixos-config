-- vim.lsp.set_log_level("trace") -- FIXME:

return {
  "neovim/nvim-lspconfig",
  opts = {
    servers = {
      eslint = {
        settings = {
          useFlatConfig = true, -- set if using flat config
          experimental = {
            useFlatConfig = nil, -- option not in the latest eslint-lsp
          },
        },
      },
      -- vtsls = {
      --   settings = {
      --     typescript = {
      --       tsserver = {
      --         experimental = {
      --           useVsCodeWatcher = true
      --         }
      --       }
      --     }
      --   }
      -- },
    },
    setup = {
      -- tsserver = function()
      --   require("lazyvim.util").lsp.on_attach(function(client)
      --     -- Enable trace logging
      --     client.config.flags = client.config.flags or {}
      --     client.config.flags.allow_incremental_sync = true
      --     client.config.init_options = {
      --       logVerbosity = "verbose",  -- Set log verbosity to verbose
      --       trace = "verbose"  -- Set trace level to verbose
      --     }
      --   end)
      -- end,
      eslint = function()
        require("lazyvim.util").lsp.on_attach(function(client)
          if client.name == "eslint" then
            client.server_capabilities.documentFormattingProvider = true
          elseif client.name == "tsserver" or client.name == "vtsls" or client.name == "volar" then
            client.server_capabilities.documentFormattingProvider = false
          end
        end)
      end,
    },
  },
}

-- export TSS_LOG="-logToFile true -file $PWD/tsserver.log -level verbose"
