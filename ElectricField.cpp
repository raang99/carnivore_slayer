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
	drect_ = { 0, 0, 200, 200 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;
	yPos = drect_.y;

	gen_timer = 500.0f;
	gen_cycle = gen_timer;
	damage = 5;

	skill_type = SkillType::ElectricField;
	//level = 1;
}

ElectricField::~ElectricField() {
	SDL_DestroyTexture(texture_);
}

void ElectricField::render() {
	if (level < 1)
		return;
	SDL_RenderCopy(renderer, texture_, &srect_, &drect_);
}

void ElectricField::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;
	if (m_bSkilloff) { // 리스트에 전기장이 없으면 (안하면 혼자서 리스트 꽉 채움)
		gen_timer -= 33;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			add_pos();
			m_bSkilloff = false;
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

void ElectricField::levelup() {
	level += 1;
	if (level == 2) {
		drect_.x -= 30;
		drect_.y -= 30;
		drect_.w += 60;
		drect_.h += 60;
	}
	else if (level == 3) {
		damage += 10;
	}
	else if (level == 4) {
		gen_cycle *= 0.2;
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
