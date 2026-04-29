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
        sprintf(cmd, "  echo %s > /tmp/crcl_json_name;\
                        echo %s > /tmp/crcl_theme;\
            crcl-angle 0 & eww open Circle -c /usr/share/crcl-select/",
            argv[2],
            (argc >= 4 ? argv[3] : "")
        );
        system(cmd);
    } else if (argv[1][0] == 'c')
    {
        char cmd[200];
        sprintf(cmd, "crcl-exe %s $(crcl-angle) &\
                    eww close-all -c /usr/share/crcl-select/",
            argv[2]);
        system(cmd);
    }
    return 0;   
}
