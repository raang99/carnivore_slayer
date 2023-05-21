#include "EffectManager.h"

EffectManager::EffectManager() {
	effects[0] = "Resource/enemy/dead.png";
}
EffectManager::~EffectManager() {
	for (auto& i : effect_list) {
		i.effect->~Sprite();
	}
}

void EffectManager::render() {
	for (auto& i : effect_list) {
		i.effect->Render(renderer, i.x, i.y);
	}
}

void EffectManager::update(int input[5]) {
	for (auto& i : effect_list) {
		i.effect->Update();
		if (input[UP]) {
			i.y += speed;
		}
		if (input[DOWN]) {
			i.y -= speed;
		}
		if (input[LEFT]) {
			i.x += speed;
		}
		if (input[RIGHT]) {
			i.x -= speed;
		}
	}
	effect_list.remove_if(isEnd);
}

void EffectManager::add(int num,int x, int y) {
	effect tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.effect = new Sprite(renderer, "Resource/enemy/dead.png", 8, 200);
	effect_list.push_back(tmp);
}
bool isEnd(effect e) {
	if (e.effect->currentFrame_ >= e.effect->frameCount_-1) {
		e.effect->~Sprite();
		return true;
	}
	else
		return false;
}