#pragma once
#include "Game.h"
#include "Sprite.h"
#include "Freeze.h"
const int OBJECT_WIDTH = 128;
const int OBJECT_HEIGHT = 40;
const float OBJECT_SPEED = 2.0f;

class Enemy {
public:
	Enemy();
	Enemy(bool bossflag);
	~Enemy();
	void render();
	void update(int input[5]);
	SDL_Rect get_drect();
	int get_hp();
	void set_hp(int hp);
	float posX_, posY_;
	bool isFrozen;
	bool isTideAttacked;
	bool flag;
	bool isThrusted;
	bool isHit;
private:
	int ani_speed = 80;
	float angle_;
	float hp_ = 20;
	float unfreeze_timer = 3000.f;
	float attacked_timer = 2000.f;
	float hit_timer = 250.f;
	const int left = 0;
	const int right = 1;
	Sprite* texture[2];
	int direct;
	bool is_boss = false;
	const int USER_PADDING = 300;
};

class Exp {
public:
	Exp(int x, int y);
	~Exp();
	void render();
	void update(int input[5]);
	SDL_Rect get_drect();
	int posX_, posY_;
private:
	SDL_Texture* texture_;
	
};
