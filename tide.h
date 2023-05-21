#pragma once
#include "Game.h"
#include "Enemy.h"

const float SPEED_TIDE = 10.0f;

class Tide : public Attack {
public:
	Tide();
	~Tide();
	void render() override;
	void update(std::list<SDL_Rect> enemies, int input[5]) override;
	int get_damage() override;
	void levelup() override;
	void add_pos(std::list<SDL_Rect> enemies);
private:
	double gen_timer, gen_cycle;
	SDL_Texture* texture_;
	SDL_Rect srect_;
	int damage;
};