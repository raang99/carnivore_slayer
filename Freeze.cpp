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
	//level = 1;
	sound = Mix_LoadMUS("Resource/sound/IceAttack.mp3");
	if (sound == 0) {
		std::cout << "Mix_LoadWAV(\"Blop Sound.wav\"): " << Mix_GetError() << std::endl;
	}
}

Freeze::~Freeze() {
	SDL_DestroyTexture(texture_);
}

void Freeze::render() {
	if (level < 1)
		return;
	if (freezeOn) {
		float alpha = (gen_timer - (gen_cycle * 0.8)) / (gen_cycle - (gen_cycle * 0.8));
		SDL_SetTextureAlphaMod(texture_, static_cast<Uint8>(alpha * 255));
		SDL_RenderCopy(renderer, texture_, &srect_, &drect_);
	}
}

void Freeze::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;
	if (m_bSkilloff) {
		gen_timer -= 33;
		if (gen_timer < 0) {
			Mix_FadeInMusic(sound, 1, 2000);
			gen_timer = gen_cycle;
			freezeOn = true;
			add_pos();
			m_bSkilloff = false;
		}
	}

	if (freezeOn) {
		int duration = gen_cycle - gen_cycle * 0.8;
		if (gen_timer < gen_cycle*0.8)
			freezeOn = false;
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

void Freeze::levelup() {
	level += 1;
	if (level == 2) {
		gen_cycle *= 0.8;
	}
	else if (level == 3) {
		drect_.x -= 50;
		drect_.y -= 50;
		drect_.w += 100;
		drect_.h += 100;
	}
	else if (level == 4) {
		gen_cycle *= 0.8;
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