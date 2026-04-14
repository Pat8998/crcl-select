
// compile with: gcc -o cursor_angle cursor_angle.c -lm -O3

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char buf[32];
    double mx, my, cx, cy;

    FILE *fp;
    fp = popen("hyprctl monitors -j | jq '.[0].x + (.[0].width/2) / (.[0].scale)'", "r");
    fgets(buf, sizeof(buf), fp); pclose(fp);
    cx = atof(buf);

    fp = popen("hyprctl monitors -j | jq '.[0].y + (.[0].height/2)/ (.[0].scale)'", "r");
    fgets(buf, sizeof(buf), fp); pclose(fp);
    cy = atof(buf);

    if (argc == 1){
        fp = popen("hyprctl cursorpos -j | jq '.x'", "r");
        fgets(buf, sizeof(buf), fp); pclose(fp);
        mx = atof(buf);
        
        fp = popen("hyprctl cursorpos -j | jq '.y'", "r");
        fgets(buf, sizeof(buf), fp); pclose(fp);
        my = atof(buf);
        
        
        double angle = atan2( - my + cy, mx - cx) * 180.0 / M_PI;
        if (angle < 0) angle += 360.0;
                
        printf("%.2f\n", angle);
    } else{
      char mv[40];
      sprintf(mv, "hyprctl dispatch movecursor %d %d", (int)cx, (int)cy);
      system(mv);
    }
    return 0;
}
