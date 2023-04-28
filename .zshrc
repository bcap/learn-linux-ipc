# PATH=/linux-ipc/bin:$PATH

alias ls='ls --color=auto'
alias ll='ls -lhp'
alias la='ll -A'


# auto completion stuff
zmodload -i zsh/complist
zstyle ':completion:*' matcher-list 'm:{a-zA-Z}={A-Za-z}' 'r:|[._-]=* r:|=*' 'l:|=* r:|=*'
zstyle ':completion:*' list-colors ''
zstyle ':completion:*:*:*:*:*' menu select
zstyle ':completion:*:cd:*' tag-order local-directories directory-stack path-directories
zstyle ':completion::complete:*' use-cache 1
zstyle ':completion::complete:*' cache-path ~/.zshcache/
zstyle '*' single-ignored show

autoload -U compinit
compinit -i