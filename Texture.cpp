#include "Texture.h"
#include <stdio.h>

void print_rect(SDL_Rect a) {
	printf("x : %d, y : %d, w : %d, h : %d\n", a.x, a.y, a.w, a.h);
}

Texture::Texture(const char* file) {
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load(file);
	if (!sheet_surface) {
		std::cout << "image file " << file << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture_);
}

void Texture::render() {
	SDL_RenderCopy(renderer, texture_, nullptr, &drect_);
}

void Texture::set_drect(int x, int y, int w, int h) {
	drect_.x = x;
	drect_.y = y;
	drect_.w = w;
	drect_.h = h;
}

void Texture::set_drect(SDL_Rect rect) {
	drect_.x = rect.x;
	drect_.y = rect.y;
	drect_.w = rect.w;
	drect_.h = rect.h;
}

void Texture::set_srect(int x, int y, int w, int h) {
	srect_.x = x;
	srect_.y = y;
	srect_.w = w;
	srect_.h = h;
}

void Texture::set_srect(SDL_Rect rect) {
	srect_.x = rect.x;
	srect_.y = rect.y;
	srect_.w = rect.w;
	srect_.h = rect.h;
}

SDL_Rect Texture::get_drect() {
	return drect_;
}

SDL_Rect Texture::get_srect() {
	return srect_;
}

Bullet::Bullet(const char* file) {
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load(file);
	if (!sheet_surface) {
		std::cout << "image file " << file << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
}

Bullet::~Bullet() {
	SDL_DestroyTexture(texture_);
}

void Bullet::set_drect(int idx, SDL_Rect rect) {
	drect_[idx].x = rect.x;
	drect_[idx].y = rect.y;
	drect_[idx].w = rect.w;
	drect_[idx].h = rect.h;
}

void Bullet::set_drect(int idx, int x, int y, int w, int h) {
	
	drect_[idx].x = x;
	drect_[idx].y = y;
	drect_[idx].w = w;
	drect_[idx].h = h;
}

SDL_Rect Bullet::get_drect(int idx) {
	return drect_[idx];
}

void Bullet::render() {
	for (int i = 0; i < 3; i++) {
		if (drect_[i].y > 0) {
			SDL_RenderCopyEx(renderer, texture_, &srect_, &drect_[i], -90, 0, SDL_FLIP_VERTICAL);
		}
	}
}


void Bullet::set_srect(int x, int y, int w, int h) {
	srect_.x = x;
	srect_.y = y;
	srect_.w = w;
	srect_.h = h;
}