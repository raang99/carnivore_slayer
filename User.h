#pragma once
#include "Game.h"
#include "Sprite.h"
#include "EffectManager.h"
class User {
public:
	User();
	~User();
	void render();
	void update(int input[5]);
	void add_exp();
	void sub_hp(int damage);
	double get_hit_delay();
	void reset_hit_delay();
	int xPos, yPos;
	SDL_Rect drect_;
	SDL_Rect hit_box;
	SDL_Rect search_rect;
	bool levelup_flag = false;
	void hp_max();
	void heal();
	void speed_up();
	void search();
	void growth();
private:
	void set_direct(int input[5]);
	Sprite* texture[4];
	Sprite* dead_effect;
	int direct;
	SDL_Rect srect_;
	float max_exp, cur_exp;
	float max_hp, cur_hp;
	double hit_delay = 100.0f;
	double heal_delay = 1000.0f;
	float heal_point = 1.0f;
	float exp = 10.0;
};