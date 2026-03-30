#include "game.h"

#define FX_N 156

FX fx[FX_N];
SPRITES sprites;

void fx_init()
{
    for (int i = 0; i < FX_N; i++)
        fx[i].used = false;
}

void fx_add(int enemy, int x, int y)
{
    /*if (!spark)
        al_play_sample(sample_explode[between(0, 2)], 0.75, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);*/

    for (int i = 0; i < FX_N; i++)
    {
        if (fx[i].used)
            continue;

        fx[i].x = x;
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].enemy = enemy;
        fx[i].used = true;
        return;
    }
}

void fx_update()
{
    for (int i = 0; i < FX_N; i++)
    {
        if (!fx[i].used)
            continue;

        fx[i].frame++;

        if ((fx[i].enemy == 0 && (fx[i].frame == (ENEMY2_FX_FRAMES * 8)))
            || (fx[i].enemy == 1 && (fx[i].frame == (ENEMY4_FX_FRAMES * 8)))
            || (fx[i].enemy == 2 && (fx[i].frame == (ENEMY_BEFORE_RAZER_FRAMES * 8)))
            || (fx[i].enemy == 3 && (fx[i].frame == (ENEMY_RAZER_FRAMES * 8)))
            || (fx[i].enemy == 4 && (fx[i].frame == (ENEMY_AFTER_RAZER_FRAMES * 8)))
            )

            fx[i].used = false;
    }
}

void fx_draw()
{
    for (int i = 0; i < FX_N; i++)
    {
        if (!fx[i].used)
            continue;

        int frame_display = fx[i].frame / 8;

        ALLEGRO_BITMAP* bmp =
            (fx[i].enemy == 0) ? sprites.enemy2_bomb[frame_display] :
            (fx[i].enemy == 1) ? sprites.enemy4_bomb[frame_display] :
            (fx[i].enemy == 2) ? sprites.razer_before_fx :
            (fx[i].enemy == 3) ? sprites.razer_fx[frame_display] :
            (fx[i].enemy == 4) ? sprites.razer_after_fx :
            NULL; // 혹은 기본 폭발 이미지

        if (bmp) {
            int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);
            int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
            al_draw_bitmap(bmp, x, y, 0);
        }
    }
}