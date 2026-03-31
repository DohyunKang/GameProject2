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

void fx_update() {
    for (int i = 0; i < FX_N; i++) {
        if (!fx[i].used) continue;
        fx[i].frame++;

        if ((fx[i].enemy == 0 && (fx[i].frame >= (ENEMY2_FX_FRAMES * 8)))
            || (fx[i].enemy == 1 && (fx[i].frame >= (ENEMY4_FX_FRAMES * 8)))
            || (fx[i].enemy == 2 && (fx[i].frame >= 50)) // 경고 50프레임
            || (fx[i].enemy == 3 && (fx[i].frame >= 24)) // 발사 준비 24프레임
            || (fx[i].enemy == 4 && (fx[i].frame >= 24)) // 잔상 24프레임
            )

            fx[i].used = false;
    }
}

void fx_draw() {
    for (int i = 0; i < FX_N; i++) {
        if (!fx[i].used) continue;

        // fx 2 (경고) 일 때, 5프레임 주기로 깜빡이게 만듦
        if (fx[i].enemy == 2 && ((fx[i].frame / 5) % 2 == 0))
            continue;

        int frame_display = fx[i].frame / 8;
        if (fx[i].enemy == 3 && frame_display > 2) frame_display = 2;

        ALLEGRO_BITMAP* bmp =
            (fx[i].enemy == 0) ? sprites.enemy2_bomb[frame_display] :
            (fx[i].enemy == 1) ? sprites.enemy4_bomb[frame_display] :
            (fx[i].enemy == 2) ? sprites.razer_before_fx :
            (fx[i].enemy == 3) ? sprites.razer_fx[frame_display] :
            (fx[i].enemy == 4) ? sprites.razer_after_fx :
            NULL; 

        if (bmp) {
            int x;
            int bmp_w = al_get_bitmap_width(bmp);
            int bmp_h = al_get_bitmap_height(bmp);

            if (fx[i].enemy > 1) {
                x = 200; // 레이저는 고정 x 좌표에서 발사
            }
            else {
                x = fx[i].x - (bmp_w / 2);
            }
            int y = fx[i].y - (bmp_h / 2);

            if (fx[i].enemy > 1) {
                // 레이저 이미지 스케일 조정 (필요시 ENEMY5_W 등 상수값 사용)
                al_draw_scaled_bitmap(bmp, 0, 0, bmp_w, bmp_h, x, y, 800, ENEMY5_W, 0);
            }
            else {
                al_draw_bitmap(bmp, x, y, 0);
            }
        }
    }
}