return {
  require("plugins.code.format"),
  require("plugins.code.lint"),
  require("plugins.code.lsp"),
  require("plugins.code.snippets"),
  require("plugins.code.syntax"),
  require("plugins.code.mason"),
}

-----------------------------------------------------------------------------------------------------------------------
-- Legend
-----------------------------------------------------------------------------------------------------------------------

--   @                            needs setup review
--   !                            setup by not tested
--   #                            setup and tested

-----------------------------------------------------------------------------------------------------------------------
-- Helpful Commands
-----------------------------------------------------------------------------------------------------------------------

-- :lua print(vim.bo.filetype)    show buffer's filetype

-- plugins.code.lsp.lspconfig -----------------------------------------------------------------------------------------
-- SPACE,c,l                      show LSP info for buffer
-- SPACE,c,z                      restart LSP

-- plugins.code.lsp.none-ls -------------------------------------------------------------------------------------------
-- :NullLsInfo                    show none-ls info for buffer
-- :NullLsLog                     show none-ls logs
--
-- plugins.code.lint.nvim-lint ----------------------------------------------------------------------------------------
-- SPACE,x,z                      show linter info for buffer
--
-- plugins.code.format.conform ----------------------------------------------------------------------------------------
-- :Conform                       show formatter info for buffer

-----------------------------------------------------------------------------------------------------------------------
-- Bash
-----------------------------------------------------------------------------------------------------------------------

-- LSP:
--   # bash-ls                    plugins.code.lsp.lspconfig
--   # printenv                   plugins.code.lsp.none-ls
--   # dontenv-linter             plugins.code.lsp.none-ls
-- Linter:
--   # shellcheck                 plugins.code.lsp.lspconfig via bashls
-- Formatter:
--   # shellharden                plugins.code.lsp.none-ls via conform
--   # shfmt                      plugins.code.lsp.none-ls via conform
--   # beautysh                   plugins.code.format.conform

-----------------------------------------------------------------------------------------------------------------------
-- HTML
-----------------------------------------------------------------------------------------------------------------------
-- TODO:
-- "html-lsp", -- lsp
-- "htmlhint", -- lint
-- "markuplint", -- lint

-- Formatter:
--   # prettierd                  plugins.code.lsp.none-ls via conform

-----------------------------------------------------------------------------------------------------------------------
-- JSON
-----------------------------------------------------------------------------------------------------------------------

-- LSP:
--   # json-ls                    plugins.code.lsp.lspconfig
-- Formatter:
--   # prettierd                  plugins.code.lsp.none-ls via conform

-----------------------------------------------------------------------------------------------------------------------
-- Lua
-----------------------------------------------------------------------------------------------------------------------

-- LSP:
--   # lua-ls                     plugins.code.lsp.lspconfig
-- Linter:
--   # selene                     plugins.code.lsp.none-ls
--   # luacheck                   plugins.code.lint.nvim-lint
-- Formatter:
--   # stylua                     plugins.code.lsp.none-ls via conform
-- Code Action:
--   # refactoring                plugins.code.lsp.none-ls
-- Hover
--   # dictionary                 plugins.code.lsp.none-ls

-----------------------------------------------------------------------------------------------------------------------
-- Markdown
-----------------------------------------------------------------------------------------------------------------------
-- FIXME: markdownlint installed via mason

-- LSP:
--   # marksman                   plugins.code.lsp.lspconfig
-- Linter:
--   # markdownlint               plugins.code.lsp.none-ls
-- Formatter:
--   # markdownlint               plugins.code.lsp.none-ls
-- Hover
--   # dictionary                 plugins.code.lsp.none-ls

-- TODO:
-- mdl: https://github.com/markdownlint/markdownlint
-- glow: https://github.com/ellisonleao/glow.nvim
-- mdp: https://github.com/iamcco/markdown-preview.nvim - doesn't work
-- Grammar:
--   grammarly: https://github.com/znck/grammarly - SDK discontinued, look for another
--   https://github.com/elijah-potter/harper
--   https://valentjn.github.io/ltex/
--    ◍ proselint
--    ◍ prosemd-lsp prosemd_lsp, prosemd_lsp
--    ◍ textlint
--    ◍ vale
--    ◍ vale-ls vale_ls, vale_ls
--    ◍ write-good
--    https://github.com/jeertmans/languagetool-rust
--    textidote
-- code block format
-- changelog format:
-- https://github.com/mdwint/ocdc
-- line wrapper:
--  https://github.com/razziel89/mdslw
--    ◍ markdown-oxide markdown_oxide, markdown_oxide
--    ◍ remark-cli
--    ◍ remark-language-server remark_ls, remark_ls

-----------------------------------------------------------------------------------------------------------------------
-- Nix
-----------------------------------------------------------------------------------------------------------------------

-- LSP:
--   # nil                        plugins.code.lsp.lspconfig
--   # nixd                       plugins.code.lsp.lspconfig
-- Linter:
--   # deadnix                    plugins.code.lint.none-ls
--   # statix                     plugins.code.lint.none-ls
-- Formatter:
--   # alejandra                  plugins.code.lsp.none-ls via conform
-- Code Action:
--   # statix                     plugins.code.lsp.none-ls

-----------------------------------------------------------------------------------------------------------------------
-- Dockerfile
-----------------------------------------------------------------------------------------------------------------------

--     ◍ docker-compose-language-service docker_compose_language_service
--     ◍ dockerfile-language-server dockerls
-- "docker-compose-language-service", -- lsp
-- "dockerfile-language-server", -- lsp
-- -- "hadolint", -- lint

-----------------------------------------------------------------------------------------------------------------------
-- YAML
-----------------------------------------------------------------------------------------------------------------------

--     ◍ yaml-language-server yamlls

-----------------------------------------------------------------------------------------------------------------------
-- OpenAPI
-----------------------------------------------------------------------------------------------------------------------

-- "spectral-language-server", -- lsp
-- "vacuum", -- linter

-----------------------------------------------------------------------------------------------------------------------
-- JavaScript
-----------------------------------------------------------------------------------------------------------------------

-- "eslint-lsp", -- lsp
-- "typescript-language-server", -- lsp

-----------------------------------------------------------------------------------------------------------------------
-- TypeScript
-----------------------------------------------------------------------------------------------------------------------

-- "eslint-lsp", -- lsp
-- "typescript-language-server", -- lsp

-----------------------------------------------------------------------------------------------------------------------
-- Other
-----------------------------------------------------------------------------------------------------------------------
-- TODO:
--  mini.surround / mini.pairs or other surrounding functionality
--    Installed
--    ◍ docker-compose-language-service docker_compose_language_service, docker_compose_language_service
--    ◍ dockerfile-language-server dockerls, dockerls
--    ◍ eslint-lsp eslint, eslint
--    ◍ markdownlint
--    ◍ typescript-language-server tsserver, tsserver
--    ◍ yaml-language-server yamlls, yamlls
