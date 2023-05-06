#pragma once
#include "Game.h"
#include "Enemy.h"

class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();
	void render();
	void update(int input[5], std::list<Attack*> *attack, std::list<Exp*>* exp_list);
	std::list<SDL_Rect> get_drect_list();

private:
	std::list<Enemy*> list;
	std::list<Exp*> exp_list;
	double gen_timer, gen_cycle;
	int gen_quantity;
};

bool isDead(Enemy* e);
bool isHitted(Enemy* e, std::list<Pos>* pos_list);
bool isOverlap(SDL_Rect rect1, SDL_Rect rect2);