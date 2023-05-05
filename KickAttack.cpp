#include "KickAttack.h"

KickAttack::KickAttack() {
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/b.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/b.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	gen_timer = 1000.0f;
	gen_cycle = 1000.0f;
	gen_quantity = 1;
	damage = 20;
	pic_time = 1000.0f;
}

KickAttack::~KickAttack() {
	SDL_DestroyTexture(texture_);
}

void KickAttack::update(std::list<SDL_Rect> enemies) {

}

void KickAttack::render() {

}

void KickAttack::add_pos(std::list<SDL_Rect> enemies) {
	float min_distance = 1234123124.0f;
	Pos pos;
	pos.posX = SCREEN_CENTER_X;
	pos.posY = SCREEN_CENTER_Y;
	float min_dx, min_dy;
	float dx, dy, distance;
	for (auto& i : enemies) {
		dx = SCREEN_CENTER_X - i.x;
		dy = SCREEN_CENTER_Y - i.y;
		distance = std::sqrt(dx * dx + dy * dy);
		if (min_distance > distance) {
			min_distance = distance;
			min_dx = dx;
			min_dy = dy;
		}
	}
	pos.cosAngle = min_dx / min_distance;
	pos.sinAngle = min_dy / min_distance;
	pos.angle = std::atan2(dy, dx) * 180.0f / M_PI;
	pos_list.push_back(pos);
}

int KickAttack::get_damage() {

}

void KickAttack::collider(std::list<SDL_Rect> enemies) {

}