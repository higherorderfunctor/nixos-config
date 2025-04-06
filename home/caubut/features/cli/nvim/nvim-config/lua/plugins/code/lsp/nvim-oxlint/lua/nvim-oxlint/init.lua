local M = {}

--- Writes to error buffer.
---@param ... string Will be concatenated before being written
local function err_message(...)
  vim.notify(table.concat(vim.iter({ ... }):flatten():totable()), vim.log.levels.ERROR)
  vim.api.nvim_command("redraw")
end

function M.resolve_git_dir(bufnr)
  local markers = { ".git" }
  local git_dir = vim.fs.root(bufnr, markers)
  return git_dir
end

-- function M.resolve_workspace_root(bufnr)
--   -- get the full path of the file in the given buffer
--   local current_file = vim.api.nvim_buf_get_name(bufnr)
--   local current_dir = vim.fn.fnamemodify(current_file, ":h") -- Get the directory of the file
--   local git_root = M.resolve_git_dir(bufnr) -- Resolve the Git root directory
--
--   if not git_root then
--     vim.notify("oxlint: Not inside a git repository", vim.log.levels.ERROR)
--     return nil
--   end
--
--   local last_package_json = nil
--
--   while current_dir and current_dir ~= git_root do
--     local package_json_path = current_dir .. "/package.json"
--     if vim.fn.filereadable(package_json_path) == 1 then
--       last_package_json = package_json_path -- record the last found package.json
--     end
--     current_dir = vim.fn.fnamemodify(current_dir, ":h") -- go one level up
--   end
--
--   -- check for package.json in the git root directory as well
--   local git_root_package_json = git_root .. "/package.json"
--   if vim.fn.filereadable(git_root_package_json) == 1 then
--     last_package_json = git_root_package_json
--   end
--
--   vim.notify("oxlint: " .. last_package_json, vim.log.levels.ERROR)
--
--   return last_package_json
-- end

function M.make_settings(buffer)
  local settings_with_function = vim.tbl_deep_extend("keep", M.user_config.settings or {}, {
    enable = true,
    binPath = vim.fn.exepath("oxc_language_server"),
    configPath = function(bufnr)
      return M.find_config(bufnr)
    end,
    run = "onType",
    workingDirectory = { mode = "auto" },
    workspaceFolder = function(bufnr)
      local git_dir = M.resolve_git_dir(bufnr)
      return {
        uri = vim.uri_from_fname(git_dir),
        name = vim.fn.fnamemodify(git_dir, ":t"),
      }
    end,
  })

  local flattened_settings = {}

  for k, v in pairs(settings_with_function) do
    if type(v) == "function" then
      flattened_settings[k] = v(buffer)
    else
      flattened_settings[k] = v
    end
  end
  return flattened_settings
end

function M.make_client_capabilities()
  local default_capabilities = vim.lsp.protocol.make_client_capabilities()
  default_capabilities.workspace.didChangeConfiguration.dynamicRegistration = true
  default_capabilities.textDocument.codeAction = {
    dynamicRegistration = true,
    codeActionLiteralSupport = {
      codeActionKind = {
        valueSet = {
          "quickfix",
          "source.fixAll.oxc",
        },
      },
    },
  }
  default_capabilities.textDocument.synchronization = {
    dynamicRegistration = true,
    willSave = true,
    willSaveWaitUntil = true,
    didSave = true,
  }
  return default_capabilities
end

function M.find_config(bufnr)
  local workspace_root = M.resolve_git_dir(bufnr)
  -- vim.notify(workspace_root)
  local config = workspace_root .. "/.oxlintrc.json"
  if vim.fn.filereadable(config) == 1 then
    --vim.notify(config)
    return config
  end
  config = workspace_root .. "/.oxlintrc.jsonc"
  if vim.fn.filereadable(config) == 1 then
    -- vim.notify(config)
    return config
  end
  vim.notify("oxlint: No config found", vim.log.levels.ERROR)
end

function M.create_cmd()
  return { "oxc_language_server", "--stdio" }
end

function M.lsp_start()
  vim.api.nvim_create_autocmd("FileType", {
    pattern = vim.tbl_extend("force", {
      "javascript",
      "javascriptreact",
      "javascript.jsx",
      "typescript",
      "typescriptreact",
      "typescript.tsx",
      "vue",
    }, M.user_config.filetypes or {}),
    callback = function(args)
      vim.lsp.start({
        name = "oxlint",
        cmd = M.user_config.cmd or M.create_cmd(),
        root_dir = M.user_config.root_dir and M.user_config.root_dir(args.buf) or M.resolve_git_dir(args.buf),
        settings = M.make_settings(args.buf),
        capabilities = M.user_config.capabilities or M.make_client_capabilities(),
        on_attach = M.user_config.on_attach,
        handlers = vim.tbl_deep_extend("keep", M.user_config.handlers or {}, {
          ["workspace/didChangeConfiguration"] = function(_, result, ctx)
            local function lookup_section(table, section)
              local keys = vim.split(section, ".", { plain = true }) --- @type string[]
              return vim.tbl_get(table, unpack(keys))
            end

            local client_id = ctx.client_id
            local client = vim.lsp.get_client_by_id(client_id)

            if not client then
              err_message("LSP[", client_id, "] client has shut down after sending a workspace/configuration request")
              return
            end
            if not result.items then
              return {}
            end

            --- Insert custom logic to update client settings
            local bufnr = vim.uri_to_bufnr(result.items[1].scopeUri)
            local new_settings = M.make_settings(bufnr)
            client.settings = new_settings
            --- end custom logic

            local response = {}
            for _, item in ipairs(result.items) do
              if item.section then
                local value = lookup_section(client.settings, item.section)
                -- For empty sections with no explicit '' key, return settings as is
                if value == nil and item.section == "" then
                  value = client.settings
                end
                if value == nil then
                  value = vim.NIL
                end
                table.insert(response, value)
              end
            end

            return response
          end,
        }),
      })
    end,
  })
end

function M.setup(user_config)
  if user_config then
    M.user_config = user_config
  end
  M.lsp_start()
end

return M
