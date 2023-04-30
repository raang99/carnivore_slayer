#pragma once
#include "Game.h"
class Texture{
public:
	Texture() {};
	Texture(const char* file);
	~Texture();
	void render();
	void set_srect(SDL_Rect rect);
	void set_srect(int x, int y, int w, int h);
	void set_drect(SDL_Rect rect);
	void set_drect(int x, int y, int w, int h);
	SDL_Rect get_srect();
	SDL_Rect get_drect();
private:
	SDL_Texture* texture_;
	SDL_Rect srect_, drect_;
};

class Bullet : public Texture {
public:
	Bullet(const char* file);
	~Bullet();
	void set_drect(int idx, SDL_Rect rect);
	void set_drect(int idx, int x, int y, int w, int h);
	void set_srect(int x, int y, int w, int h);
	SDL_Rect get_drect(int idx);
	void render();
private:
	SDL_Texture* texture_;
	SDL_Rect srect_, drect_[3];
};