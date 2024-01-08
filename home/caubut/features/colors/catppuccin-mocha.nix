{config, ...}: let
  template = {
    rosewater = "#f5e0dc";
    flamingo = "#f2cdcd";
    pink = "#f5c2e7";
    mauve = "#cba6f7";
    red = "#f38ba8";
    maroon = "#eba0ac";
    peach = "#fab387";
    yellow = "#f9e2af";
    green = "#a6e3a1";
    teal = "#94e2d5";
    sky = "#89dceb";
    sapphire = "#74c7ec";
    blue = "#89b4fa";
    lavender = "#b4befe";
    text = "#cdd6f4";
    subtext1 = "#bac2de";
    subtext0 = "#a6adc8";
    overlay2 = "#9399b2";
    overlay1 = "#7f849c";
    overlay0 = "#6c7086";
    surface2 = "#585b70";
    surface1 = "#45475a";
    surface0 = "#313244";
    base = "#1e1e2e";
    mantle = "#181825";
    crust = "#11111b";
  };
in {
  imports = [./colors.nix];
  colors = {
    black = template.base;
    inherit (template) blue;
    cyan = template.teal;
    inherit (template) green;
    magenta = template.maroon;
    inherit (template) red;
    white = template.text;
    inherit (template) yellow;
    highlights = {
      text = {
        fg = template.text;
      };
      prompt0 = {
        fg = template.yellow; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
      prompt1 = {
        fg = template.sky; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
      prompt2 = {
        fg = template.mauve; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
      username = {
        fg = template.teal; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
      hostname = {
        fg = template.teal; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
      directory = {
        fg = template.pink; # 	Text 	#cdd6f4 	rgb(205, 214, 244) 	hsl(226, 64%, 88%)
      };
    };
  };
}
