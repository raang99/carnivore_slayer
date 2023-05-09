#pragma once
#include "Game.h"
#include "Enemy.h"
#include <cstdlib>
#include <time.h>

class Thunder : public Attack {
public:
	Thunder();
	~Thunder();
	void render()override;
	void update(std::list<SDL_Rect> enemies, int input[5])override;
	int get_damage()override;
	//void add_pos(std::list<SDL_Rect> enemies);
	//bool collider(Pos e);

	bool stateoff;
	void ClearPos() { pos_list.clear(); stateoff = true; };


private:
	double gen_timer, gen_cycle;
	
	int gen_quantity;
	SDL_Texture* texture_;
	SDL_Rect s_rect , d_rect;
	SDL_Point s_cen;
	int damage;
	Pos des;
};
double setRandom(int a);
double setRandom2(int a);