#include "game.h"

#define FX_N 128

FX fx[FX_N];
SPRITES sprites;

void fx_init()
{
    for (int i = 0; i < FX_N; i++)
        fx[i].used = false;
}

void fx_add(bool enemy, int x, int y)
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

        if ((!fx[i].enemy && (fx[i].frame == (ENEMY2_FX_FRAMES * 4)))
            || (fx[i].enemy && (fx[i].frame == (ENEMY4_FX_FRAMES * 4)))
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

        int frame_display = fx[i].frame / 4;
        ALLEGRO_BITMAP* bmp =
            fx[i].enemy
            ? sprites.enemy4_bomb[frame_display]
            : sprites.enemy2_bomb[frame_display]
            ;

        int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);
        int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
        al_draw_bitmap(bmp, x, y, 0);
    }
}