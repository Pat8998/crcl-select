#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <open|close> <json_name>\n", argv[0]);
        return 1;
    }
    if (argv[1][0] == 'o')
    {
        char cmd[200];
        sprintf(cmd, "  echo %s > ~/.config/crcl-select/json_files/.json_name;\
                        echo %s >  ~/.config/crcl-select/.theme;\
            ~/.config/crcl-select/cr-angle 0 & eww open Circle -c ~/.config/crcl-select/",
            argv[2],
            (argc >= 4 ? argv[3] : "")
        );
        system(cmd);
    } else if (argv[1][0] == 'c')
    {
        char cmd[200];
        sprintf(cmd, "~/.config/crcl-select/cr-exe %s $(~/.config/crcl-select/cr-angle) &\
                    eww close-all -c ~/.config/crcl-select/",
            argv[2]);
        system(cmd);
    }
    return 0;   
}