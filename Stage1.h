#pragma once

#include "Game.h"
#include "Texture.h"
#include "TTF.h"
#include "User.h"
#include "Map.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "BasicAttack.h"

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
	int input[5] = { 0 };
	int score_point = 0;
	std::string output;

	User user_;
	Map map_;
	EnemyManager enemy;
	std::list<Attack*> attack_list;
	Texture *plain, *background;
	Bullet *bullet;
	TTF* score_text_, * score_num_;
	SDL_Texture* sheet_texture, * b_texture, * back_texture, * score, * point_texture;
	TTF_Font* font2;
	SDL_Surface* tmp_surface;
	SDL_Rect srect, bsrect, back_srect;
	SDL_Rect drect, back_drect;
	SDL_Rect brect[BULLET];
	SDL_Rect score_rect;
	SDL_Color black = { 0, 0, 0, 0 };
	bool is_shot = false;
	int num_rows = MAX_Y / TILE; // 행의 개수
	int num_cols = MAX_X / TILE; // 열의 개수
	// 흘러간 시간 기록
	double g_elapsed_time_ms;
	Mix_Music* bg_sound;
	Mix_Chunk* gun_sound;

};