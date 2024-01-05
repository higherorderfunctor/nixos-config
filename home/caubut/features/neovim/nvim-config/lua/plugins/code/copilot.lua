return {
	"zbirenbaum/copilot.lua",
	lazy = false,
	build = ":Copilot auth",
	cmd = "Copilot",
	keys = {
		{ "<leader>cc", "<cmd>Copilot panel<cr>", desc = "Copilot" },
	},
	opts = {
		suggestion = { enabled = false },
		panel = { enabled = true },
		filetypes = {
			markdown = true,
			help = true,
		},
	},
	config = function(_, opts)
		require("copilot").setup(opts)
	end,
}
