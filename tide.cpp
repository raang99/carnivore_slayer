#include "Tide.h"
#include "Enemy.h"

Tide::Tide() {
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/td_ex.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/td_ex.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	srect_ = { 287, 43, 205, 513 };
	width = 200;
	height = 288;
	sprite = new Sprite(renderer, "Resource/effect/tide.png", 8, 200);
	gen_timer = 5000.0f;
	gen_cycle = gen_timer;
	damage = 5;
	//level = 1;
	skill_type = SkillType::Tide;
}

Tide::~Tide() {
	SDL_DestroyTexture(texture_);
}

void Tide::render() {
	if (level < 1)
		return;
	for (auto& i : pos_list) {
		i.objectRect = { static_cast<int>(i.posX), static_cast<int>(i.posY), width, height };
		/*SDL_RenderCopyEx(renderer, texture_, &srect_, &i.objectRect, i.angle, nullptr, SDL_FLIP_HORIZONTAL);*/
		sprite->RenderEx2(renderer, i.objectRect, i.angle);
	}
}

bool isOut2(Pos& b) {
	if (b.posX < -500 || b.posY < -500 ||
		b.posX > SCREEN_WIDTH + 500 || b.posY > SCREEN_HEIGHT + 500) {
		return true;
	}
	else
		return false;
}

void Tide::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;
	gen_timer -= 33.f;
	if (gen_timer < 0) {
		gen_timer = gen_cycle;
		add_pos(enemies);
	}

	sprite->Update();
	for (auto& i : pos_list) {
		i.posX -= SPEED_TIDE * i.cosAngle;
		i.posY -= SPEED_TIDE * i.sinAngle;
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
	pos_list.remove_if(isOut2);
}

void Tide::add_pos(std::list<SDL_Rect> enemies) {
	float min_distance = 1234123124.0f;
	Pos pos;
	pos.posX = SCREEN_CENTER_X - (width/2);
	pos.posY = SCREEN_CENTER_Y - (height/2);
	float min_dx = 1234123124.0f, min_dy = 1234123124.0f;
	float dx = 0.f, dy = 0.f, distance;
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
	pos.angle = std::atan2(min_dy, min_dx) * 180.0f / M_PI;

	pos_list.push_back(pos);
}

int Tide::get_damage() {
	return damage;
}

void Tide::levelup() {
	level += 1;
	if (level == 2) {
		gen_cycle *= 0.8;
	}
	else if (level == 3) {
		width += 100;
		height += 100;
	}
	else if (level == 4) {
		damage += 10;
	}
}