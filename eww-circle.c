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
    // int bg_color = 0x690899;
    char* bg_color = "690899";
    char* *colors ;
    int color_number = 2;
   	colors = malloc(color_number * sizeof(char*));
   	colors[0] = "ff00ff";
   	colors[1] = "ff0073";

    char path [400] ;
    strcpy(path, getenv("HOME")); //TODO : use XDG ??
    strcat(path, "/.config/crcl-select/theme.json");
    
    json_error_t error;
    json_t *root = json_load_file(path, 0, &error);
    if (!root) {
        fprintf(stderr, "JSON error: %s\n Fallback /etc/crcl-select/theme.json\n", error.text);
        snprintf(path, sizeof(path), "/etc/crcl-select/theme.json");
		root = json_load_file(path, 0, &error);
    }
	if (!root) {
		fprintf(stderr, "JSON error: %s\n", error.text);
		system("toilet RATIO");
       	return 1;
    } else {
        json_t* theme = json_object_get(root, 
            (argc >= 3 ? 
                argv[2] : 
                (
                    json_string_value(json_object_get(root, "default"))
                )
            ));
			// if (argc >= 3)
   //          system("notify-send \"JSON error: theme not found\n fallback default theme\"");
            if (theme == json_null()){
            	fprintf(stderr, "JSON error: theme not found\n fallback default theme"); 	
            	theme = json_object_get(root, 
            	                (
            	                    json_string_value(json_object_get(root, "default"))
            	                )
            	            );
            }         
            if (theme == json_null()) {
            	fprintf(stderr, "JSON error: no default theme\n fallback piink theme (hardcoded)");
            } else {
	            bg_color = (char*)(json_string_value(json_object_get(theme, "bg")));

	            json_t* color_table = json_object_get(theme, "colors");
	            color_number = json_array_size(color_table);
	            colors = malloc(color_number * sizeof(char*));
	            for (int i = 0; i < color_number; i++)
	            {
	                colors[i] = (char*) json_string_value(json_array_get(color_table, i));
	            }
            }
            
        }


    strcpy(path, getenv("HOME"));
    strcat(path, "/.config/crcl-select/");
    strcat(path, argv[1]);
    root = json_load_file(path, 0, &error);
    if (!root) {
        fprintf(stderr, "JSON error: %s\n Fallback /etc/crcl-select/%s\n", error.text, argv[1]);
        snprintf(path, sizeof(path), "/etc/crcl-select/%s", argv[1]);
		root = json_load_file(path, 0, &error);
		if (!root) {
			fprintf(stderr, "JSON error: %s\n", error.text);
			system("toilet RATIO");
        	return 1;
        }
    }
    unsigned int  count = json_array_size(root);
    AppEntry *entries = calloc(count, sizeof(AppEntry));
    


    for (size_t i = 0; i < count; i++) {
        json_t *item = json_array_get(root, i);

        const char *cmd = json_string_value(json_object_get(item, "command"));
        const char *icon = json_string_value(json_object_get(item, "icon"));

        snprintf(entries[i].command, sizeof(entries[i].command), "%s", cmd);
        // Check if icon contains $()
        if (icon && icon[0] == '$' && icon[1] == '#') {
            // Extract and execute the command
            // For example: if icon is "$(echo 󰈹)" extract "echo 󰈹"
            FILE *fp = popen(icon + 2, "r");  // skip "$#"
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
    (circular-progress :value 50 :thickness 0 :style \"background:none; font-size: 300; color : rgba(40, 0, 78, 0)\" \"L    ?\" \n)\
        "); //${round(EWW_BATTERY.total_avg, 0)}󰏰  ${angle}

    for (size_t i = 0; i < count; i++) {
        float angle = (float)i / count * 2* M_PI;
        float s_angle = (angle - M_PI / count) * 180 / M_PI; // Convert to degrees for styling
        float e_angle = (angle + M_PI / count) * 180 / M_PI; // Convert to degrees for styling
        printf("(overlay\
             (circular-progress  :start-at %f :value %f :thickness 60 :style \"color : #${(angle > %f %s angle < %f) ? '%s' : '%s'}\" \n)\
                (transform :translate-x %f \n :translate-y %f \n", 
                100 - e_angle/3.6, 100.0/count,
                    s_angle +   (i == 0 ? 360 : 0),
                                (i == 0) ? "||"     : "&&",
                    e_angle,
                    colors[i % color_number],
                    bg_color,
                    155     * cos(angle),
                    -155    * sin(angle)
                    ); 
                    printf("(button \
                        :style \"color : #${(angle > %f %s angle < %f) ? '%s' : '%s'}; font-size: 35px;\"\
                        :halign \"center\"\n\
                        :valign \"center\"\n\
                        :onclick \"%s &\" \"%s\"\n\
                        )",
                        s_angle +   (i == 0 ? 360 : 0),
                        (i == 0) ? "||"     : "&&",
                        e_angle,
                        bg_color,
                        colors[i % color_number],
                        entries[i].command, entries[i].icon);

                printf(")\n");
            printf(")\n");
                // printf("circle-part :i \"%zu\" :total \"%zu\" :cmd \"%s\" :icon \"%s\")\n", i, count, entries[i].command, entries[i].icon);
        }
        printf("(label\
	        	:style \"font-size:4em; color :#${");
	    for	(int i = 0; i < color_number; i++)
	    	printf("((angle %% %f) < %f) ? '%s' :\n",
	    	1.0 * color_number * (360 / count),
	    	1.0 * i * (360/count) + 180 / count,
	    	colors[i]
	    	);

	    printf("'%s'};\"\
	        	:text \"${round(EWW_BATTERY.total_avg, 0)}󰏰\"\
			)\
        )\n", colors[0]);
    
    
    free(entries);
    free(colors);
    json_decref(root);

    return 0;
}
