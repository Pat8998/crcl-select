#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#define M_PI 25
#include <math.h>
typedef struct {
    char icon[64];      // nerdfont char or generated icon
    char command[256];
    int icon_is_cmd;    // 1 if icon field is a shell command to run
} AppEntry;


int main(int argc, char** argv){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <json_name>\n", argv[0]);
        return 1;
    }
    int hilighted = 0x690899;
    int color [2] = {
        0xff00ff, // color1
        0xff0073,    // color2
    };
    int color_number = 2;


    char path [400] ;
    strcpy(path, getenv("HOME"));
    strcat(path, "/.config/crcl-select/");
    strcat(path, argv[1]);
    json_error_t error;
    json_t *root = json_load_file(path, 0, &error);
    if (!root) {
        fprintf(stderr, "JSON error: %s\n", error.text);
        return 1;
    }
    size_t count = json_array_size(root);
    AppEntry *entries = calloc(count, sizeof(AppEntry));
    // printf("%s\n\ncaca\n", path);
    


    for (size_t i = 0; i < count; i++) {
        json_t *item = json_array_get(root, i);

        const char *cmd = json_string_value(json_object_get(item, "command"));
        const char *icon = json_string_value(json_object_get(item, "icon"));
        // int icon_is_cmd = json_boolean_value(json_object_get(item, "icon_is_cmd"));

        snprintf(entries[i].command, sizeof(entries[i].command), "%s", cmd);
        // Check if icon contains $()
        if (icon && icon[0] == '$' && icon[1] == '#') {
            // Extract and execute the command
            // For example: if icon is "$(echo 󰈹)" extract "echo 󰈹"
            FILE *fp = popen(icon + 2, "r");  // skip "$("
            if (fp) {
                char buffer[64];
                fgets(buffer, sizeof(buffer), fp);
                pclose(fp);
                // Remove trailing newline
                buffer[strcspn(buffer, "\n")] = 0;
                snprintf(entries[i].icon, sizeof(entries[i].icon), "%s", buffer);
            }
        } else {
            snprintf(entries[i].icon, sizeof(entries[i].icon), "%s", icon);
        }
    }


    // Generate yuck markup
    printf("(overlay :width 300 :height 300 \n\
        (circular-progress :value 50 :thickness 60 :style \"background-color : #0f0; font-size: 300; color : rgb(71, 2, 136)\" \"L    ?\" \n)"); //${round(EWW_BATTERY.total_avg, 0)}󰏰  ${angle}

    for (size_t i = 0; i < count; i++) {
        float angle = (float)i / count * 2* M_PI;
        float s_angle = (angle - M_PI / count) * 180 / M_PI; // Convert to degrees for styling
        float e_angle = (angle + M_PI / count) * 180 / M_PI; // Convert to degrees for styling
        printf("(overlay\
             (circular-progress  :start-at %f :value %f :thickness 60 :style \"color : #${(angle > %f %s angle < %f) ? '%06x' : '%06x'}\" \n)\
                (transform :translate-x %f \n :translate-y %f \n", 
                100 - e_angle/3.6, 100.0/count,
                    s_angle +   (i == 0 ? 360 : 0),
                                (i == 0) ? "||"     : "&&",
                    e_angle,
                    color[i % color_number],
                    hilighted,
                    155     * cos(angle),
                    -155    * sin(angle)
                    ); 
                    printf("(button \
                        :style \"color : #${(angle > %f %s angle < %f) ? '%06x' : '%06x'}; font-size: 35px;\"\
                        :halign \"center\"\n\
                        :valign \"center\"\n\
                        :onclick \"%s &\" \"%s\"\n\
                        )",
                        s_angle +   (i == 0 ? 360 : 0),
                        (i == 0) ? "||"     : "&&",
                        e_angle,
                        hilighted,
                        color[i % 2],
                        entries[i].command, entries[i].icon);

                printf(")\n");
            printf(")\n");
                // printf("circle-part :i \"%zu\" :total \"%zu\" :cmd \"%s\" :icon \"%s\")\n", i, count, entries[i].command, entries[i].icon);
        }
        printf(")\n");
    
    
    free(entries);
    json_decref(root);

    return 0;
}