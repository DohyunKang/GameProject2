#include "game.h"

void init_pi() 
{
	p.x = BUFFER_W / 2;
	p.y = BUFFER_H - 50; 
	p.hp = 3; p.inv_timer = 0;
	p.barrier = false; 
	p.barrier_timer = 0;
	frames = 1;

	for (int i = 0; i < MAX_ITEMS; i++) 
		it[i].active = false;
}

void player_update()
{
	//시작 상태
	if (state != STATE_PLAYING)
		return;

	//frames++;

	if (p.inv_timer > 0)
		p.inv_timer--;
	if (p.barrier && --p.barrier_timer <= 0)
		p.barrier = false;

	//피격 시 플레이어 상태
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!en[i].active)
			continue;

		if (en[i].active && p.inv_timer == 0 && 
			collide((int)p.x, (int)p.y, (int)p.x + PLAYER_W, (int)p.y + PLAYER_H, 
				(int)en[i].x, (int)en[i].y, (int)en[i].x + ENEMY_W, (int)en[i].y + ENEMY_H))
		{
			if (p.barrier)
			{
				p.barrier = false;
				p.barrier_timer = 0;
				//p.inv_timer = 60;
			}
			else
				p.hp--;

			p.inv_timer = 120;
			en[i].active = false;

			if (p.hp <= 0)
			{
				if (snd_die)
					al_play_sample(snd_die, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				state = (mode == MODE_CHALLENGE) ? STATE_INPUT_NAME : STATE_GAMEOVER;
			}
			else if (snd_hit)
				al_play_sample(snd_hit, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		//아이템 먹은 상태
		for (int i = 0; i < MAX_ITEMS; i++)
		{
			if (!it[i].active)
				continue;
			if (--it[i].timer <= 0)
			{
				it[i].active = false;
				continue;
			}
			if (collide((int)p.x, (int)p.y, (int)p.x + PLAYER_SIZE, (int)p.y + PLAYER_SIZE, 
				(int)it[i].x, (int)it[i].y, (int)it[i].x + ITEM_SIZE, (int)it[i].y + ITEM_SIZE))
			{
				it[i].active = false;
				if (it[i].type == ITEM_HEART && p.hp < 5)
					p.hp++;
				else if (it[i].type == ITEM_BARRIER)
				{
					p.barrier = true;
					p.barrier_timer = 300;
				}
			}
		}

		//플레이어 키보드 입력받고 움직임.
		if (key[ALLEGRO_KEY_UP] && p.y > 0)
			p.y -= 2.5;
		if (key[ALLEGRO_KEY_DOWN] && p.y < BUFFER_H)
			p.y += 2.5;
		if (key[ALLEGRO_KEY_LEFT] && p.x > 0)
			p.x -= 2.5;
		if (key[ALLEGRO_KEY_RIGHT] && p.x < BUFFER_W)
			p.x += 2.5;

		//테두리 밖으로 나가지 않게
		if (p.x < 0)
			p.x = 0;
		if (p.y < 0)
			p.y = 0;

		if (p.x > BUFFER_W)
			p.x = BUFFER_W;
		if (p.y > BUFFER_H)
			p.y = BUFFER_H;
	}
}

void item_update()
{
	if (state != STATE_PLAYING)
		return;

	//frames++;

	if (frames % 400 == 0)
	{
		for (int i = 0; i < MAX_ITEMS; i++) if (!it[i].active)
		{
			it[i].x = (float)(50 + rand() % (BUFFER_W - 100));
			it[i].y = (float)(50 + rand() % (BUFFER_H - 100));
			it[i].type = (ITEM_TYPE)(rand() % 4);
			it[i].timer = 300;
			it[i].active = true;

			break;
		}
	}
}

void player_draw()
{
	if (p.hp < 1)
		return;
	if (ship.respawn_timer)
		return;
	if (((ship.invincible_timer / 2) % 3) == 1)
		return;
	if (p.gender == 1)
	{
		if (key[ALLEGRO_KEY_RIGHT])
		{
			al_draw_bitmap(sprites.p, p.x, p.y, 0);
		}
		else if (key[ALLEGRO_KEY_LEFT])
		{
			al_draw_bitmap(sprites.p, p.x, p.y, 0);
		}
		
	}
	else if (p.gender == 2)
	{
		if (key[ALLEGRO_KEY_RIGHT])
		{
			if(p.)
			al_draw_bitmap(sprites.p, p.x, p.y, 0);
		}
		else if (key[ALLEGRO_KEY_LEFT])
		{
			al_draw_bitmap(sprites.p, p.x, p.y, 0);
		}
	}
	else if ()
	{

	}
}

void item_draw()
{

}