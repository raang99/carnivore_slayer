#pragma once
#include "Game.h"
#include "Enemy.h"
#include "ElectricField.h"
#include "thunder.h"
#include "Freeze.h"
#include "HornAttack.h"
#include "Sprite.h"
#include "EffectManager.h"
class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();
	void render();
	void update(int input[5], std::vector<Attack*> *attack, std::list<Exp*>* exp_list);
	std::list<SDL_Rect> get_drect_list();

private:
	std::list<Enemy*> list;
	std::list<Exp*> exp_list;
	EffectManager dead_enemies;
	double gen_timer, gen_cycle;
	int gen_quantity;
};

bool isDead(Enemy* e);
bool isHitted(Enemy* e, Attack* Attack);
bool isOverlap(SDL_Rect rect1, SDL_Rect rect2);
bool isMultiattack(Attack* Attack);