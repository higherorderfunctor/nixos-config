return {
  "rafamadriz/friendly-snippets",
  opts = function()
    require("luasnip").filetype_extend("typescript", { "tsdoc" })
    require("luasnip.loaders.from_vscode").lazy_load()
    return {}
  end,
}
