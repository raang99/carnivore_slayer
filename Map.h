#pragma once
#include "Game.h"

const int TILE_SIZE = 512;

class Map {
public:
	Map();
	~Map();
	void render();
	void setCamera(int x, int y);
private:
	SDL_Texture* texture_;
	int cameraX_, cameraY_;
};