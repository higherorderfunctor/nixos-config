local function set_minus(self, other)
  local index = {}
  for _, v in ipairs(other) do
    index[v] = true
  end
  for i, v in ipairs(self) do
    if index[v] then
      table.remove(self, i)
    end
  end
end

-- installed by nix
local exclude_packages = {
  "docker_compose_language_service",
  "dockerls",
  "hadolint",
  "jsonls",
  "lua_ls",
  "markdownlint",
  "marksman",
  "nil_ls",
  "shfmt",
  "stylua",
  "yamlls",
}

-- patch to prevent excluded packages from being installed
local mason_settings = require("mason.settings")
mason_settings._set = mason_settings.set
---@diagnostic disable-next-line: duplicate-set-field
require("mason.settings").set = function(opts)
  set_minus(opts.ensure_installed, exclude_packages)
  mason_settings._set(opts)
end

local mason_lspconfig_settings = require("mason-lspconfig.settings")
mason_lspconfig_settings._set = mason_lspconfig_settings.set
---@diagnostic disable-next-line: duplicate-set-field
require("mason-lspconfig.settings").set = function(opts)
  set_minus(opts.ensure_installed, exclude_packages)
  mason_lspconfig_settings._set(opts)
end

return {
  --  :lua print(vim.inspect(require("mason.settings").current))
  {
    "williamboman/mason.nvim",
    opts = function(_, opts)
      opts.ensure_installed = opts.ensure_installed or {}
      set_minus(opts.ensure_installed, exclude_packages)
    end,
  },
  --  :lua print(vim.inspect(require("mason-lspconfig.settings").current))
  {
    "williamboman/mason-lspconfig",
    opts = function(_, opts)
      opts.ensure_installed = opts.ensure_installed or {}
      set_minus(opts.ensure_installed, exclude_packages)
    end,
  },
}
