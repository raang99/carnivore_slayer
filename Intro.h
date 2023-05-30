#pragma once
#include "Game.h"
#include "Texture.h"
#define MAX_X 800
#define MAX_Y 600
#define BULLET 3
#define TILE 80
class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
private:
	Texture *start_button;
	Texture* background[13];
	int cnt;
	Mix_Music* bg_sound;
	bool sound_started = false;
};