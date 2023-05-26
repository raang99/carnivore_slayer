#pragma once
#include "Game.h"
#include "Enemy.h"
#include "EffectManager.h"


class Thunder : public Attack {
public:
	Thunder();
	~Thunder();
	void render()override;
	void update(std::list<SDL_Rect> enemies, int input[5])override;
	int get_damage()override;
	void levelup() override;
	void add_pos(std::list<SDL_Rect> enemies);
	
	bool stateoff, thunderOn;
	void ClearPos() { pos_list.clear(); stateoff = true; };


private:
	float gen_timer, gen_cycle;
	int gen_quantity;
	SDL_Rect s_rect , d_rect;
	int damage;
	Pos APos;
	int width, height;
	EffectManager effects;
	Mix_Chunk* sound;
};
int setRandom(int a);