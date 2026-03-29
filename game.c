#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "game.h"

#if 01
void background(int n, Player* p)
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return;
    }
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.png", n);
    ALLEGRO_BITMAP* image = al_load_bitmap(filename);

    if (!image) {
        printf("couldn't load images : %s\n", filename);
        return;
    }
    int screen_width = 1200;
    int screen_height = 900;
    float img_width = al_get_bitmap_width(image);
    float img_height = al_get_bitmap_height(image);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_init_primitives_addon();

    al_draw_scaled_bitmap(image, 0, 0, img_width, img_height, 0, 0, screen_width, screen_height, 0);

    if ((n == 1) || (n == 2) || (n == 3)) {
        al_draw_filled_rectangle(200, 200, 900, 600, al_map_rgb(0, 0, 0));
    }

    if (p->gender == 1) {
        ALLEGRO_BITMAP* ingame_male = al_load_bitmap("ingame_male.png");
        if (!ingame_male) {
            printf("couldn't load character image\n");
            return;
        }
        al_draw_scaled_bitmap(ingame_male, 0, 0, al_get_bitmap_width(ingame_male), al_get_bitmap_height(ingame_male), 0, 0, 130, 130, 0);
    }

    if (p->gender == 2) {
        ALLEGRO_BITMAP* ingame_female = al_load_bitmap("ingame_female.png");
        if (!ingame_female) {
            printf("couldn't load character image\n");
            return;
        }
        al_draw_scaled_bitmap(ingame_female, 0, 0, al_get_bitmap_width(ingame_female), al_get_bitmap_height(ingame_female), 0, 0, 130, 130, 0);
    }
        al_flip_display();
        al_destroy_bitmap(image);   
}
void drawhearts(Player* p) {
  ALLEGRO_BITMAP* heart = al_load_bitmap("heart.png");
    if (!heart) {
        printf("couldn't load image\n");
        return;
    }
    for (int i = 0; i < p->hp; i++) {
        al_draw_scaled_bitmap(heart,0,0,al_get_bitmap_width(heart), al_get_bitmap_height(heart), 140+(50*i), 10, 50, 50, 0);
    }
    al_flip_display();
    al_destroy_bitmap(heart);
}

//이거 보물상자 관련해서 어디있는지 잘 모르겠음
void drawtreasurebox(Player* p) {
    ALLEGRO_BITMAP* treasure = al_load_bitmap("treasurebox.png");
    if (!treasure) {
        printf("couldn't load image\n");
        return;
    }
    for (int i = 0; i < p->hp; i++) {
        al_draw_scaled_bitmap(treasure, 0, 0, al_get_bitmap_width(treasure), al_get_bitmap_height(treasure), 140 + (50 * i), 30, 50, 50, 0);
    }
    al_flip_display();
    al_destroy_bitmap(treasure);
}

void printtime(ALLEGRO_FONT* font,double start_time,int x,int y) {
    al_init_font_addon();
    double current_time = al_get_time();
    double elapsed_time = current_time - start_time;
    al_draw_textf(font,al_map_rgb(255, 255, 255), x, y,ALLEGRO_ALIGN_LEFT, "Time : %.2f", elapsed_time);
}

void stagenum() { //여기는 시간부분 해결되면 진행할 예정 아마 얼마 안걸릴듯

}

int main() {
    if (!al_init()) return 1;
    if (!al_init_image_addon()) return 1;
    ALLEGRO_DISPLAY* disp = al_create_display(1200, 900);
    ALLEGRO_FONT* font= al_create_builtin_font();
    if (!disp) return 1;
    Player* current= (Player *)calloc(1,sizeof(Player));
    current->gender = 1;
    current->hp = 3;
    background(1,current);
    printtime(font,0, 800, 200);
    drawhearts(current);
    al_rest(20.0);//그냥 테스트로 20초 살려놓기
    free(current);
    al_destroy_font(printtime);
    al_destroy_display(disp);
    return 0;
}
#endif