return {
	require("plugins.code.conform"),
	require("plugins.code.copilot"),
	require("plugins.code.eslint"),
	require("plugins.code.luasnip"),
	require("plugins.code.mason"),
	require("plugins.code.nvim-lint"),
	require("plugins.code.null-ls"),
	-- {
	-- 	"hrsh7th/nvim-cmp",
	-- 	opts = function(_, opts)
	-- 		local cmp = require("cmp")
	-- 		table.insert(opts, 1, {
	-- 			window = {
	-- 				completion = cmp.config.window.bordered(),
	-- 				documentation = cmp.config.window.bordered(),
	-- 			},
	-- 		})
	-- 	end,
	-- },
}
