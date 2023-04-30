#pragma once
#include "Game.h"
#include "Texture.h"
class TTF {
public:
	TTF(const char* font, int font_size);
	~TTF();
	void set_text(const wchar_t* text, SDL_Color color);
	void render(int x, int y);
private:
	SDL_Texture* texture_;
	TTF_Font* font_;
	SDL_Rect srect_;
};
