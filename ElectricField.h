#pragma once
#include "Game.h"
#include "Enemy.h"


class ElectricField : public Attack {
public:
	ElectricField();
	~ElectricField();
	void render() override;
	void update(std::list<SDL_Rect> enemies, int input[5]) override;
	int get_damage() override;
	void add_pos();
	int xPos, yPos;
	SDL_Rect drect_;

	bool m_bSkilloff;
	void ClearPos() { pos_list.clear(); m_bSkilloff = true; };

private:
	double gen_timer, gen_cycle;
	SDL_Texture* texture_;
	SDL_Rect srect_;
	int damage;
};