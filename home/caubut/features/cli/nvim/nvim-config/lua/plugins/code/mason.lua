return {
  "WhoIsSethDaniel/mason-tool-installer",
  opts = {
    automatic_installation = true,
    ensure_installed = {
      "beautysh", -- format
      "bash-language-server", -- lsp
      "docker-compose-language-service", -- lsp
      "dockerfile-language-server", -- lsp
      "eslint-lsp", -- lsp
      "hadolint", -- lint
      "html-lsp", -- lsp
      "htmlhint", -- lint
      "markuplint", -- lint
      "json-lsp", -- lsp*
      "lua-language-server", -- lsp
      "luacheck", -- lint - luarocks
      "luaformatter", -- format - luarocks cmake
      "markdownlint", -- lint format
      "marksman", -- lsp
      "nil", -- lsp - cargo
      "prettierd", -- format
      "shellcheck", -- lint
      "shfmt", -- format
      "spectral-language-server", -- lsp
      "stylua", -- format
      "typescript-language-server", -- lsp
      "vacuum", -- linter
      "vim-language-server", -- lsp
      "yaml-language-server", -- lsp
    },
  },
}
