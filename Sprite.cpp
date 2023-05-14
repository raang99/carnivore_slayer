#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, const std::string& filePath, int frameCount, int animationSpeed)
    : texture_(nullptr), frameCount_(frameCount), currentFrame_(0), animationSpeed_(animationSpeed), frameWidth_(0), frameHeight_(0)
{
    // 이미지 파일로부터 텍스처 생성
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        return;
    }

    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // 텍스처로부터 프레임의 너비와 높이 계산
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture_, nullptr, nullptr, &textureWidth, &textureHeight);
    frameWidth_ = textureWidth / frameCount_;
    frameHeight_ = textureHeight;
}

Sprite::~Sprite()
{
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
    }
}

void Sprite::Update()
{
    // 애니메이션 프레임 업데이트
    currentFrame_ = static_cast<int>((SDL_GetTicks() / animationSpeed_) % frameCount_);
}

void Sprite::Render(SDL_Renderer* renderer, int x, int y)
{
    // 현재 프레임의 텍스처 영역 계산
    SDL_Rect srcRect = { frameWidth_ * currentFrame_, 0, frameWidth_, frameHeight_ };

    // 텍스처를 렌더러에 그림
    SDL_Rect destRect = { x, y, frameWidth_, frameHeight_ };
    SDL_RenderCopy(renderer, texture_, &srcRect, &destRect);
}