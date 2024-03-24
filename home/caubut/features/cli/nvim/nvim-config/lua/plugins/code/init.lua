return {
  require("plugins.code.format"),
  require("plugins.code.lint"),
  require("plugins.code.lsp"),
  require("plugins.code.snippets"),
  require("plugins.code.syntax"),
  require("plugins.code.mason"),
}

-- Bash
-- -- "shellcheck", -- lint
-- -- "shellharden", -- lint
-- !! "bash-language-server", -- lsp

-- LSP(s):
--   * bashls - plugins.code.lsp.lspconfig
-- Linter(s):
--   * shellcheck - plugins.code.lint.nvim-lint
--   ! shellharden - plugins.code.lint.nvim-lint - verify a warning
-- Formatter(s):
--   * shfmt - plugins.code.format.conform
--   * beautysh - plugins.code.format.conform

-- Dockerfile

--     ◍ docker-compose-language-service docker_compose_language_service
--     ◍ dockerfile-language-server dockerls
-- "docker-compose-language-service", -- lsp
-- "dockerfile-language-server", -- lsp
-- -- "hadolint", -- lint

-- LSP(s):
-- Linter(s):
-- Formatter(s):

--     ◍ eslint-lsp eslint
--     ◍ hadolint
--     ◍ markdownlint
--     ◍ nil nil_ls
--     ◍ shfmt
--     ◍ typescript-language-server tsserver
--     ◍ yaml-language-server yamlls

-- "eslint-lsp", -- lsp
-- "html-lsp", -- lsp
-- "htmlhint", -- lint
-- "markuplint", -- lint
-- "prettierd", -- format
-- "spectral-language-server", -- lsp
-- "typescript-language-server", -- lsp
-- "vacuum", -- linter

-- yaml
-- "yaml-language-server", -- lsp

-- json
-- !! "json-lsp", -- lsp*

-- Nix

-- !! "nil", -- lsp - cargo

-- lua
-- !! "luacheck", -- lint - luarocks
-- !! "lua-language-server", -- lsp
-- !! "stylua", -- format

-- markdown
-- !! "markdownlint", -- lint format
-- !! "marksman", -- lsp
