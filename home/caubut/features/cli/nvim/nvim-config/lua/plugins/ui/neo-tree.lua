return {
  "nvim-neo-tree/neo-tree.nvim",
  opts = {
    default_component_configs = {
      file_size = { enabled = false },
      last_modified = { enabled = false },
      created = { enabled = false },
      symlink_target = { enabled = true },
    },
    buffers = {
      follow_current_file = { enabled = true, leave_open = true },
    },
    filesystem = {
      filtered_items = { visible = true },
      follow_current_file = { enabled = true, leave_open = true },
      window = {
        mappings = {
          ["O"] = "system_open",
        },
      },
      components = {
        name = function(config, node, state)
          local fc = require("neo-tree.sources.filesystem.components")
          local result = fc.name(config, node, state)
          if vim.fn.isdirectory(node.path) ~= 0 then
            return result
          end
          local permissions = vim.fn.getfperm(node.path)
          if string.match(permissions, "x", 3) then
            result.text = result.text .. " 󱆃"
            if result.highlight == "NeoTreeFileName" then
              result.highlight = "NeoTreeExecutableTarget"
            end
          end
          return result
        end,
      },
      commands = {
        -- move deleted files to the trash
        delete = function(state)
          local path = state.tree:get_node().path
          vim.fn.system({ "gio", "trash", vim.fn.fnameescape(path) })
          require("neo-tree.sources.manager").refresh(state.name)
        end,
        system_open = function(state)
          local node = state.tree:get_node()
          local path = node:get_id()
          -- macOs: open file in default application in the background.
          vim.fn.jobstart({ "xdg-open", "-g", path }, { detach = true })
          -- Linux: open file in default application
          vim.fn.jobstart({ "xdg-open", path }, { detach = true })
        end,
      },
    },
  },
}
