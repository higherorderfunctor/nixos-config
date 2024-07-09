-- <c-b>	Scroll Backward	n, i, s
-- <c-f>	Scroll Forward	n, i, s
-- <leader>sn	  +noice	n
-- <leader>sna	Noice All	n
-- <leader>snd	Dismiss All	n
-- <leader>snh	Noice History	n
-- <leader>snl	Noice Last Message	n
-- <leader>snt	Noice Picker (Telescope/FzfLua)	n
-- <S-Enter>	Redirect Cmdline	c

-- return {
--   "rcarriga/nvim-notify",
--   keys = {
--     { "<leader>uN", "<cmd>Telescope notify<cr>", desc = "Show Notifications" },
--   },
-- }
return {
  "folke/noice.nvim",
  event = "VeryLazy",
  -- FIXME: REMOVE THIS once this issue is fixed: https://github.com/yioneko/vtsls/issues/159
  opts = {
    routes = {
      {
        filter = {
          event = "notify",
          find = "Node ComputedPropertyName was unexpected.",
        },
        opts = { skip = true },
      },
      {
        filter = {
          event = "notify",
          find = "Debug Failure. False expression.",
        },
        opts = { skip = true },
      },
    },
  },
}
