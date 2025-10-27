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
  "yetone/avante.nvim",
  -- if you want to build from source then do `make BUILD_FROM_SOURCE=true`
  -- ⚠️ must add this setting! ! !
  build = function()
    -- conditionally use the correct build system for the current OS
    if vim.fn.has("win32") == 1 then
      return "powershell -ExecutionPolicy Bypass -File Build.ps1 -BuildFromSource false"
    else
      return "make BUILD_FROM_SOURCE=true"
    end
  end,
  event = "VeryLazy",
  version = false, -- Never set this value to "*"! Never!
  keys = {
    {
      "<leader>A+",
      function()
        local tree_ext = require("avante.extensions.nvim_tree")
        tree_ext.add_file()
      end,
      desc = "Select file in NvimTree",
      ft = "NvimTree",
    },
    {
      "<leader>A-",
      function()
        local tree_ext = require("avante.extensions.nvim_tree")
        tree_ext.remove_file()
      end,
      desc = "Deselect file in NvimTree",
      ft = "NvimTree",
    },
  },
  opts = {
    auto_suggestions_provider = "aihubmix",
    provider = "aihubmix",
    cursor_applying_provider = "aihubmix",
    behavior = {
      auto_suggestions = true,
      enable_cursor_planning_mode = true,
      max_completion_tokens = 32768,
    },
    providers = {
      aihubmix = {
        model = "gpt-4o-2024-11-20",
      },
      web_search_engine = {
        provider = "kagi",
        proxy = nil,
      },
    },
    selector = {
      exclude_auto_select = { "NvimTree" },
    },
    mappings = {
      ---@class AvanteConflictMappings
      -- diff = {
      --   ours = "co",
      --   theirs = "ct",
      --   all_theirs = "ca",
      --   both = "cb",
      --   cursor = "cc",
      --   next = "]x",
      --   prev = "[x",
      -- },
      -- suggestion = {
      --   accept = "<M-l>",
      --   next = "<M-]>",
      --   prev = "<M-[>",
      --   dismiss = "<C-]>",
      -- },
      -- jump = {
      --   next = "]]",
      --   prev = "[[",
      -- },
      -- submit = {
      --   normal = "<CR>",
      --   insert = "<C-s>",
      -- },
      -- cancel = {
      --   normal = { "<C-c>", "<Esc>", "q" },
      --   insert = { "<C-c>" },
      -- },
      -- -- NOTE: The following will be safely set by avante.nvim
      ask = "<leader>Aa",
      new_ask = "<leader>An",
      edit = "<leader>Ae",
      refresh = "<leader>Ar",
      focus = "<leader>Af",
      stop = "<leader>AS",
      toggle = {
        default = "<leader>At",
        debug = "<leader>Ad",
        hint = "<leader>Ah",
        suggestion = "<leader>As",
        repomap = "<leader>AR",
      },
      -- sidebar = {
      --   apply_all = "A",
      --   apply_cursor = "a",
      --   retry_user_request = "r",
      --   edit_user_request = "e",
      --   switch_windows = "<Tab>",
      --   reverse_switch_windows = "<S-Tab>",
      --   remove_file = "d",
      --   add_file = "@",
      --   close = { "q" },
      --   ---@alias AvanteCloseFromInput { normal: string | nil, insert: string | nil }
      --   ---@type AvanteCloseFromInput | nil
      --   close_from_input = nil, -- e.g., { normal = "<Esc>", insert = "<C-d>" }
      -- },
      files = {
        add_current = "<leader>Ac", -- Add current buffer to selected files
        add_all_buffers = "<leader>AB", -- Add all buffer files to selected files
      },
      select_model = "<leader>A?",
      select_history = "<leader>Ah",
      -- confirm = {
      --   focus_window = "<C-w>f",
      --   code = "c",
      --   resp = "r",
      --   input = "i",
      -- },
    },
  },
  dependencies = {
    "nvim-lua/plenary.nvim",
    "MunifTanjim/nui.nvim",
    --- The below dependencies are optional,
    "nvim-mini/mini.pick", -- for file_selector provider mini.pick
    "nvim-telescope/telescope.nvim", -- for file_selector provider telescope
    "hrsh7th/nvim-cmp", -- autocompletion for avante commands and mentions
    "ibhagwan/fzf-lua", -- for file_selector provider fzf
    "stevearc/dressing.nvim", -- for input provider dressing
    "folke/snacks.nvim", -- for input provider snacks
    "nvim-tree/nvim-web-devicons", -- or echasnovski/mini.icons
    "zbirenbaum/copilot.lua", -- for providers='copilot'
    {
      -- support for image pasting
      "HakonHarnes/img-clip.nvim",
      event = "VeryLazy",
      opts = {
        -- recommended settings
        default = {
          embed_image_as_base64 = false,
          prompt_for_file_name = false,
          drag_and_drop = {
            insert_mode = true,
          },
          -- required for Windows users
          use_absolute_path = true,
        },
      },
    },
    {
      -- Make sure to set this up properly if you have lazy=true
      "MeanderingProgrammer/render-markdown.nvim",
      opts = {
        file_types = { "markdown", "Avante" },
      },
      ft = { "markdown", "Avante" },
    },
  },
}
