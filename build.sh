cd ~/.config/crcl-select
gcc eww-circle.c    -O3 -o cr-circle-gen   -ljansson -lm
gcc eww-execute.c   -O3 -o cr-exe          -ljansson -lm
gcc eww-angle.c     -O3 -o cr-angle        -ljansson -lm
gcc eww-circle-select.c -o c-select     -O3