#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <math.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <json_file> <angle>\n", argv[0]);
        return 1;
    }

    const char *json_filename = argv[1];
    float angle = atof(argv[2]);

    // Normalize angle to 0-360
    angle = fmod(angle, 360.0f);
    if (angle < 0) angle += 360.0f;

    // Build full path
    char path[512];
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Error: HOME environment variable not set\n");
        return 1;
    }
    snprintf(path, sizeof(path), "%s/.config/crcl-select/%s", home, json_filename);

    // Load JSON
    json_error_t error;
    json_t *root = json_load_file(path, 0, &error);
    if (!root) {
        fprintf(stderr, "JSON error: %s\n Fallback /etc/crcl-select/%s\n", error.text, json_filename);
        snprintf(path, sizeof(path), "/etc/crcl-select/%s", json_filename);
		root = json_load_file(path, 0, &error);
		if (!root) {
			fprintf(stderr, "JSON error: %s\n", error.text);
			system("toilet RATIO");
        	return 1;
        }
    }

    size_t count = json_array_size(root);
    if (count == 0) {
        fprintf(stderr, "Error: Empty JSON array\n");
        json_decref(root);
        return 1;
    }

    size_t index = 0;
    if (argc == 3)
    {
        
        // Calculate which entry the angle points to
        // Each entry spans 360/count degrees
        float sector_size = 360.0f / count;
         index = (size_t)((angle + sector_size/2) / sector_size) ;
    } else {
        index = atoi (argv[2]);
    }
        if (index >= count) index = 0; // Wrap around
        // Extract command
        json_t *item = json_array_get(root, index);
        const char *command = json_string_value(json_object_get(item, "command"));

    if (!command) {
        fprintf(stderr, "Error: Could not extract command at index %zu\n", index);
        json_decref(root);
        return 1;
    }

    // Execute command
    int result = system(command);

    json_decref(root);
    return (result == -1) ? 1 : 0;
}
