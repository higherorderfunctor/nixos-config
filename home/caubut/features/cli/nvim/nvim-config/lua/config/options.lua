local opt = vim.opt

opt.colorcolumn = "120" -- show column and line length

vim.lsp.handlers["textDocument/publishDiagnostics"] = vim.lsp.with(vim.lsp.diagnostic.on_publish_diagnostics, {
  -- delay update diagnostics
  update_in_insert = false,
})
