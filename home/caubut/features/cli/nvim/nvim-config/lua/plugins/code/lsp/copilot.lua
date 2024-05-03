return {
  "zbirenbaum/copilot.lua",
  keys = {
    { "<leader>cc", "<cmd>Copilot panel<cr>", desc = "Copilot" },
  },
  opts = {
    suggestion = { enabled = false },
    panel = { enabled = true },
    filetypes = {
      bash = true,
      help = true,
      javascript = true,
      json = true,
      lua = true,
      markdown = true,
      nix = true,
      openapi = true,
      sh = function()
        if string.match(vim.fs.basename(vim.api.nvim_buf_get_name(0)), "%.env.*") then
          return false
        end
        if string.match(vim.fs.basename(vim.api.nvim_buf_get_name(0)), "%secrets.*") then
          return false
        end
        return true
      end,
      typescript = true,
      yaml = true,
      ["*"] = false,
    },
  },
  config = function(_, opts)
    require("copilot").setup(opts)
  end,
}
