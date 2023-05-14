//#include <SDL.h>
//#include <SDL_image.h>
//#include <iostream>
//#include <vector>
//
//// 스프라이트 클래스 정의
//class Sprite {
//public:
//    Sprite(SDL_Renderer* renderer, const std::string& filePath, int frameCount, int animationSpeed);
//    ~Sprite();
//
//    void Update(float deltaTime);
//    void Render(SDL_Renderer* renderer, int x, int y);
//
//private:
//    SDL_Texture* texture_;
//    int frameCount_;
//    int currentFrame_;
//    int animationSpeed_;
//    int frameWidth_;
//    int frameHeight_;
//};
//
//Sprite::Sprite(SDL_Renderer* renderer, const std::string& filePath, int frameCount, int animationSpeed)
//    : texture_(nullptr), frameCount_(frameCount), currentFrame_(0), animationSpeed_(animationSpeed), frameWidth_(0), frameHeight_(0)
//{
//    // 이미지 파일로부터 텍스처 생성
//    SDL_Surface* surface = IMG_Load(filePath.c_str());
//    if (surface == nullptr) {
//        std::cerr << "Failed to load image: " << filePath << std::endl;
//        return;
//    }
//
//    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//
//    // 텍스처로부터 프레임의 너비와 높이 계산
//    int textureWidth, textureHeight;
//    SDL_QueryTexture(texture_, nullptr, nullptr, &textureWidth, &textureHeight);
//    frameWidth_ = textureWidth / frameCount_;
//    frameHeight_ = textureHeight;
//}
//
//Sprite::~Sprite()
//{
//    if (texture_ != nullptr) {
//        SDL_DestroyTexture(texture_);
//    }
//}
//
//void Sprite::Update(float deltaTime)
//{
//    // 애니메이션 프레임 업데이트
//    currentFrame_ = static_cast<int>((SDL_GetTicks() / animationSpeed_) % frameCount_);
//}
//
//void Sprite::Render(SDL_Renderer* renderer, int x, int y)
//{
//    // 현재 프레임의 텍스처 영역 계산
//    SDL_Rect srcRect = { frameWidth_ * currentFrame_, 0, frameWidth_, frameHeight_ };
//
//    // 텍스처를 렌더러에 그림
//    SDL_Rect destRect = { x, y, frameWidth_, frameHeight_ };
//    SDL_RenderCopy(renderer, texture_, &srcRect, &destRect);
//}
//
//int main(int argc, char* argv[])
//{
//    const int screenWidth = 640;
//    const int screenHeight = 480;
//
//    // SDL 초기화
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    // SDL 윈도우 생성
//    SDL_Window* window = SDL_CreateWindow("Sprite Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
//    if (window == nullptr) {
//        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//    // SDL 렌더러 생성
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (renderer == nullptr) {
//        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//
//    // SDL_image 초기화
//    int imgFlags = IMG_INIT_PNG;
//    if (!(IMG_Init(imgFlags) & imgFlags)) {
//        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//
//    // 스프라이트 생성
//    Sprite sprite(renderer, "Resource/user/down.png", 10, 200);
//
//    // 게임 루프
//    bool quit = false;
//    SDL_Event event;
//    while (!quit) {
//        while (SDL_PollEvent(&event) != 0) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // 프레임 업데이트
//        float deltaTime = 0.01f; // 이 값을 조정하여 애니메이션 속도를 조절할 수 있습니다.
//        sprite.Update(deltaTime);
//
//        // 화면 지우기
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        // 스프라이트 렌더링
//        sprite.Render(renderer, screenWidth / 2 - 64 / 2, screenHeight / 2 - 64 / 2);
//
//        // 화면 업데이트
//        SDL_RenderPresent(renderer);
//    }
//
//    // 자원 해제
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    IMG_Quit();
//    SDL_Quit();
//
//    return 0;
//}