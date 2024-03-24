return {
  "stevearc/conform.nvim",
  opts = {
    format = { lsp_fallback = "always" },
    formatters_by_ft = {
      html = { "prettierd" },
      markdown = { "markdownlint" },
      nix = { "alejandra" },
      sh = { "shfmt", "beautysh" },
      typescript = {},
      ["*"] = { "trim_newlines", "trim_whitespace" },
      ["_"] = { "trim_newlines", "trim_whitespace" },
    },
  },
}
