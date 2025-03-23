return {
  -- $ systctl fs.inotify.max_queued_events
  -- fs.inotify.max_queued_events = 16384
  -- $ sysctl fs.inotify.max_user_watches
  -- fs.inotify.max_user_watches = 65536
  -- Add this:
  -- $ sudo vi /etc/sysctl.conf
  -- fs.inotify.max_user_instances = 524288
  -- fs.inotify.max_user_watches = 524288
  -- fs.inotify.max_queued_events = 524288
  -- $ sudo sysctl -p

  -- {
  --   "ThePrimeagen/refactoring.nvim",
  --   dependencies = {
  --     "nvim-lua/plenary.nvim",
  --     "nvim-treesitter/nvim-treesitter",
  --   },
  --   config = function()
  --     require("refactoring").setup()
  --   end,
  -- },
  -- NOTE: vim.lsp.buf.format()
  {
    "nvimtools/none-ls.nvim",
    opts = function(_, opts)
      local none_ls = require("null-ls")
      opts.log_level = "trace"
      -- NOTE: fix
      -- require('lazyvim.util').info(vim.inspect(require("lazyvim.util.format").formatters))
      -- local lazy_format = require("lazyvim.util.format")
      -- for _, entry in ipairs(lazy_format.formatters) do
      --   if entry.name == "none-ls.nvim" then
      --     entry.priority = 50
      --     break
      --   end
      -- end
      -- table.sort(lazy_format.formatters, function(a, b)
      --   return a.priority > b.priority
      -- end)
      --require('lazyvim.util').info(vim.inspect(require("lazyvim.util.format").formatters))
      -- List formatters run:
      -- vim.lsp.buf.format({ async = true, bufnr = vim.api.nvim_get_current_buf(), filter = function(client) print(client.name) return true end })
      -- List all clients that support formatting:
      -- for _, client in pairs(vim.lsp.get_active_clients({ bufnr = vim.api.nvim_get_current_buf() })) do if client.server_capabilities.documentFormattingProvider then print(client.name) end end
      -- List all clients that support formatting method (set bufnr):
      -- lua for _, client in pairs(vim.lsp.get_active_clients({ bufnr = vim.api.nvim_get_current_buf() })) do if client.supports_method("textDocument/formatting") then print(client.name) end end
      -- lua for _, client in pairs(vim.lsp.get_active_clients({ bufnr = vim.api.nvim_get_current_buf() })) do if client.supports_method("textDocument/formatting",vim.api.nvim_get_current_buf()) then print(client.name) end end
      -- lua for _, client in pairs(vim.lsp.get_clients({ bufnr = vim.api.nvim_get_current_buf() })) do if client.supports_method("textDocument/formatting") then print(client.name) end end
      -- lua for _, client in pairs(vim.lsp.get_clients({ bufnr = vim.api.nvim_get_current_buf() })) do if client.supports_method("textDocument/formatting", vim.api.nvim_get_current_buf()) then print(client.name) end end
      -- lua for _, client in pairs(vim.lsp.get_clients({ bufnr = vim.api.nvim_get_current_buf(), method = "textDocument/formatting" })) do print(client.name) end
      -- List all lsp capabilities:
      -- for _, client in pairs(vim.lsp.get_active_clients({ bufnr = vim.api.nvim_get_current_buf() })) do print("Client: " .. client.name); for method, _ in pairs(client.server_capabilities) do print("  Method: " .. method) end end
      -- Conform test func:
      -- require("lazyvim.util").info(vim.inspect(vim.lsp.get_clients({ bufnr = vim.api.nvim_get_current_buf(), method = "textDocument/formatting" })))
      vim.list_extend(opts.sources or {}, {
        -- code actions
        none_ls.builtins.code_actions.refactoring, -- go, javascript, lua, python, typescript
        none_ls.builtins.code_actions.statix, -- nix
        -- diagnostics
        none_ls.builtins.diagnostics.alex, -- markdown
        none_ls.builtins.diagnostics.deadnix, -- nix
        none_ls.builtins.diagnostics.dotenv_linter, -- sh
        none_ls.builtins.diagnostics.markdownlint, -- markdown
        none_ls.builtins.diagnostics.pylint, -- python
        none_ls.builtins.diagnostics.selene, -- lua
        none_ls.builtins.diagnostics.statix, -- nix
        -- formatting
        none_ls.builtins.formatting.alejandra, -- nix
        -- none_ls.builtins.formatting.markdownlint,   -- markdown
        none_ls.builtins.formatting.shellharden, -- sh
        none_ls.builtins.formatting.shfmt, -- sh
        -- none_ls.builtins.formatting.stylua, -- lua
        none_ls.builtins.formatting.stylua.with({
          command = "/etc/profiles/per-user/caubut/bin/stylua",
        }),
        none_ls.builtins.formatting.prettierd.with({
          filetypes = {
            -- "javascript",
            -- "javascriptreact",
            -- "typescript",
            -- "typescriptreact",
            -- "vue",
            "css",
            "scss",
            -- "less",
            "html",
            "json",
            "jsonc",
            "json5",
            -- "yaml",
            -- "markdown",
            -- "markdown.mdx",
            "graphql",
            -- "handlebars",
          },
        }),
        -- hover
        none_ls.builtins.hover.printenv, -- sh, dosbatch, ps1
        none_ls.builtins.hover.dictionary, -- org, text, markdown
      })
      require("null-ls").setup(opts)
    end,
  },
}
