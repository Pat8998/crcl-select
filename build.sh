cd ~/.config/crcl-select
gcc Circle.c    -O3 -o circle-gen   -ljansson -lm
gcc execute.c   -O3 -o exe          -ljansson -lm
gcc angle.c     -O3 -o angle        -ljansson -lm