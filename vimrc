colorscheme delek
set number
set autoindent
set tabstop=4
set shiftwidth=4

au BufNewFile ~/Documents/*.cpp 0r ~/Documents/base.cpp

function! NewJava()
	silent! 0r ~/Documents/base.java
	%s/TODO/\=expand("%:t:r")
endfunction

autocmd BufNewFile ~/Documents/*.java call NewJava()
