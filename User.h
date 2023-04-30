#pragma once
#include "Game.h"

class User {
public:
	User();
	~User();
	void render();
	void update(int input[5]);
	int xPos, yPos;
	SDL_Rect drect_;
private:
	SDL_Texture* texture_;
	SDL_Rect srect_;
};