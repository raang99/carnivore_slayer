#include "Thunder.h"

Thunder::Thunder()
	:stateoff(true)
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/thunder.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/b.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	s_rect = { 0,0,30,30 };
	d_rect = { 0,0,30,30 };
	s_cen = { 15,15 };
	gen_timer = 1000.0f;
	gen_cycle = 1000.0f;
	gen_quantity = 1;
	damage = 20;
	

	skill_type = SkillType::Thunder;


}

Thunder::~Thunder() {
	SDL_DestroyTexture(texture_);
}

void Thunder::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (stateoff) {
		gen_timer -= 250;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			add_pos();
			stateoff = false;
		}
	}
}

void Thunder::render() {
	SDL_RenderCopy(renderer, texture_, &s_rect, &d_rect);
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