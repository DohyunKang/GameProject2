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

    if (!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return 1;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    if (!timer)
    {
        printf("couldn't initialize timer\n");
        return 1;
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (!queue)
    {
        printf("couldn't initialize queue\n");
        return 1;
    }

    
    ALLEGRO_DISPLAY* disp = al_create_display(1200, 900);
    if (!disp)
    {
        printf("couldn't initialize display\n");
        return 1;
    }

    al_init_font_addon();

    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font)
    {
        printf("couldn't initialize font\n");
        return 1;
    }
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.png", n);
    ALLEGRO_BITMAP* image = al_load_bitmap(filename);


    if (!image) {
        printf("couldn't load images : %s\n",filename);
        return 1;
    }

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;
        int screen_width = 1200;
        int screen_height = 900;
        if (redraw && al_is_event_queue_empty(queue))
        {
            float img_width = al_get_bitmap_width(image);
            float img_height = al_get_bitmap_height(image);
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_scaled_bitmap(image,0, 0, img_width, img_height, 0, 0, screen_width, screen_height,0);
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_bitmap(image);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}

int main() {
    background(0);
    background(1);
    background(2);
    background(3);
    background(4);
    background(5);
}
#endif