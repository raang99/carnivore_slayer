#pragma once
#include "Game.h"
#include "Texture.h"
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
	Texture* button, * background;
	Texture* back_win;
	Mix_Music* bg_sound_happy;
	Mix_Music* bg_sound_sad;
	bool sound_started = false;
};