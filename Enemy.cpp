#include "Game.h"
#include "Enemy.h"

Enemy::Enemy(){
	posX_ = static_cast<float>(rand() % SCREEN_WIDTH);
	if (posX_ < 0) {
		posX_ -= 200;
	}
	else {
		posX_ += 200;
	}
	posY_ = static_cast<float>(rand() % SCREEN_HEIGHT);
	if (posY_ < 0) {
		posY_ -= 200;
	}
	else {
		posY_ += 200;
	}
	angle_ = 0.0f;
	SDL_Surface* surface = IMG_Load("Resource/enemy.png");
	if (surface == nullptr) {
		printf("이미지 파일 로드 실패: %s\n", IMG_GetError());
		exit(-1);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture_ == nullptr) {
		printf("텍스처 생성 실패: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_FreeSurface(surface);

}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture_);
}

void Enemy::render() {
	SDL_Rect objectRect = { static_cast<int>(posX_), static_cast<int>(posY_), OBJECT_SIZE, OBJECT_SIZE };
	SDL_RenderCopyEx(renderer, texture_, nullptr, &objectRect, angle_, nullptr, SDL_FLIP_NONE);
}

void Enemy::update(int input[5]) {
	// 삼각비를 이용한 이동
	float dx = SCREEN_CENTER_X - posX_;
	float dy = SCREEN_CENTER_Y - posY_;
	float distance = std::sqrt(dx * dx + dy * dy);
	float cosAngle = dx / distance;
	float sinAngle = dy / distance;
	posX_ += OBJECT_SPEED * cosAngle;
	posY_ += OBJECT_SPEED * sinAngle;

	if (input[UP]) {
		posY_ += 5;
	}
	if (input[DOWN]) {
		posY_ -= 5;
	}
	if (input[LEFT]) {
		posX_ += 5;
	}
	if (input[RIGHT]) {
		posX_ -= 5;
	}
	// 각도 계산
	angle_ = std::atan2(dy, dx) * 180.0f / M_PI;
}
SDL_Rect Enemy::get_drect() {
	SDL_Rect objectRect = { static_cast<int>(posX_), static_cast<int>(posY_), OBJECT_SIZE, OBJECT_SIZE };
	return objectRect;
}
int Enemy::get_hp() {
	return hp_;
}
void Enemy::set_hp(int hp) {
	hp_ = hp;
}
