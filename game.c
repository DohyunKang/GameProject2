#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "game.h"

#if 01

void background(int n)
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return ;
    }
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.png", n);
    ALLEGRO_BITMAP* image = al_load_bitmap(filename);

    if (!image) {
        printf("couldn't load images : %s\n",filename);
        return ;
    }
    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(image);
    float img_height = al_get_bitmap_height(image);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_init_primitives_addon();
    
    al_draw_scaled_bitmap(image,0, 0, img_width, img_height, 0, 0, screen_width, screen_height,0);
    
    if ((n == 1) || (n == 2) || (n == 3)) {
        al_draw_filled_rectangle(200, 200, 900, 600, al_map_rgb(0, 0, 0));
    }
    ALLEGRO_BITMAP* ingame_male = al_load_bitmap("ingame_male.png");
    if (!ingame_male) {
        printf("couldn't load character image\n");
        al_destroy_bitmap(image);
        return;
    }
    
    al_draw_scaled_bitmap(ingame_male,0,0,al_get_bitmap_width(ingame_male),al_get_bitmap_height(ingame_male),0,0,150,150,0);
    al_flip_display();
    al_destroy_bitmap(image);
}

int main() {
    if (!al_init()) return 1;
    if (!al_init_image_addon()) return 1;
    ALLEGRO_DISPLAY* disp = al_create_display(1200, 900);
    if (!disp) return 1;
    background(1);
    al_rest(20.0);
    al_destroy_display(disp);
    return 0;
}
#endif