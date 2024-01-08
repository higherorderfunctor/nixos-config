{config, ...}: let
  cfg = config.colors;
in {
  imports = [./colors.nix];
  colors = {
    blue = "#89B4FA";
    green = "#a6e3a1";
    red = "#f38ba8";
    highlights = {
      text = {
        fg = "#cdd6f4"; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
      color0 = {fg = "#f5e0dc";}; #  	Rosewater 	#f5e0dc 	rgb(245, 224, 220) 	hsl(10, 56%, 91%)
      color1 = {fg = "#f2cdcd";}; # 	Flamingo 	#f2cdcd;#  	Rosewater 	#f5e0d 	rgb(242, 205, 205) 	hsl(0, 59%, 88%)
      color2 = {fg = "#f5c2e7";}; # 	Pink 	#f5c2e7 	r;#  	Rosewater 	#f5e0dgb(245, 194, 231) 	hsl(316, 72%, 86%)
      color3 = {fg = "#cba6f7";}; # 	Mauve 	#cba6f7  ;#  	Rosewater 	#f5e0d rgb(203, 166, 247) 	hsl(267, 84%, 81%)
      color4 = {fg = cfg.red;}; # 	Red 	#f38ba8 	r;#  	Rosewater 	#f5e0dgb(243, 139, 168) 	hsl(343, 81%, 75%)
      color5 = {fg = "#eba0ac";}; # 	Maroon 	#eba0ac  ;#  	Rosewater 	#f5e0d rgb(235, 160, 172) 	hsl(350, 65%, 77%)
      color6 = {fg = "#fab387";}; # 	Peach 	#fab387  ;#  	Rosewater 	#f5e0d rgb(250, 179, 135) 	hsl(23, 92%, 75%)
      color7 = {fg = "#f9e2af";}; # 	Yellow 	#f9e2af  ;#  	Rosewater 	#f5e0d rgb(249, 226, 175) 	hsl(41, 86%, 83%)
      color8 = {fg = cfg.green;}; # 	Green 	#a6e3a1  ;#  	Rosewater 	#f5e0d rgb(166, 227, 161) 	hsl(115, 54%, 76%)
      color9 = {fg = "#94e2d5";}; # 	Teal 	#94e2d5 	r;#  	Rosewater 	#f5e0dgb(148, 226, 213) 	hsl(170, 57%, 73%)
      color10 = {fg = "#89dceb";}; # 	Sky 	#89dceb 	r;#  	Rosewater 	#f5e0dgb(137, 220, 235) 	hsl(189, 71%, 73%)
      color11 = {fg = "#74c7ec";}; # 	Sapphire 	#74c7ec;#  	Rosewater 	#f5e0d 	rgb(116, 199, 236) 	hsl(199, 76%, 69%)
      color12 = {fg = cfg.blue;}; # 	Blue 	#89b4fa 	r;#  	Rosewater 	#f5e0dgb(137, 180, 250) 	hsl(217, 92%, 76%)
      color13 = {fg = "#b4befe";}; # 	Lavender 	#b4befe;#  	Rosewater 	#f5e0d 	rgb(180, 190, 254) 	hsl(232, 97%, 85%)
    };
  };
}
# 	Subtext1 	#bac2de 	rgb(186, 194, 222) 	hsl(227, 35%, 80%)
# 	Subtext0 	#a6adc8 	rgb(166, 173, 200) 	hsl(228, 24%, 72%)
# 	Overlay2 	#9399b2 	rgb(147, 153, 178) 	hsl(228, 17%, 64%)
# 	Overlay1 	#7f849c 	rgb(127, 132, 156) 	hsl(230, 13%, 55%)
# 	Overlay0 	#6c7086 	rgb(108, 112, 134) 	hsl(231, 11%, 47%)
# 	Surface2 	#585b70 	rgb(88, 91, 112) 	hsl(233, 12%, 39%)
# 	Surface1 	#45475a 	rgb(69, 71, 90) 	hsl(234, 13%, 31%)
# 	Surface0 	#313244 	rgb(49, 50, 68) 	hsl(237, 16%, 23%)
# 	Base 	#1e1e2e 	rgb(30, 30, 46) 	hsl(240, 21%, 15%)
# 	Mantle 	#181825 	rgb(24, 24, 37) 	hsl(240, 21%, 12%)
# 	Crust 	#11111b 	rgb(17, 17, 27) 	hsl(240, 23%, 9%)
