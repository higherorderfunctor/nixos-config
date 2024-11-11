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

  {
    "ThePrimeagen/refactoring.nvim",
    dependencies = {
      "nvim-lua/plenary.nvim",
      "nvim-treesitter/nvim-treesitter",
    },
    config = function()
      require("refactoring").setup()
    end,
  },
  {
    "nvimtools/none-ls.nvim",
    opts = function(_, opts)
      local none_ls = require("null-ls")
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
        none_ls.builtins.formatting.markdownlint, -- markdown
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
            "vue",
            "css",
            "scss",
            -- "less",
            "html",
            "json",
            "jsonc",
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
    end,
  },
}
