#include "Thunder.h"

Thunder::Thunder()
	:stateoff(true), thunderOn(false)
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/thunder.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/thunder.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	s_rect = { 0,0,30,30 };
	d_rect = { 0,0,60,60 };
	gen_timer = 1000.0f;
	gen_cycle = gen_timer;
	gen_quantity = 1;
	damage = 20;
	
	skill_type = SkillType::Thunder;

	level = 1;
}

Thunder::~Thunder() {
	SDL_DestroyTexture(texture_);
}

void Thunder::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;
	if (stateoff) {
		gen_timer -= 33;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			thunderOn = true;
			add_pos(enemies);
			stateoff = false;
		}
	}

	if (thunderOn) {
		int duration = gen_cycle - gen_cycle * 0.8;
		if (gen_timer < gen_cycle * 0.8)
			thunderOn = false;
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

void Thunder::render() {
	if (level < 1)
		return;

	if (thunderOn) {
		float alpha = (gen_timer - (gen_cycle * 0.8)) / (gen_cycle - (gen_cycle * 0.8));
		SDL_SetTextureAlphaMod(texture_, static_cast<Uint8>(alpha * 255));
		SDL_RenderCopy(renderer, texture_, nullptr, &d_rect);
	}
}

void Thunder::levelup() {
	level += 1;
	if (level == 2) {
		gen_cycle *= 0.7;
	}
	else if (level == 3) {
		gen_cycle *= 0.7;
	}
	else if (level == 4) {
		gen_cycle *= 0.7;
	}
}

void Thunder::add_pos(std::list<SDL_Rect> enemies) {
	pos_list.remove(APos);
	std::list<SDL_Rect>::iterator itr;
	int i = 0;
	bool click = false;
	for (itr = enemies.begin(); itr != enemies.end(); itr++) {
		if (i == setRandom(enemies.size())) {
			if (itr->x > 0 && itr->x < SCREEN_WIDTH && itr->y > 0 && itr->y <SCREEN_HEIGHT) {
				d_rect.x = itr->x;
				d_rect.y = itr->y;
				APos.posX = d_rect.x;
				APos.posY = d_rect.y;
				APos.objectRect = d_rect;
				click = true;
				break;
			}
		}
		i++;
	}

	if (!click) {
		float min_distance = 1234123124.0f;
		float min_x = 1234123124.0f, min_y = 1234123124.0f;
		float dx = 0, dy = 0, distance = 0;
		for (auto& i : enemies) {
			dx = SCREEN_CENTER_X - i.x;
			dy = SCREEN_CENTER_Y - i.y;
			distance = std::sqrt(dx * dx + dy * dy);
			if (min_distance > distance) {
				min_distance = distance;
				min_x = i.x;
				min_y = i.y;
			}
		}
		APos.posX = min_x;
		APos.posY = min_y;
		APos.objectRect = d_rect;
	}

	pos_list.push_back(APos);
}


int Thunder::get_damage() {
	//데미지 주기
	return damage;
}


int setRandom(int a) {
	srand(time(NULL));
	return rand() % a;
}