#include "Enemy.h"

Enemy::Enemy()
	:isFrozen(false), isTideAttacked(false), flag(true), isThrusted(false), isHit(false)
{
	posX_ = static_cast<float>((rand()- (RAND_MAX / 2)) % (SCREEN_WIDTH * 2));
	posY_ = static_cast<float>((rand()- (RAND_MAX / 2)) % (SCREEN_HEIGHT * 2));\
	while (posX_ < SCREEN_CENTER_X + USER_PADDING && posX_ > SCREEN_CENTER_X - USER_PADDING &&
		posY_ < SCREEN_CENTER_Y + USER_PADDING && posY_ > SCREEN_CENTER_Y - USER_PADDING) {
		posX_ = static_cast<float>(rand() % (SCREEN_WIDTH * 2));
		posY_ = static_cast<float>(rand() % (SCREEN_HEIGHT * 2));
	}
	angle_ = 0.0f;

	texture[right] = new Sprite(renderer, "Resource/enemy/right.png", 11, ani_speed);
	texture[left] = new Sprite(renderer, "Resource/enemy/left.png", 11, ani_speed);

}
Enemy::Enemy(bool bossflag) 
	:isFrozen(false), isTideAttacked(false), flag(true), isThrusted(false), isHit(false)
{
	posX_ = static_cast<float>((rand() - (RAND_MAX / 2)) % (SCREEN_WIDTH * 2));
	posY_ = static_cast<float>((rand() - (RAND_MAX / 2)) % (SCREEN_HEIGHT * 2));\
	while (posX_ < SCREEN_CENTER_X + USER_PADDING && posX_ > SCREEN_CENTER_X - USER_PADDING &&
		posY_ < SCREEN_CENTER_Y + USER_PADDING && posY_ > SCREEN_CENTER_Y - USER_PADDING) {
		posX_ = static_cast<float>(rand() % (SCREEN_WIDTH * 2));
		posY_ = static_cast<float>(rand() % (SCREEN_HEIGHT * 2));
	}
	angle_ = 0.0f;

	hp_ = 2000;
	texture[right] = new Sprite(renderer, "Resource/enemy/right.png", 11, ani_speed);
	texture[left] = new Sprite(renderer, "Resource/enemy/left.png", 11, ani_speed);
	is_boss = true;
}

Enemy::~Enemy() {
	for (int i = 0; i < 2; i++)
		texture[i]->~Sprite();
}

void Enemy::render() {
	if (isFrozen) {
		texture[direct]->setColor(renderer, { 100,100,255,255 });
	}
	else {
		if (isHit) {
			texture[direct]->setColor(renderer,{ 255,50,50,255 });
		}
		else {
			texture[direct]->setColor(renderer, { 255,255,255,255 });
		}
	}

	if (is_boss) {
		{	//hp_bar
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_Rect hp_rect = { static_cast<int>(posX_) + 20, static_cast<int>(posY_) - 10 , 200, 5 };
			SDL_RenderFillRect(renderer, &hp_rect);
			int point = static_cast<int>((hp_ / 2000) * 200.0);
			SDL_SetRenderDrawColor(renderer, 136, 8, 8, 255);
			hp_rect.w = point;
			SDL_RenderFillRect(renderer, &hp_rect);
		}
		texture[direct]->RenderEx(renderer, static_cast<int>(posX_), static_cast<int>(posY_), 2);
	}
	else
		texture[direct]->Render(renderer, static_cast<int>(posX_), static_cast<int>(posY_));
}

void Enemy::update(int input[5]) {
	// 삼각비를 이용한 이동
	float dx = (SCREEN_CENTER_X-50) - posX_;
	float dy = (SCREEN_CENTER_Y-30) - posY_;
	float distance = std::sqrt(dx * dx + dy * dy);
	float cosAngle = dx / distance;
	float sinAngle = dy / distance;
	if (cosAngle < 0) 
		direct = left;
	else 
		direct = right;
	texture[direct]->Update();
	
	if (isFrozen) {
		unfreeze_timer -= 33.f;
		posX_ += OBJECT_SPEED * cosAngle * 0.3;
		posY_ += OBJECT_SPEED * sinAngle * 0.3;
		if (unfreeze_timer < 0.f) {
			isFrozen = false;
			unfreeze_timer = 3000.f;
		}
	}
	else {
		posX_ += OBJECT_SPEED * cosAngle;
		posY_ += OBJECT_SPEED * sinAngle;
	}

	if (isTideAttacked) {
		attacked_timer -= 33.f;
		if (attacked_timer < 0.f) {
			isTideAttacked = false;
			flag = true;
			attacked_timer = 2000.f;
		}
		if (!isThrusted) {
			posX_ -= OBJECT_SPEED * cosAngle * 100;
			posY_ -= OBJECT_SPEED * sinAngle * 100;
		}
		isThrusted = true;
	}

	if (isHit) {
		hit_timer -= 33.f;
		if (hit_timer < 0.f) {
			isHit = false;
			hit_timer = 250.f;
		}
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
	SDL_Rect objectRect;
	if(is_boss)
		objectRect = { static_cast<int>(posX_), static_cast<int>(posY_), OBJECT_WIDTH*2, OBJECT_HEIGHT*2};
	else
		objectRect = { static_cast<int>(posX_), static_cast<int>(posY_), OBJECT_WIDTH, OBJECT_HEIGHT };
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