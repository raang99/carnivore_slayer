#include "Game.h"
#include "User.h"

User::User() {
	SDL_Surface *sheet_surface;
	const char* image_path = "Resource/plain.png";
	sheet_surface = IMG_Load(image_path);
	if (!sheet_surface) {
		std::cout << "image file " << image_path << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	srect_ = { 403, 443, 200, 130 };
	drect_ = { 0, 0, 100, 50 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;//나중에 중앙 정렬할 수 있게 수정
	yPos = drect_.y;
	max_exp = 100;
	cur_exp = 0;
	max_hp = 200;
	cur_hp = max_hp;
}

User::~User() {
	SDL_DestroyTexture(texture_);
}

void User::render() {
	SDL_RenderCopy(renderer, texture_, &srect_, &drect_);
	//	Bright Yellow - exp bar
	{
		int point = static_cast<int>((cur_exp / max_exp) * 100.0);
		SDL_SetRenderDrawColor(renderer, 255, 234, 0, 255);
		SDL_Rect exp_rect = { drect_.x, drect_.y - 20, point, 5 };
		SDL_RenderFillRect(renderer, &exp_rect);
	}
	// Blood Red - hp bar
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect hp_rect = { drect_.x, drect_.y + 50, 100, 5 };
		SDL_RenderFillRect(renderer, &hp_rect);
		int point = static_cast<int>((cur_hp / max_hp) * 100.0);
		SDL_SetRenderDrawColor(renderer, 136, 8, 8, 255);
		hp_rect.w = point;
		SDL_RenderFillRect(renderer, &hp_rect);
	}
	hit_delay -= 22;
}

void User::update(int input[5]) {
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