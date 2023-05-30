#pragma once
#include "Game.h"
#include "Enemy.h"
#include "ElectricField.h"
#include "thunder.h"
#include "Freeze.h"
#include "HornAttack.h"
#include "BasicAttack.h"
#include "Sprite.h"
#include "EffectManager.h"
class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();
	void render();
	void update(int input[5], std::vector<Attack*> *attack, std::list<Exp*>* exp_list, bool cheat_on);
	void add_boss();
	void set_cycle(double cycle);
	std::list<SDL_Rect> get_drect_list();

private:
	std::list<Enemy*> list;
	std::list<Exp*> exp_list;
	Enemy* boss = 0;
	EffectManager dead_enemies;
	Mix_Chunk* dead_sound;
	Mix_Music* electric_sound;
	double gen_timer, gen_cycle;
	double clear_timer = 1600;
	Sprite* boss_dead;
	int gen_quantity;
	bool isHitted(Enemy* e, Attack* Attack);
};

bool isDead(Enemy* e);
bool isOverlap(SDL_Rect rect1, SDL_Rect rect2);
bool isMultiattack(Attack* Attack);