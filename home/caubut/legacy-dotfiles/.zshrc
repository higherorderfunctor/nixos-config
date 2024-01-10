export PATH="$HOME/.local/bin:$PATH"
export MANPATH="$HOME/.local/man:$MANPATH"
export EDITOR="nvim"
export LESS='--mouse -R'
alias dotfiles='/usr/bin/git --git-dir=$HOME/.dotfiles/ --work-tree=$HOME'

# bitwarden
if command -v bw > /dev/null; then
  # TODO move to install script eval "$(bw completion --shell zsh); compdef _bw bw;"
fi

# tabtab source for packages
# uninstall by removing these lines
[[ -f ~/.config/tabtab/zsh/__tabtab.zsh ]] && . ~/.config/tabtab/zsh/__tabtab.zsh || true

# pnpm
export PNPM_HOME="/home/caubut/.local/share/pnpm"
case ":$PATH:" in
  *":$PNPM_HOME:"*) ;;
  *) export PATH="$PNPM_HOME:$PATH" ;;
esac
# pnpm end

# bun completions
[ -s "/home/caubut/.bun/_bun" ] && source "/home/caubut/.bun/_bun"

# bun
export BUN_INSTALL="$HOME/.bun"
export PATH="$BUN_INSTALL/bin:$PATH"

eval "$(oh-my-posh init zsh --config '~/.config/oh-my-posh/catppuccin.omp.json')"

if ! fast-theme --show | grep -q 'catppuccin-mocha'; then
  fast-theme XDG:catppuccin-mocha
fi
