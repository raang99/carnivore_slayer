#include "BasicAttack.h"
#include "Enemy.h"

BasicAttack::BasicAttack() {
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
}

BasicAttack::~BasicAttack() {
	SDL_DestroyTexture(texture_);
}

void BasicAttack::render() {
	for (auto& i : pos_list) {
		i.objectRect = { static_cast<int>(i.posX), static_cast<int>(i.posY), 40, 20 };
		SDL_RenderCopyEx(renderer, texture_, nullptr , &i.objectRect, i.angle, nullptr, SDL_FLIP_HORIZONTAL);
	}
}
bool isOut(Pos b) {
	if (b.posX < 0 || b.posY < 0 ||
		b.posX > SCREEN_WIDTH || b.posY > SCREEN_HEIGHT) {
		return true;
	}
	else
		return false;
}
void BasicAttack::update(std::list<SDL_Rect> enemies) {
	gen_timer -= 33;
	if (gen_timer < 0) {
		gen_timer = gen_cycle;
		for (int i = 0; i < gen_quantity; i++) {
			add_pos(enemies);
		}
	}
	for (auto &i : pos_list) {
		i.posX -= SPEED * i.cosAngle;
		i.posY -= SPEED * i.sinAngle;
	}
	pos_list.remove_if(isOut);
}



void BasicAttack::add_pos(std::list<SDL_Rect> enemies) {
	//가장 가까운 적 탐색
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

int BasicAttack::get_damage() {
	return damage;
}