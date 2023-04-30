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
private:
	SDL_Texture* texture_;
	float angle_;
	int hp_ = 20;
};