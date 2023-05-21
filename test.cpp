#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const int ANIMATION_DURATION = 2000; // 애니메이션 지속 시간 (밀리초)
//
//SDL_Window* window = nullptr;
//SDL_Renderer* renderer = nullptr;
//SDL_Texture* objectTexture = nullptr;
//
//bool initializeSDL()
//{
//    if (SDL_Init(SDL_INIT_VIDEO) < 0)
//    {
//        std::cout << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
//    {
//        std::cout << "SDL_image 초기화 실패: " << IMG_GetError() << std::endl;
//        return false;
//    }
//
//    window = SDL_CreateWindow("투명도 애니메이션", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    if (!window)
//    {
//        std::cout << "윈도우 생성 실패: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer)
//    {
//        std::cout << "렌더러 생성 실패: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    return true;
//}
//
//bool loadMedia()
//{
//
//    SDL_Surface* surface = IMG_Load("Resource/b.png");
//    if (!surface)
//    {
//        std::cout << "이미지 로드 실패: " << IMG_GetError() << std::endl;
//        return false;
//    }
//
//    objectTexture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//
//    if (!objectTexture)
//    {
//        std::cout << "텍스처 생성 실패: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    return true;
//}
//
//void closeSDL()
//{
//    SDL_DestroyTexture(objectTexture);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    IMG_Quit();
//    SDL_Quit();
//}
//
//void renderAnimation()
//{
//    Uint32 startTime = SDL_GetTicks(); // 애니메이션 시작 시간
//    Uint32 currentTime = 0;
//    float alpha = 0.0f; // 투명도 값
//
//    while (true)
//    {
//        SDL_Event e;
//        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
//            break;
//
//        currentTime = SDL_GetTicks(); // 현재 시간
//        float deltaTime = (currentTime - startTime) / static_cast<float>(ANIMATION_DURATION); // 경과 시간 비율 계산
//
//        // 경과 시간에 따라 투명도 값 업데이트
//        alpha = deltaTime;
//        if (alpha > 1.0f) // 애니메이션 종료 후 반복되도록 설정
//            alpha = fmod(deltaTime, 1.0f);
//
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 배경을 검정색으로 설정
//        SDL_RenderClear(renderer);
//
//        SDL_SetTextureAlphaMod(objectTexture, static_cast<Uint8>(alpha * 255));  // 텍스처를 윈도우 중앙 기준으로 렌더링
//        int textureWidth, textureHeight;
//        SDL_QueryTexture(objectTexture, nullptr, nullptr, &textureWidth, &textureHeight);
//
//        SDL_Rect renderRect = { (WINDOW_WIDTH - textureWidth) / 2, (WINDOW_HEIGHT - textureHeight) / 2,
//                                textureWidth, textureHeight };
//
//        SDL_RenderCopy(renderer, objectTexture, nullptr, &renderRect);
//
//        SDL_RenderPresent(renderer);
//    }
//}
//int main(int argc, char* args[])
//{
//    if (!initializeSDL())
//    {
//        std::cout << "SDL 초기화 실패" << std::endl;
//        return 1;
//    }
//    if (!loadMedia())
//    {
//        std::cout << "미디어 로드 실패" << std::endl;
//        closeSDL();
//        return 1;
//    }
//
//    renderAnimation();
//
//    closeSDL();
//    return 0;
//}