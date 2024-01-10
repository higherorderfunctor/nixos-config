return {
	-- adds aerial to the list of files that don't replace the current buffer
	{
		"nvim-neo-tree/neo-tree.nvim",
		opts = function(_, opts)
			table.insert(
				vim.list_extend(
					opts.open_files_do_not_replace_types or {},
					{ "terminal", "Trouble", "qf", "aerial", "trouble" }
				),
				"edgy"
			)
		end,
	},
	-- open from cwd instead of root dir, personal preference for monorepos
	{
		"folke/edgy.nvim",
		opts = function(_, opts)
			--	opts.options = { left = { size = 65 } }
			opts.left[1].open = function()
				vim.api.nvim_input("<esc><space>E")
			end
			return require("edgy").setup(opts)
		end,
	},
}
