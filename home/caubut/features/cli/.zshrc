
# export ZSH="$HOME/.oh-my-zsh"

# theme
# ZSH_THEME="robbyrussell"

# static plugins
# plugins=(
#   git
# )

# poetry plugin
[[ -f ~/.local/bin/poetry ]] && plugins+=('poetry')

# fzf plugin
# [ -f ~/.fzf.zsh ] && source ~/.fzf.zsh

if [[ ! -d ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/plugins/fast-syntax-highlighting ]]; then
  git clone https://github.com/zdharma-continuum/fast-syntax-highlighting.git \
  ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/plugins/fast-syntax-highlighting
fi

plugins+=('fast-syntax-highlighting')

# oh-my-zsh
source $ZSH/oh-my-zsh.sh

# custom completions
fpath=("$ZSH_CUSTOM/completions" $fpath)

# vim bindings
bindkey -v

# history
setopt HIST_IGNORE_SPACE

# envs
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

# eval "$(oh-my-posh init zsh --config '~/.config/oh-my-posh/catppuccin.omp.json')"

if ! fast-theme --show | grep -q 'catppuccin-mocha'; then
  fast-theme XDG:catppuccin-mocha
fi
