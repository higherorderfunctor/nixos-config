local diffview_toggle = function()
  local lib = require("diffview.lib")
  local view = lib.get_current_view()
  if view then
    -- Current tabpage is a Diffview; close it
    vim.cmd.DiffviewClose()
  else
    -- No open Diffview exists: open a new one
    vim.cmd.DiffviewOpen()
  end
end

return {
  "sindrets/diffview.nvim",
  keys = {
    { "<leader>gd", diffview_toggle, desc = "Diffview" },
  },
}

-- https://github.com/sindrets/diffview.nvim/blob/main/doc/diffview_defaults.txt
