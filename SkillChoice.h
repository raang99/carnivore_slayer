#pragma once
#include "Game.h"

struct Button
{
	int x;
	int y;
	int width;
	int height;
	std::string label;
};
const int BUTTON_COUNT = 3;
const int BUTTON_PADDING = 20;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;
const std::string BUTTON_LABELS[] = { "선택지 1", "선택지 2", "선택지 3" };
class SkillChoice {
public:
	SkillChoice();
	~SkillChoice();
	void handleEvents();
	void render();
private:
	TTF_Font* font_;
	Button buttons_[BUTTON_COUNT];
};