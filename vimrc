set number
set relativenumber
set smartindent
set tabstop=4
set shiftwidth=4
"set expandtab

set showmatch
set mouse=a

set t_Co=256
set term=xterm-256color
set termguicolors
colorscheme desert

au BufNewFile ~/Directory/*.cpp 0r ~/TemplateDirectory/base.cpp

function! NewJava()
	silent! 0r ~/TemplateDirectory/base.java
	%s/TemplatePublicClassName/\=expand("%:t:r")
endfunction

autocmd BufNewFile ~/Directory/*.java call NewJava()
