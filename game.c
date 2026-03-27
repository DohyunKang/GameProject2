#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#if 01

void background(int n)
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return 1;
    }
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.png", n);
    ALLEGRO_BITMAP* image = al_load_bitmap(filename);

    if (!image) {
        printf("couldn't load images : %s\n",filename);
        return 1;
    }
    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(image);
    float img_height = al_get_bitmap_height(image);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(image,0, 0, img_width, img_height, 0, 0, screen_width, screen_height,0);
    al_flip_display();
    al_destroy_bitmap(image);
   
}

int main() {
    if (!al_init()) return 1;
    if (!al_init_image_addon()) return 1;
    ALLEGRO_DISPLAY* disp = al_create_display(1200, 900);
    if (!disp) return 1;
    background(1);
    al_rest(3.0);
    al_destroy_display(disp);
    return 0;
}
#endif