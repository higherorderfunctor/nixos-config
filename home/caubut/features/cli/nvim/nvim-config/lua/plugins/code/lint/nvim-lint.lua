local show_active_linters = function()
  local linters = require("lint")._resolve_linter_by_ft(vim.bo.filetype)
  require("notify")(vim.inspect(linters))
end

return {
  "mfussenegger/nvim-lint",
  opts = {
    linters_by_ft = {
      docker = { "hadolint" },
      lua = { "luacheck" },
      markdown = {}, -- override LazyVim, handled by none-ls
      python = { "mypy" },
      openapi = { "vacuum" },
    },
  },
  keys = {
    { "<leader>xz", show_active_linters, desc = "Show Active Linters" },
  },
}
