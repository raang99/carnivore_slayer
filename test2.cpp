//#include <SDL.h>
//#include <SDL_image.h>
//#include <iostream>
//#include <vector>
//
//// ��������Ʈ Ŭ���� ����
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
//    // �̹��� ���Ϸκ��� �ؽ�ó ����
//    SDL_Surface* surface = IMG_Load(filePath.c_str());
//    if (surface == nullptr) {
//        std::cerr << "Failed to load image: " << filePath << std::endl;
//        return;
//    }
//
//    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//
//    // �ؽ�ó�κ��� �������� �ʺ�� ���� ���
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
//    // �ִϸ��̼� ������ ������Ʈ
//    currentFrame_ = static_cast<int>((SDL_GetTicks() / animationSpeed_) % frameCount_);
//}
//
//void Sprite::Render(SDL_Renderer* renderer, int x, int y)
//{
//    // ���� �������� �ؽ�ó ���� ���
//    SDL_Rect srcRect = { frameWidth_ * currentFrame_, 0, frameWidth_, frameHeight_ };
//
//    // �ؽ�ó�� �������� �׸�
//    SDL_Rect destRect = { x, y, frameWidth_, frameHeight_ };
//    SDL_RenderCopy(renderer, texture_, &srcRect, &destRect);
//}
//
//int main(int argc, char* argv[])
//{
//    const int screenWidth = 640;
//    const int screenHeight = 480;
//
//    // SDL �ʱ�ȭ
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    // SDL ������ ����
//    SDL_Window* window = SDL_CreateWindow("Sprite Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
//    if (window == nullptr) {
//        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//    // SDL ������ ����
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (renderer == nullptr) {
//        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//
//    // SDL_image �ʱ�ȭ
//    int imgFlags = IMG_INIT_PNG;
//    if (!(IMG_Init(imgFlags) & imgFlags)) {
//        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//
//    // ��������Ʈ ����
//    Sprite sprite(renderer, "Resource/user/down.png", 10, 200);
//
//    // ���� ����
//    bool quit = false;
//    SDL_Event event;
//    while (!quit) {
//        while (SDL_PollEvent(&event) != 0) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // ������ ������Ʈ
//        float deltaTime = 0.01f; // �� ���� �����Ͽ� �ִϸ��̼� �ӵ��� ������ �� �ֽ��ϴ�.
//        sprite.Update(deltaTime);
//
//        // ȭ�� �����
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        // ��������Ʈ ������
//        sprite.Render(renderer, screenWidth / 2 - 64 / 2, screenHeight / 2 - 64 / 2);
//
//        // ȭ�� ������Ʈ
//        SDL_RenderPresent(renderer);
//    }
//
//    // �ڿ� ����
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    IMG_Quit();
//    SDL_Quit();
//
//    return 0;
//}