return {
  "stevearc/conform.nvim",
  opts = {
    default_format_opts = { lsp_fallback = "always", timeout_ms = 60000 }, -- 10000 },
    formatters_by_ft = {
      lua = {}, -- override LazyVim, handled by none-ls
      sh = { "beautysh" }, -- override LazyVim, stylua handled by none-ls
      javascript = {}, -- override LazyVim
      typescript = {}, -- override LazyVim
      ["*"] = { "trim_newlines", "trim_whitespace" },
      ["_"] = { "trim_newlines", "trim_whitespace" },
    },
  },
}
