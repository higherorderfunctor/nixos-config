local ai_hub_mix_api_key_path = vim.fn.expand("/run/user/1000/secrets/caubut-ai-hub-mix-api-key")
local kagi_api_key_path = vim.fn.expand("/run/user/1000/secrets/caubut-ai-hub-mix-api-key")

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

local ai_hub_mix_api_key = read_file(ai_hub_mix_api_key_path)
if ai_hub_mix_api_key then
  vim.env.AVANTE_AIHUBMIX_API_KEY = ai_hub_mix_api_key
end

local kagi_api_key = read_file(kagi_api_key_path)
if kagi_api_key then
  vim.env.KAGI_API_KEY = kagi_api_key
end

return {
  {
    "yetone/avante.nvim",
    opts = function(_, opts)
      return vim.tbl_deep_extend("force", opts or {}, {
        provider = "aihubmix",
        auto_suggestions_provider = "aihubmix",

        behavior = {
          auto_suggestions = true,
        },

        providers = {
          aihubmix = {
            model = "gpt-5.1-chat-latest",
            api_key_name = "AVANTE_AIHUBMIX_API_KEY",
          },
          copilot = {},
        },

        rag_service = {
          enabled = true,
          host_mount = os.getenv("HOME"),
          runner = "docker",

          -- LLM used by the RAG service for query processing
          llm = {
            provider = "openai",
            endpoint = "https://aihubmix.com/v1",
            api_key = "AVANTE_AIHUBMIX_API_KEY", -- env var name, not the key itself
            model = "gpt-4o-mini", -- cheap model for RAG internals
          },

          -- Embedding model — local via Ollama, no API cost
          embed = {
            provider = "ollama",
            endpoint = "http://127.0.0.1:11434",
            api_key = "", -- Ollama doesn't need a key,
            model = "nub235/voyage-4-nano", -- code-optimized embeddings
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
