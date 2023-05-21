#include "Thunder.h"

Thunder::Thunder()
	:stateoff(true)
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/thunder.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/thunder.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	s_rect = { 0,0,30,30 };
	d_rect = { 0,0,30,30 };
	s_cen = { 15,15 };
	gen_timer = 1000.0f;
	gen_cycle = gen_timer;
	gen_quantity = 1;
	damage = 20;
	
	skill_type = SkillType::Thunder;

	level = 1;
}

Thunder::~Thunder() {
	SDL_DestroyTexture(texture_);
}

void Thunder::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;
	if (stateoff) {
		gen_timer -= 33;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			add_pos();
			stateoff = false;
		}
	}
}

void Thunder::render() {
	if (level < 1)
		return;
	/*float alpha = gen_timer / gen_cycle;
	printf("%f\n", alpha);
	SDL_SetTextureAlphaMod(texture_, static_cast<Uint8>(alpha * 255));*/
	SDL_RenderCopy(renderer, texture_, nullptr, &d_rect);
}

void Thunder::levelup() {
	level += 1;
	if (level == 2) {
		gen_cycle *= 0.7;
	}
	else if (level == 3) {
		gen_cycle *= 0.7;
	}
	else if (level == 4) {
		gen_cycle *= 0.7;
	}
}

void Thunder::add_pos() {
	pos_list.remove(APos);
	d_rect.x = setRandom(400);
	d_rect.y = setRandom2(300);
	APos.posX = d_rect.x;
	APos.posY = d_rect.y;
	APos.objectRect = d_rect;
	pos_list.push_back(APos);
}


int Thunder::get_damage() {
	//데미지 주기
	return damage;
}


double setRandom(int a) {
	double rnd = (rand() % a) + SCREEN_CENTER_X - (a/2);
	//printf("%f",rnd);
	return rnd;
}
double setRandom2(int a) {
	double rnd = (rand() % a) + SCREEN_CENTER_Y - (a / 2);
	//printf("%f", rnd);
	return rnd;
}