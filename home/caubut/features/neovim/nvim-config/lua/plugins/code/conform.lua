return {
	"stevearc/conform.nvim",
	opts = {
		format = { lsp_fallback = "always" },
		formatters_by_ft = {
			sh = { "shfmt", "beautysh" },
      nix = { "alejandra" },
			["*"] = { "trim_newlines", "trim_whitespace" },
			["_"] = { "trim_newlines", "trim_whitespace" },
		},
	},
}
