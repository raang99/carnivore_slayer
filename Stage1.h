#pragma once

#include "Game.h"
#include "Texture.h"
#include "TTF.h"
#include "User.h"
#include "Map.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "BasicAttack.h"
#include "ElectricField.h"
#include "Thunder.h"
#include "Freeze.h"
#include "Tide.h"
#include "SkillChoice.h"

#define MAX_X 800
#define MAX_Y 600
#define BULLET 3
#define TILE 80


class Stage1 : public PhaseInterface
{
public:
	Stage1();
	~Stage1();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
private:
	void user_hitted(std::list<SDL_Rect> enemy_drect_list);
	void set_enemyCycle();
	int input[5] = { 0 };
	int score_point = 0;
	User user_;
	Map map_;
	EnemyManager enemy;
	SkillChoice sk_ch;
	std::vector<Attack*> attack_list;
	std::list<Exp*> exp_list;
	Mix_Chunk* exp_sound;
	Mix_Chunk* user_sound;
	std::list<Sprite*> effect_list;
	SDL_Color white = { 255, 255, 255, 0 };
	bool is_shot = false;
	int num_rows = MAX_Y / TILE; // 행의 개수
	int num_cols = MAX_X / TILE; // 열의 개수
	// 흘러간 시간 기록
	TTF* time;
	double g_elapsed_time_ms;
	bool boss_flag = true;
	Mix_Music* bg_sound;
	float boss_time;
	bool cheat_on;
};