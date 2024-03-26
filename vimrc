set nu
-------
" 设置字体
set guifont=Monaco:h10


" 设置tap键是4
set ts=4
set expandtab

set history=500

" 显示括号自动匹配
set showmatch
set matchtime=5

" 设置对应的文本编码
filetype on
set fileencodings=utf-8,gb2312,gbk,gb18031
set termencoding=utf-8
set fileencoding=utf-8
set encoding=utf-8
set fileformat=unix


" 显示tab键
set list
set listchars=tab:>-,trail:-



" 增加鼠标行高亮
set cursorline
hi CursorLine cterm=NONE ctermbg=darkred ctermfg=white