#pragma once
#include "Game.h"
#include "Enemy.h"

const float SPEED = 10.0f;

class BasicAttack : public Attack{
public:
	BasicAttack();
	~BasicAttack();
	void render() override;
	void update(std::list<SDL_Rect> enemies) override;
	int get_damage() override;
	void add_pos(std::list<SDL_Rect> enemies);
private:
	double gen_timer, gen_cycle;
	int gen_quantity;
	SDL_Texture *texture_;
	int damage;
};