return {
	"NvChad/nvim-colorizer.lua",
	opts = {
		filetypes = { "*" },
		buftypes = { "*" },
	},
	config = function(_, opts)
		require("colorizer").setup(opts)
	end,
}
