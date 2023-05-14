#pragma once
#include "Game.h"
#include "Sprite.h"

class User {
public:
	User();
	~User();
	void render();
	void update(int input[5]);
	void add_exp(int exp);
	void sub_hp(int damage);
	double get_hit_delay();
	void reset_hit_delay();
	int xPos, yPos;
	SDL_Rect drect_;
private:
	void set_direct(int input[5]);
	Sprite* texture[4];
	int direct;
	SDL_Rect srect_;
	float max_exp, cur_exp;
	float max_hp, cur_hp;
	double hit_delay = 100.0f;
};