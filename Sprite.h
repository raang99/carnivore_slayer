#pragma once
#include "Game.h"

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& filePath, int frameCount, int animationSpeed);
    ~Sprite();

    void Update();
    void Render(SDL_Renderer* renderer, int x, int y);

private:
    SDL_Texture* texture_;
    int frameCount_;
    int currentFrame_;
    int animationSpeed_;
    int frameWidth_;
    int frameHeight_;
};
