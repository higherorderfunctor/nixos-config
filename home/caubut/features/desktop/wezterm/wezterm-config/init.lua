-- Official doco: https://wezfurlong.org/wezterm/config/files.html

local wezterm = require("wezterm") -- Pull in the wezterm API
local act = wezterm.action -- for binding keys to actions
local gpus = wezterm.gui.enumerate_gpus()
-- local mux = wezterm.mux -- multiplexer layer: panes, tabs, windows, and workspaces

-- Debug
-- wezterm.log_level = "debug"
-- After restarting WezTerm:
-- $HOME/.local/share/wezterm/logs/ (on Linux/macOS)
-- %APPDATA%\wezterm\logs\ (on Windows)

wezterm.add_to_config_reload_watch_list(wezterm.config_dir .. "/wezterm-config/init.lua")

-- -- Config struct documentation
-- -- https://wezfurlong.org/wezterm/config/lua/config/index.html
local config = {} -- This table will hold the configuration.
if wezterm.config_builder then
	config = wezterm.config_builder()
end

config:set_strict_mode(true)
config.term = "wezterm"

config.webgpu_preferred_adapter = gpus[1]
config.front_end = "WebGpu"

--
-- Theme
--
local custom = wezterm.color.get_builtin_schemes()["Catppuccin Mocha"]
custom.background = "#000000"
custom.tab_bar.background = "#040404"
custom.tab_bar.inactive_tab.bg_color = "#0f0f0f"
custom.tab_bar.new_tab.bg_color = "#080808"

config.color_schemes = {
	["OLEDppuccin"] = custom,
}
config.color_scheme = "OLEDppuccin"

config.window_background_opacity = 0.90

--
-- Hyperlinks
--

-- https://wezfurlong.org/wezterm/hyperlinks.html

-- Terminal hyperlinks
-- https://gist.github.com/egmontkob/eb114294efbcd5adb1944c9f3cb5feda
-- printf '\e]8;;http://example.com\e\\This is a link\e]8;;\e\\\n'

-- Use the defaults as a base.  https://wezfurlong.org/wezterm/config/lua/config/hyperlink_rules.html
config.hyperlink_rules = wezterm.default_hyperlink_rules()

-- make username/project paths clickable. this implies paths like the following are for github.
-- ( "nvim-treesitter/nvim-treesitter" | wbthomason/packer.nvim | wez/wezterm | "wez/wezterm.git" )
-- as long as a full url hyperlink regex exists above this it should not match a full url to
-- github or gitlab / bitbucket (i.e. https://gitlab.com/user/project.git is still a whole clickable url)

-- Regex syntax:  https://docs.rs/regex/latest/regex/#syntax and https://docs.rs/fancy-regex/latest/fancy_regex/#syntax
-- Lua's [[ ]] literal strings prevent character [[:classes:]] :(
-- To avoid "]]] at end, use "[a-z].{0}]]"
-- https://www.lua.org/pil/2.4.html#:~:text=bracketed%20form%20may%20run%20for%20several%20lines%2C%20may%20nest

table.insert(config.hyperlink_rules, {
	-- https://github.com/shinnn/github-username-regex  https://stackoverflow.com/a/64147124/5353461
	regex = [[(^|(?<=[\[(\s'"]))([0-9A-Za-z][-0-9A-Za-z]{0,38})/([A-Za-z0-9_.-]{1,100})((?=[])\s'".!?])|$)]],
	--  is/good  0valid0/-_.reponname  /bad/start  -bad/username  bad/end!  too/many/parts -bad/username
	--  [wraped/name] (aa/bb) 'aa/bb' "aa/bb"  end/punct!  end/punct.
	format = "https://www.github.com/$2/$3/",
	-- highlight = 0,  -- highlight this regex match group, use 0 for all
})

--
-- Miscellaneous
--

config.enable_scroll_bar = true
config.hide_tab_bar_if_only_one_tab = true
config.initial_cols = 140
config.initial_rows = 40
config.exit_behavior = "CloseOnCleanExit" -- Use 'Hold' to not close

--
-- Fonts
--
-- https://wezfurlong.org/wezterm/config/lua/wezterm/font.html
-- https://wezfurlong.org/wezterm/config/lua/config/font_rules.html
-- wezterm ls-fonts
-- wezterm ls-fonts --list-system
--
-- config.font = wezterm.font 'JetBrains Mono'
-- config.font = wezterm.font 'Iosevka Term SS06'
-- config.font = wezterm.font({ family = 'Iosevka Term SS06', stretch = 'UltraCondensed'})
-- config.font = wezterm.font({ family = 'Iosevka SS06', stretch = 'UltraCondensed'})
config.font_size = 10.0
config.warn_about_missing_glyphs = true
config.freetype_load_target = "Normal" -- https://wezfurlong.org/wezterm/config/lua/config/freetype_load_target.html
-- HorizontalLcd
--config.foreground_text_hsb = {
--	hue = 1.1,
--	saturation = 0.5,
--	brightness = 0.0,
--}

local zz = "$999*"

-- Monaspace:  https://monaspace.githubnext.com/
-- Based upon, contributed to:  https://gist.github.com/ErebusBat/9744f25f3735c1e0491f6ef7f3a9ddc3
config.font = wezterm.font({ -- Normal text
	family = "MonaspiceNe Nerd Font Mono",
	harfbuzz_features = {
		"calt",
		"liga",
		"dlig",
		"ss01",
		"ss02",
		"ss03",
		"ss04",
		"ss05",
		"ss06",
		"ss07",
		"ss08",
	},
	weight = "Light",
	-- stretch = "UltraCondensed", -- This doesn't seem to do anything
})
wezterm.add_to_config_reload_watch_list(wezterm.config_dir .. "/wezterm-config/init.lua")

--  print("WezTerm config loaded")
--  wezterm.on("update-right-status", function(window, pane)
--  	-- Each element holds the text for a cell in a "powerline" style << fade
--  	local cells = {}
--
--  	-- Figure out the cwd and host of the current pane.
--  	-- This will pick up the hostname for the remote host if your
--  	-- shell is using OSC 7 on the remote host.
--  	local cwd_uri = pane:get_current_working_dir()
--  	if cwd_uri then
--  		local cwd = ""
--  		local hostname = ""
--
--  		if type(cwd_uri) == "userdata" then
--  			-- Running on a newer version of wezterm and we have
--  			-- a URL object here, making this simple!
--
--  			cwd = cwd_uri.file_path
--  			hostname = cwd_uri.host or wezterm.hostname()
--  		else
--  			-- an older version of wezterm, 20230712-072601-f4abf8fd or earlier,
--  			-- which doesn't have the Url object
--  			cwd_uri = cwd_uri:sub(8)
--  			local slash = cwd_uri:find("/")
--  			if slash then
--  				hostname = cwd_uri:sub(1, slash - 1)
--  				-- and extract the cwd from the uri, decoding %-encoding
--  				cwd = cwd_uri:sub(slash):gsub("%%(%x%x)", function(hex)
--  					return string.char(tonumber(hex, 16))
--  				end)
--  			end
--  		end
--
--  		-- Remove the domain name portion of the hostname
--  		local dot = hostname:find("[.]")
--  		if dot then
--  			hostname = hostname:sub(1, dot - 1)
--  -		end
--  		if hostname == "" then
--  			hostname = wezterm.hostname()
--  		end
--
--  		table.insert(cells, cwd)
--  		table.insert(cells, hostname)
--  	end
--
--  	-- I like my date/time in this style: "Wed Mar 3 08:14"
--  	local date = wezterm.strftime("%a %b %-d %H:%M")
--  	table.insert(cells, date)
--
--  	-- An entry for each battery (typically 0 or 1 battery)
--  	for _, b in ipairs(wezterm.battery_info()) do
--  		table.insert(cells, string.format("%.0f%%", b.state_of_charge * 100))
--  	end
--
--  -	-- The powerline < symbol
--  	local LEFT_ARROW = utf8.char(0xe0b3)
--  	-- The filled in variant of the < symbol
--  	local SOLID_LEFT_ARROW = utf8.char(0xe0b2)
--
--  	-- Color palette for the backgrounds of each cell
--  	local colors = {
--  		"#3c1361",
--  		"#52307c",
--  		"#663a82",
--  		"#7c5295",
--  		"#b491c8",
--  	}
--
--  	-- Foreground color for the text across the fade
--  	local text_fg = "#c0c0c0"
--
--  	-- The elements to be formatted
--  	local elements = { { Text = zz } }
--  	-- How many cells have been formatted
--  	local num_cells = 0
--
--  	-- Translate a cell into elements
--  	function push(text, is_last)
--  		local cell_no = num_cells + 1
--  		table.insert(elements, { Foreground = { Color = text_fg } })
--  		table.insert(elements, { Background = { Color = colors[cell_no] } })
--  		table.insert(elements, { Text = " " .. text .. " " })
--  		if not is_last then
--  			table.insert(elements, { Foreground = { Color = colors[cell_no + 1] } })
--  			table.insert(elements, { Text = SOLID_LEFT_ARROW })
--  		end
--  		num_cells = num_cells + 1
--  	end
--
--  	while #cells > 0 do
--  		local cell = table.remove(cells, 1)
--  		push(cell, #cells == 0)
--  	end
--
--  	window:set_right_status(wezterm.format(elements))
--  end)
--  config.enable_wayland = true
config.font_rules = {
	{ -- Italic
		intensity = "Normal",
		italic = true,
		font = wezterm.font({
			-- family="Monaspace Radon",  -- script style
			family = "MonaspiceXe Nerd Font Mono", -- courier-like
			style = "Italic",
		}),
	},

	{ -- Bold
		intensity = "Bold",
		italic = false,
		font = wezterm.font({
			family = "MonaspiceKr Nerd Font Mono",
			weight = "Bold",
		}),
	},

	{ -- Bold Italic
		intensity = "Bold",
		italic = true,
		font = wezterm.font({
			family = "MonaspiceRn Nerd Font Mono",
			style = "Italic",
			weight = "Bold",
		}),
	},
}

return config
