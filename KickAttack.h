#pragma once

#include "Game.h"
#include "Enemy.h"

class KickAttack : public Attack {
public:
	KickAttack();
	~KickAttack();
	void render();
	void update(std::list<SDL_Rect> enemies);
	int get_damage();
	void add_pos(std::list<SDL_Rect> enemies);
	void collider(std::list<SDL_Rect> enemies);

private:
	double gen_timer, gen_cycle , pic_time;
	int gen_quantity;
	SDL_Texture* texture_;
	int damage;
	bool pic;

};