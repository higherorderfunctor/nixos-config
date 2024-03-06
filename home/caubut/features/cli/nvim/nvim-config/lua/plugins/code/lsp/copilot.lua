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
      sh = true,
      typescript = true,
      yaml = true,
      ["*"] = false,
    },
  },
  config = function(_, opts)
    require("copilot").setup(opts)
  end,
}
