#pragma once
#include "Game.h"
#include "Enemy.h"


class Freeze : public Attack {
public:
	Freeze();
	~Freeze();
	void render() override;
	void update(std::list<SDL_Rect> enemies, int input[5]) override;
	int get_damage() override;
	void levelup() override;
	void add_pos();
	int xPos, yPos;
	SDL_Rect drect_;

	bool m_bSkilloff;
	bool freezeOn;
	void ClearPos() { pos_list.clear(); m_bSkilloff = true; };

private:
	float gen_timer, gen_cycle;
	SDL_Texture* texture_;
	SDL_Rect srect_;
	int damage;
	int alpha;
};