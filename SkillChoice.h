#pragma once
#include "Game.h"
#include "User.h"
#include "EnemyManager.h"
#include "Texture.h"
#include "TTF.h"
#include "BasicAttack.h"
#include "HornAttack.h"
#include "ElectricField.h"
#include "Freeze.h"
#include "Thunder.h"

#define HP_MAX 0x0
#define HEAL 0x1
#define SPEED 0x2
#define SEARCH 0x3
#define GROWTH 0x4
#define BASIC 0x5
#define HORN 0x6
#define ELECTRIC 0x7
#define FREEZE 0x8
#define THUNDER 0x9
#define TIDE 0xA

struct Button
{
	int x;
	int y;
	int width;
	int height;
};

const int BACK_WIDTH = 700;
const int BACK_HEIGHT = 500;
const int BACK_X = 50;
const int BACK_Y = 70;
const int BUTTON_COUNT = 3;
const int BUTTON_PADDING = 40;
const int EXPLAIN_PADDING = 50;
const int BUTTON_WIDTH = BACK_WIDTH/3;
const int BUTTON_HEIGHT = BACK_HEIGHT;
const int TEXT_Y = 250;
const int SKILL_COUNT = 11;
class SkillChoice {
public:
	SkillChoice();
	~SkillChoice();
	void handleEvents(User* user, std::vector<Attack*>* attack);
	void render(User* user, std::vector<Attack*>* attack);
	void set_rand_choice(std::vector<Attack*> attack);
private:
	int get_skill_level(int skill, std::vector<Attack*> attack);
	wchar_t SKILL_EXPLAIN[SKILL_COUNT][4][100];
	wchar_t SKILL_LABEL[SKILL_COUNT][50] = { L"강인함", 
													L"재생의 바람", 
													L"기민한 발놀림", 
													L"탐색", 
													L"과잉 성장",
													L"매직 미사일",
													L"뿔치기",
													L"전자기장",
													L"빙결",
													L"낙뢰",
													L"파도"};
	TTF_Font* font_, *explain_font;
	Texture* images[SKILL_COUNT];
	Button buttons_[BUTTON_COUNT];
	bool reset_flag;
	int choices[3];
	void* skill_list[SKILL_COUNT];
};