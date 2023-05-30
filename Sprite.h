#pragma once
#include "Game.h"

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& filePath, int frameCount, int animationSpeed);
    ~Sprite();

    void Update();
    void Render(SDL_Renderer* renderer, int x, int y);
    void RenderEx(SDL_Renderer* renderer, float x, float y, float n);
    void RenderEx2(SDL_Renderer* renderer, SDL_Rect rect, float angle);
    void setColor(SDL_Renderer* renderer, SDL_Color color);
    int frameCount_;
    int currentFrame_ = 0;
    int startFrame;

private:
    SDL_Texture* texture_;
    int animationSpeed_;
    int frameWidth_;
    int frameHeight_;
    bool isStart = false;
};

struct effect {
    int x, y;
    Sprite* effect;
};

#define ENEMY_DEAD 0

class EffectManager {
public:
    EffectManager();
    ~EffectManager();
    void render();
    void update(int input[5]);
    void add(int num, int x, int y);
private:
    std::string effects[2];
    std::list<effect> effect_list;
};
bool isEnd(effect e);
