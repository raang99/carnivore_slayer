#include "Thunder.h"

Thunder::Thunder()
	:stateoff(true), thunderOn(false)
{
	s_rect = { 0,0,30,30 };
	d_rect = { 0,0,50,50 };
	gen_timer = 1000.0f;
	gen_cycle = gen_timer;
	gen_quantity = 1;
	damage = 100;
	
	skill_type = SkillType::Thunder;

	sound = Mix_LoadWAV("Resource/sound/ThunderAttacklong.wav");
	if (sound == 0) {
		std::cout << "Resource/sound/ThunderAttacklong.wav" << Mix_GetError() << std::endl;
	}
	// �̹��� ���Ϸκ��� �ؽ�ó ����
	SDL_Surface* surface = IMG_Load("Resource/effect/thunder.png");
	if (surface == nullptr) {
		std::cerr << "Failed to load image: " << "Resource/effect/thunder.png" << std::endl;
		return;
	}

	SDL_Texture* objectTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &width, &height);
	width /= 15;
	//level = 1;

}

Thunder::~Thunder() {
	effects.~EffectManager();
}

void Thunder::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (level < 1)
		return;
	
	gen_timer -= 33;
	if (gen_timer < 0) {
		gen_timer = gen_cycle;
		add_pos();
	}
	effects.update(input);
	
}

void Thunder::render() {
	if (level < 1)
		return;
	effects.render();
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

void Thunder::add_pos() {
	Mix_PlayChannel(-1, sound, 0);
	pos_list.remove(APos);
	d_rect.x = rand() % SCREEN_WIDTH;
	d_rect.y = rand() % SCREEN_HEIGHT;
	APos.posX = d_rect.x;
	APos.posY = d_rect.y ;
	APos.objectRect = d_rect;
	effects.add(1, d_rect.x - (width / 2)+15, d_rect.y - height + 100);
	pos_list.push_back(APos);
}


int Thunder::get_damage() {
	//������ �ֱ�
	return damage;
}
