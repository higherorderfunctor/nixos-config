-- local ai_hub_mix_api_key_path = "/run/user/1000/secrets/caubut-ai-hub-mix-api-key"
-- local kiro_proxy_key_path = "/run/user/1000/secrets/kiro-proxy-api-key"
local kagi_api_key_path = "/run/user/1000/secrets/caubut-kagi-api-key"

local function read_file(path)
  local file = io.open(path, "r")
  if not file then
    vim.notify("Failed to open API key file: " .. path, vim.log.levels.ERROR)
    return nil
  end
  local content = file:read("*l")
  file:close()
  return content
end

-- -- Load AIHubMix key
-- local ai_hub_mix_api_key = read_file(ai_hub_mix_api_key_path)
-- if ai_hub_mix_api_key then
--   vim.env.AVANTE_AIHUBMIX_API_KEY = ai_hub_mix_api_key
-- end

-- Load Kagi key
local kagi_api_key = read_file(kagi_api_key_path)
if kagi_api_key then
  vim.env.KAGI_API_KEY = kagi_api_key
end

-- TODO: Manage via SOPs.  Local-to-local communication only, no need to store
-- in env vars, just pass directly to avante config.  This is only needed for
-- the rag service, which is currently configured to use a local kiro proxy
-- that requires an API key.
-- Running:
-- PROXY_API_KEY="my-super-secret-password-123" \
--   KIRO_CLI_DB_FILE="~/.local/share/kiro-cli/data.sqlite3" \
--   kiro-gateway
vim.env.KIRO_API_KEY = "my-super-secret-password-123"

return {
  {
    "ravitemer/mcphub.nvim",
    dependencies = { "nvim-lua/plenary.nvim" },
    build = "pnpm install -g mcp-hub@latest",
    config = function()
      require("mcphub").setup({
        servers = {
          filesystem = {
            command = "pnpm",
            args = { "dlx", "@modelcontextprotocol/server-filesystem", "." },
          },
          -- fetch = {
          --   command = "uvx",
          --   args = { "mcp-server-fetch" },
          -- },
          -- git = {
          --   command = "uvx",
          --   args = { "mcp-server-git" },
          -- },
          -- ["sequential-thinking"] = {
          --   command = "npx",
          --   args = { "-y", "@modelcontextprotocol/server-sequentialthinking" },
          -- },
          -- ["memory-graph"] = {
          --   command = "npx",
          --   args = { "-y", "memory-graph" },
          --   env = {
          --     NEO4J_URI = "bolt://localhost:7687",
          --     NEO4J_USER = "neo4j",
          --     NEO4J_PASSWORD = os.getenv("NEO4J_PASSWORD") or "changeme",
          --   },
          -- },
          -- time = {
          --   command = "npx",
          --   args = { "-y", "@modelcontextprotocol/server-time" },
          -- },
          -- notifications = {
          --   command = "npx",
          --   args = { "-y", "@anthropic/mcp-server-notifications" },
          -- },
        },
        extensions = {
          avante = {
            make_slash_commands = true,
          },
        },
      })
    end,
  },
  {
    "yetone/avante.nvim",
    opts = function(_, opts)
      return vim.tbl_deep_extend("force", opts or {}, {
        provider = "kiro",
        auto_suggestions_provider = "kiro",

        behavior = {
          auto_suggestions = true,
        },

        acp_providers = {
          -- NOTE: can be verified working with a simple "are you Kiro?" query in the
          -- avante chat
          ["kiro"] = {
            command = "kiro-cli",
            args = { "acp" },
          },
        },

        -- TODO: debug why not reusing index causing file build up
        -- rag_service = {
        --   enabled = true,
        --   host_mount = os.getenv("HOME"),
        --   runner = "docker",

        --   llm = {
        --     provider = "openai",
        --     endpoint = "http://172.17.0.1:8000", -- docker loopback
        --     api_key = "KIRO_API_KEY",
        --     model = "claude-opus-4.6",
        --   },

        --   embed = {
        --     -- NOTE: ollama is installed via nix home manager and runs via systemd.
        --     -- Usage to pull the model: ollama pull nub235/voyage-4-nano
        --     -- Check the logs as nvim doesn't report errors:  docker logs -f avante-rag-service
        --     -- Should see a bunch of embed calls while indexing
        --     provider = "ollama",
        --     endpoint = "http://172.17.0.1:11434", -- docker loopback
        --     api_key = "",
        --     model = "nub235/voyage-4-nano",
        --     extra = nil,
        --   },
        -- },

        web_search_engine = {
          provider = "kagi",
        },
      })
    end,
  },
}
