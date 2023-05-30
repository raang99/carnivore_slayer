#pragma once
#include "Game.h"
#include "Texture.h"
#include "Sprite.h"
#define MAX_X 800
#define MAX_Y 600
#define BULLET 3
#define TILE 80
class Outro : public PhaseInterface
{
public:
	Outro();
	~Outro();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
private:
	Sprite* background;
	Texture* back_win[10];
	int win_cnt;
	Mix_Music* bg_sound_happy;
	Mix_Music* bg_sound_sad;
	bool sound_started = false;
};