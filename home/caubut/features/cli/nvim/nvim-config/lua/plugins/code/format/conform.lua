return {
  "stevearc/conform.nvim",
  opts = {
    format = { lsp_fallback = "always" },
    formatters_by_ft = {
      lua = {}, -- override LazyVim, handled by none-ls
      sh = { "beautysh" }, -- override LazyVim, stylua handled by none-ls
      typescript = {}, -- override LazyVim, stylua handled by none-ls
      ["*"] = { "trim_newlines", "trim_whitespace" },
      ["_"] = { "trim_newlines", "trim_whitespace" },
    },
  },
}
