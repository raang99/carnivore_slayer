#pragma once

#include "Game.h"
#include "Enemy.h"
#include <math.h>

class HornAttack : public Attack {
public:
	HornAttack();
	~HornAttack();
	void render()override;
	void update(std::list<SDL_Rect> enemies, int input[5])override;
	int get_damage()override;
	void levelup() override;
	void add_pos(std::list<SDL_Rect> enemies);

	bool m_bSkilloff;
	bool run_flag;
	void ClearPos() { pos_list.clear(); m_bSkilloff = true; };


private:
	double gen_timer, gen_cycle,duration_time,duration_cycle, length_h , length_w;
	int gen_quantity;
	SDL_Texture* texture_;
	SDL_Rect s_rect;
	SDL_Point s_cen;
	int damage;
	Pos des;
};
