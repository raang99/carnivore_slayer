#include "Game.h"
#include "User.h"

User::User() {
	SDL_Surface *sheet_surface;
	const char* image_path = "Resource/plain.png";
	sheet_surface = IMG_Load(image_path);
	if (!sheet_surface) {
		std::cout << "image file " << image_path << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	srect_ = { 403, 443, 200, 130 };
	drect_ = { 0, 0, 100, 50 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;//나중에 중앙 정렬할 수 있게 수정
	yPos = drect_.y;
}

User::~User() {
	SDL_DestroyTexture(texture_);
}

void User::render() {
	SDL_RenderCopy(renderer, texture_, &srect_, &drect_);
}

void User::update(int input[5]) {
	if (input[UP]) {
		yPos -= 5;
	}
	if (input[DOWN]) {
		yPos += 5;
	}
	if (input[LEFT]) {
		xPos -= 5;
	}
	if (input[RIGHT]) {
		xPos += 5;
	}
}