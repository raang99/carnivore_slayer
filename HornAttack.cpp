#include "HornAttack.h"

HornAttack::HornAttack() {
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/horn.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/horn.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	srect_ = { 96, 58, 130, 104 };
	drect_ = { 0, 0, 130, 104 };
	gen_timer = 2000.0f;
	gen_cycle = gen_timer;
	damage = 10;
	dir = UP;

	skill_type = SkillType::HornAttack;
}

HornAttack::~HornAttack() {
	SDL_DestroyTexture(texture_);
}

void HornAttack::render() {
	if (level < 1)
		return;
	for (auto& i : pos_list) {
		i.objectRect = { static_cast<int>(i.posX), static_cast<int>(i.posY), drect_.w, drect_.h };
		SDL_RenderCopyEx(renderer, texture_, &srect_, &i.objectRect, i.angle, nullptr, SDL_FLIP_NONE);
	}
}

bool isOut3(Pos& b) {
	if (b.posX < 150 || b.posY < 100 ||
		b.posX > SCREEN_WIDTH - 280 || b.posY > SCREEN_HEIGHT - 204) {
		return true;
	}
	else
		return false;
}

void HornAttack::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;

	set_dir(input);

	gen_timer -= 33.f;
	if (gen_timer < 0) {
		gen_timer = gen_cycle;
		add_pos(enemies);
	}

	for (auto& i : pos_list) {
		i.posX -= SPEED_HORN * i.cosAngle;
		i.posY -= SPEED_HORN * i.sinAngle;
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

	pos_list.remove_if(isOut3);
}

void HornAttack::add_pos(std::list<SDL_Rect> enemies) {
	float min_distance = 1234123124.0f;
	Pos pos;
	pos.posX = SCREEN_CENTER_X - 20;
	pos.posY = SCREEN_CENTER_Y - 10;
	
	if (dir == UP) {
		pos.angle = 270;
		pos.cosAngle = 0;
		pos.sinAngle = 1;
	}

	else if (dir == DOWN) {
		pos.angle = 90;
		pos.cosAngle = 0;
		pos.sinAngle = -1;
	}

	else if (dir == LEFT) {
		pos.angle = 180;
		pos.cosAngle = 1;
		pos.sinAngle = 0;
	}

	else if (dir == RIGHT) {
		pos.angle = 0;
		pos.cosAngle = -1;
		pos.sinAngle = 0;
	}

	pos_list.push_back(pos);
}

int HornAttack::get_damage() {
	return damage;
}

void HornAttack::levelup() {
	level += 1;
	if (level == 2) {
		gen_cycle *= 0.8;
	}
	else if (level == 3) {
		drect_.w += 60;
		drect_.h += 60;
	}
	else if (level == 4) {
		gen_cycle *= 0.7;
	}
}

void HornAttack::set_dir(int input[5]) {
	if (input[UP] && !input[DOWN] && !input[LEFT] && !input[RIGHT])
		dir = UP;
	else if (!input[UP] && input[DOWN] && !input[LEFT] && !input[RIGHT])
		dir = DOWN;
	else if (!input[UP] && !input[DOWN] && input[LEFT] && !input[RIGHT])
		dir = LEFT;
	else if (!input[UP] && !input[DOWN] && !input[LEFT] && input[RIGHT])
		dir = RIGHT;
}