local lint_progress = function()
  local linters = require("lint")._resolve_linter_by_ft(vim.bo.filetype)
  for _, linter in pairs(linters) do
    require("notify")(linter)
  end
end

return {
  "mfussenegger/nvim-lint",
  opts = {
    linters_by_ft = {
      bash = { "shellcheck", "shellharden" },
      docker = { "hadolint" },
      lua = { "luacheck" },
      markdown = { "markdownlint" },
      openapi = { "vacuum" },
      nix = { "statix" },
    },
  },
  keys = {
    { "<leader>xz", lint_progress, desc = "Show Active Linters" },
  },
}
