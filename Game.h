#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include <list>
#include <cmath>
#include <ctime>
#include <string>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <atlstr.h>
#include <vector>

#define UP 0x0
#define DOWN 0x1
#define LEFT 0x2
#define RIGHT 0x3
#define SHOT 0x4
#define KEYUP 0xff

#define INTRO 0x0
#define STAGE1 0x1
#define END 0x2

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float SCREEN_CENTER_X = SCREEN_WIDTH / 2.0f;
const float SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0f;


void InitGame();

extern bool g_running;
extern SDL_Renderer* renderer;
extern int cur_phase;
extern int speed;

struct Pos {
	float posX, posY;
	float angle, cosAngle, sinAngle;
	SDL_Rect objectRect;
	bool operator==(const Pos& other) const {
		return posX == other.posX && posY == other.posY &&
			angle == other.angle && cosAngle == other.cosAngle && sinAngle == other.sinAngle;
	}
};

class PhaseInterface
{
public:
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

enum class SkillType {
	Default,
	BasicAttack,
	HornAttack,
	ElectricField,
	Thunder,
	Freeze,
	Tide
};

class Attack
{
public:
	Attack() {};
	~Attack() {};
	virtual void update(std::list<SDL_Rect> enemies, int input[5]) = 0;
	virtual void render() = 0;
	virtual int get_damage() = 0;
	virtual void levelup() = 0;
	int level = 0;
	std::list<Pos> pos_list;
	SkillType skill_type = SkillType::Default;
};
