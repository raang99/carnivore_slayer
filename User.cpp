#include "Game.h"
#include "User.h"

User::User() {
	srect_ = { 403, 443, 200, 130 };
	drect_ = { 0, 0, 64, 64 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;//나중에 중앙 정렬할 수 있게 수정
	yPos = drect_.y;
	max_exp = 100;
	cur_exp = 0;
	max_hp = 200;
	cur_hp = max_hp;
	texture[UP] = new Sprite(renderer, "Resource/user/up.png", 10, 200);
	texture[DOWN] = new Sprite(renderer, "Resource/user/down.png", 10, 200);
	texture[LEFT] = new Sprite(renderer, "Resource/user/left.png", 12, 200);
	texture[RIGHT] = new Sprite(renderer, "Resource/user/right.png", 12, 200);
	direct = DOWN;
}

User::~User() {
}

void User::render() {
	texture[direct]->Render(renderer, drect_.x, drect_.y);
	//	Bright Yellow - exp bar
	{
		int point = static_cast<int>((cur_exp / max_exp) * 100.0);
		SDL_SetRenderDrawColor(renderer, 255, 234, 0, 255);
		SDL_Rect exp_rect = { drect_.x - 16, drect_.y - 20, point, 5 };
		SDL_RenderFillRect(renderer, &exp_rect);
	}
	// Blood Red - hp bar
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect hp_rect = { drect_.x - 16, drect_.y + 70, 100, 5 };
		SDL_RenderFillRect(renderer, &hp_rect);
		int point = static_cast<int>((cur_hp / max_hp) * 100.0);
		SDL_SetRenderDrawColor(renderer, 136, 8, 8, 255);
		hp_rect.w = point;
		SDL_RenderFillRect(renderer, &hp_rect);
	}
	hit_delay -= 22;
}

void User::update(int input[5]) {
	set_direct(input);
	for(int i = 0; i < 4; i++)
		texture[i]->Update();

	if (input[UP]) {
		yPos -= 5;
	}
	if (input[DOWN]) {
		yPos += 5;
	}
	if (input[LEFT]) {
		xPos -= 5;
	}
	if (input[RIGHT]) {
		xPos += 5;
	}
	//level up
	if (cur_exp >= max_exp) {
		cur_exp = 0;
		max_exp *= 1.2;
	}
}

void User::add_exp(int exp) {
	cur_exp += exp;
}

void User::sub_hp(int damage) {
	cur_hp -= damage;
}

double User::get_hit_delay() {
	return hit_delay;
}
void User::reset_hit_delay() {
	hit_delay = 100.0f;
}

void User::set_direct(int input[5]) {
	if (input[UP] && !input[DOWN] && !input[LEFT] && !input[RIGHT])
		direct = UP;
	else if (!input[UP] && input[DOWN] && !input[LEFT] && !input[RIGHT])
		direct = DOWN;
	else if (!input[UP] && !input[DOWN] && input[LEFT] && !input[RIGHT])
		direct = LEFT;
	else if (!input[UP] && !input[DOWN] && !input[LEFT] && input[RIGHT])
		direct = RIGHT;
}