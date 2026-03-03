-- local ai_hub_mix_api_key_path = vim.fn.expand("/run/user/1000/secrets/caubut-ai-hub-mix-api-key")
local kagi_api_key_path = vim.fn.expand("/run/user/1000/secrets/caubut-ai-hub-mix-api-key")
-- local kiro_proxy_key_path = vim.fn.expand("/run/user/1000/secrets/kiro-proxy-api-key") -- Path for your kiro key

local function read_file(path)
  local file = io.open(path, "r")
  if not file then
    vim.notify("Failed to open API key file: " .. path, vim.log.levels.ERROR)
    return nil
  end
  local content = file:read("*l") -- read first line only
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

-- Load Kiro Gateway key
-- This ensures the Prox y API Key is available for avante to send to the gateway
-- local kiro_proxy_key = read_file(kiro_proxy_key_path)
-- if kiro_proxy_key then
vim.env.KIRO_API_KEY = "my-super-secret-password-123"
-- end

return {
  -- {
  --   "ravitemer/mcphub.nvim",
  --   dependencies = { "nvim-lua/plenary.nvim" },
  --   build = "pnpm install -g mcp-hub@latest",
  --   config = function()
  --     require("mcphub").setup({
  --       servers = {
  --         filesystem = {
  --           command = "pnpm",
  --           args = { "dlx", "@modelcontextprotocol/server-filesystem", "." },
  --         },
  --         -- fetch = {
  --         --   command = "uvx",
  --         --   args = { "mcp-server-fetch" },
  --         -- },
  --         -- git = {
  --         --   command = "uvx",
  --         --   args = { "mcp-server-git" },
  --         -- },
  --         -- ["sequential-thinking"] = {
  --         --   command = "npx",
  --         --   args = { "-y", "@modelcontextprotocol/server-sequentialthinking" },
  --         -- },
  --         -- ["memory-graph"] = {
  --         --   command = "npx",
  --         --   args = { "-y", "memory-graph" },
  --         --   env = {
  --         --     NEO4J_URI = "bolt://localhost:7687",
  --         --     NEO4J_USER = "neo4j",
  --         --     NEO4J_PASSWORD = os.getenv("NEO4J_PASSWORD") or "changeme",
  --         --   },
  --         -- },
  --         -- time = {
  --         --   command = "npx",
  --         --   args = { "-y", "@modelcontextprotocol/server-time" },
  --         -- },
  --         -- notifications = {
  --         --   command = "npx",
  --         --   args = { "-y", "@anthropic/mcp-server-notifications" },
  --         -- },
  --       },
  --       extensions = {
  --         avante = {
  --           make_slash_commands = true,
  --         },
  --       },
  --     })
  --   end,
  -- },
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
          ["kiro"] = {
            command = "kiro-cli",
            args = { "acp" },
          },
        },

        rag_service = {
          enabled = true,
          host_mount = os.getenv("HOME"),
          runner = "docker",

          llm = {
            provider = "openai",
            endpoint = "http://127.0.0.1:8000/",
            api_key = "KIRO_API_KEY",
            model = "claude-opus-4.6",
          },

          embed = {
            provider = "ollama",
            endpoint = "http://127.0.0.1:11434",
            api_key = "",
            model = "nub235/voyage-4-nano",
            extra = nil,
          },
        },

        web_search_engine = {
          provider = "kagi",
        },
      })
    end,
  },
}
