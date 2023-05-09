#include "ElectricField.h"

ElectricField::ElectricField()
	: m_bSkilloff(true)
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/ef_ex.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/ef_ex.png" << "(open error)" << std::endl;
		exit(0);
	}
	SDL_SetColorKey(sheet_surface, SDL_TRUE, SDL_MapRGB(sheet_surface->format, 0, 0, 0));
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	srect_ = { 214, 99, 439, 394 };
	drect_ = { 0, 0, 200, 100 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;
	yPos = drect_.y;

	gen_timer = 1000.0f;
	gen_cycle = 1000.0f;
	damage = 5;

	skill_type = SkillType::ElectricField;
}

ElectricField::~ElectricField() {
	SDL_DestroyTexture(texture_);
}

void ElectricField::render() {
	SDL_RenderCopy(renderer, texture_, &srect_, &drect_);
}

void ElectricField::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (m_bSkilloff) { // 리스트에 전기장이 없으면 (안하면 혼자서 리스트 꽉 채움)
		gen_timer -= 250;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			add_pos();
			m_bSkilloff = false;
		}
	}

	for (auto& i : pos_list) {
		if (input[UP]) {
			i.posY += 5;
		}
		if (input[DOWN]) {
			i.posY -= 5;
		}
		if (input[LEFT]) {
			i.posX += 5;
		}
		if (input[RIGHT]) {
			i.posX -= 5;
		}
	}
}

void ElectricField::add_pos() {
	Pos pos;
	pos.posX = SCREEN_CENTER_X;
	pos.posY = SCREEN_CENTER_Y;
	pos.objectRect = drect_;
	pos.cosAngle = 0.0f;
	pos.sinAngle = 0.0f;
	pos.angle = 0.0f;
	pos_list.push_back(pos);
}

int ElectricField::get_damage() {
	return damage;
}