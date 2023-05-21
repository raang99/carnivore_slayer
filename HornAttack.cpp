#include "HornAttack.h"

HornAttack::HornAttack() 
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/horn.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/horn.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	s_rect = {0,0,20,100};
	s_cen = {10,0};
	gen_cycle = 3000.0f;
	gen_timer = gen_cycle;
	gen_quantity = 1;
	damage = 20;
	skill_type = SkillType::HornAttack;
	level = 1;
}

HornAttack::~HornAttack() {
	SDL_DestroyTexture(texture_);
}

void HornAttack::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;

	if (m_bSkilloff) {
		gen_timer -= 33;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			run_flag = true;
			add_pos(enemies);
			m_bSkilloff = false;
		}
	}

	if (run_flag) {
		if (gen_timer < gen_cycle * 0.8) {
			run_flag = false;
		}
	}

	for (auto& i : pos_list) {
		if (input[UP]) {
			i.posY += speed;
		}
		if (input[DOWN]) {
			i.posY -= speed;
		}
		if (input[LEFT]) {
			i.posX += speed;
		}
		if (input[RIGHT]) {
			i.posX -= speed;
		}
	}
}

void HornAttack::render() {
	if (level < 1)
		return;
	for (auto& i : pos_list) {
		i.objectRect = { static_cast<int>(i.posX), static_cast<int>(i.posY), 20, 100 };
		SDL_RenderCopyEx(renderer, texture_, &s_rect, &i.objectRect, i.angle, &s_cen, SDL_FLIP_VERTICAL);
	}
}
void HornAttack::levelup() {
	level += 1;
}
void HornAttack::add_pos(std::list<SDL_Rect> enemies) {
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
	des.posX = min_dx;
	des.posY = min_dy;
	des.angle = std::atan2(dy, dx);
	pos.cosAngle = min_dx / min_distance;
	pos.sinAngle = min_dy / min_distance;
	pos.angle = std::atan2(dy, dx) * 180.0f / M_PI;
	pos_list.push_back(pos);
}


int HornAttack::get_damage() {
	//데미지 주기
	return damage;
}
