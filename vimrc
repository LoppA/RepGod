colorscheme delek
set number
set autoindent
set tabstop=4
set shiftwidth=4

au BufNewFile ~/Directory/*.cpp 0r ~/TemplateDirectory/base.cpp

function! NewJava()
	silent! 0r ~/TemplateDirectory/base.java
	%s/TemplatePublicClassName/\=expand("%:t:r")
endfunction

autocmd BufNewFile ~/Directory/*.java call NewJava()
