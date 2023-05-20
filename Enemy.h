#pragma once
#include "Game.h"
const int OBJECT_SIZE = 40;
const float OBJECT_SPEED = 2.0f;


class Enemy {
public:
	Enemy();
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
	SDL_Texture* texture_;
	float angle_;
	int hp_ = 20;
	float unfreeze_timer = 3000.f;
	float attacked_timer = 2000.f;
	float hit_timer = 250.f;
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