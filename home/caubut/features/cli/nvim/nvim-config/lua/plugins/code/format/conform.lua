return {
  "stevearc/conform.nvim",
  opts = function(_, opts)
    vim.tbl_deep_extend("force", opts or {}, {
      default_format_opts = {
        --   async = true,
        timeout_ms = 60000,
      }, -- 10000 },
      formatters_by_ft = {
        lua = {}, -- override LazyVim, handled by none-ls
        sh = { "beautysh" }, -- override LazyVim, stylua handled by none-ls
        markdown = {},
        javascript = {}, -- override LazyVim
        typescript = {}, -- override LazyVim
        ["*"] = { "trim_newlines", "trim_whitespace" },
        ["_"] = { "trim_newlines", "trim_whitespace" },
      },
    })
    return opts
  end,
}
