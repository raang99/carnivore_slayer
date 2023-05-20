#include "Game.h"
#include "Enemy.h"
#include "Freeze.h"

Enemy::Enemy()
	:isFrozen(false)

{
	posX_ = static_cast<float>(rand() % SCREEN_WIDTH);
	if (posX_ < SCREEN_CENTER_X) {
		posX_ -= 200;
	}
	else {
		posX_ += 200;
	}
	posY_ = static_cast<float>(rand() % SCREEN_HEIGHT);
	if (posY_ < SCREEN_CENTER_Y) {
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
	
	if (isFrozen) {
		SDL_SetTextureColorMod(texture_, 100, 100, 255);
		SDL_SetTextureAlphaMod(texture_, 255);
	}
	else {
		SDL_SetTextureColorMod(texture_, 255, 255, 255);
		SDL_SetTextureAlphaMod(texture_, 255);
	}

	SDL_RenderCopyEx(renderer, texture_, nullptr, &objectRect, angle_, nullptr, SDL_FLIP_NONE);
}

void Enemy::update(int input[5]) {
	// 삼각비를 이용한 이동
	float dx = SCREEN_CENTER_X - posX_;
	float dy = SCREEN_CENTER_Y - posY_;
	float distance = std::sqrt(dx * dx + dy * dy);
	float cosAngle = dx / distance;
	float sinAngle = dy / distance;

	if (isFrozen) {
		unfreeze_timer -= 5.f;
		posX_ += OBJECT_SPEED * cosAngle * 0.3;
		posY_ += OBJECT_SPEED * sinAngle * 0.3;
		if (unfreeze_timer < 0.f) {
			isFrozen = false;
			unfreeze_timer = 500.f;
		}
	}
	else {
		posX_ += OBJECT_SPEED * cosAngle;
		posY_ += OBJECT_SPEED * sinAngle;
	}

	if (input[UP]) {
		posY_ += speed;
	}
	if (input[DOWN]) {
		posY_ -= speed;
	}
	if (input[LEFT]) {
		posX_ += speed;
	}
	if (input[RIGHT]) {
		posX_ -= speed;
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

Exp::Exp(int x, int y) {
	posX_ = x;
	posY_ = y;
	SDL_Surface* surface = IMG_Load("Resource/exp.png");
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
Exp::~Exp() {
	SDL_DestroyTexture(texture_);
}

void Exp::render() {
	SDL_Rect objectRect = { posX_, posY_, 25, 25 };
	SDL_RenderCopy(renderer, texture_, nullptr, &objectRect);
}

void Exp::update(int input[5]) {
	if (input[UP]) {
		posY_ += speed;
	}
	if (input[DOWN]) {
		posY_ -= speed;
	}
	if (input[LEFT]) {
		posX_ += speed;
	}
	if (input[RIGHT]) {
		posX_ -= speed;
	}
}

SDL_Rect Exp::get_drect() {
	return { posX_, posY_, 25, 25 };
}