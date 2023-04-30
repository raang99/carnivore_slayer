#include "TTF.h"

TTF::TTF(const char* font, int font_size) {
	font_ = TTF_OpenFont(font, font_size);
}

TTF::~TTF() {
	TTF_CloseFont(font_);
}


void TTF::set_text(const wchar_t* text, SDL_Color color) {
	SDL_Surface* tmp_surface;
	tmp_surface = TTF_RenderUTF8_Blended(font_, CW2A(text, CP_UTF8), color);
	srect_.x = 0;
	srect_.y = 0;
	srect_.w = tmp_surface->w;
	srect_.h = tmp_surface->h;
	texture_ = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}
void TTF::render(int x, int y) {
	SDL_Rect drect = { x, y, srect_.w, srect_.h };
	SDL_RenderCopy(renderer, texture_, &srect_, &drect);
}