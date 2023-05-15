#include "Freeze.h"

Freeze::Freeze()
	: m_bSkilloff(true), freezeOn(false)
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/fz_ex.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/ef_ex.png" << "(open error)" << std::endl;
		exit(0);
	}
	SDL_SetColorKey(sheet_surface, SDL_TRUE, SDL_MapRGB(sheet_surface->format, 0, 0, 0));
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	srect_ = { 366, 80, 373, 353 };
	drect_ = { 0, 0, 400, 400 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;
	yPos = drect_.y;

	gen_timer = 5000.0f;
	gen_cycle = 5000.0f;
	damage = 10;

	skill_type = SkillType::Freeze;
}

Freeze::~Freeze() {
	SDL_DestroyTexture(texture_);
}

void Freeze::render() {
	if (freezeOn)
		SDL_RenderCopy(renderer, texture_, &srect_, &drect_);
}

void Freeze::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (m_bSkilloff) {
		gen_timer -= 20;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			freezeOn = true;
			add_pos();
			m_bSkilloff = false;
		}
	}

	if (freezeOn) {
		if (gen_timer < 4500)
			freezeOn = false;
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

void Freeze::add_pos() {
	Pos pos;
	pos.posX = SCREEN_CENTER_X;
	pos.posY = SCREEN_CENTER_Y;
	pos.objectRect = drect_;
	pos.cosAngle = 0.0f;
	pos.sinAngle = 0.0f;
	pos.angle = 0.0f;
	pos_list.push_back(pos);
}

int Freeze::get_damage() {
	return damage;
}