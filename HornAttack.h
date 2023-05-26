#pragma once
#include "Game.h"
#include "Enemy.h"

const float SPEED_HORN = 20.0f;

class HornAttack : public Attack {
public:
	HornAttack();
	~HornAttack();
	void render() override;
	void update(std::list<SDL_Rect> enemies, int input[5]) override;
	int get_damage() override;
	void levelup() override;
	void add_pos(std::list<SDL_Rect> enemies);
	SDL_Rect drect_;
private:
	double gen_timer, gen_cycle;
	SDL_Texture* texture_;
	SDL_Rect srect_;
	int damage;
	int dir;
	void set_dir(int input[5]);
};