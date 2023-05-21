#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const int ANIMATION_DURATION = 2000; // �ִϸ��̼� ���� �ð� (�и���)
//
//SDL_Window* window = nullptr;
//SDL_Renderer* renderer = nullptr;
//SDL_Texture* objectTexture = nullptr;
//
//bool initializeSDL()
//{
//    if (SDL_Init(SDL_INIT_VIDEO) < 0)
//    {
//        std::cout << "SDL �ʱ�ȭ ����: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
//    {
//        std::cout << "SDL_image �ʱ�ȭ ����: " << IMG_GetError() << std::endl;
//        return false;
//    }
//
//    window = SDL_CreateWindow("���� �ִϸ��̼�", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    if (!window)
//    {
//        std::cout << "������ ���� ����: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer)
//    {
//        std::cout << "������ ���� ����: " << SDL_GetError() << std::endl;
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
//        std::cout << "�̹��� �ε� ����: " << IMG_GetError() << std::endl;
//        return false;
//    }
//
//    objectTexture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//
//    if (!objectTexture)
//    {
//        std::cout << "�ؽ�ó ���� ����: " << SDL_GetError() << std::endl;
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
//    Uint32 startTime = SDL_GetTicks(); // �ִϸ��̼� ���� �ð�
//    Uint32 currentTime = 0;
//    float alpha = 0.0f; // ���� ��
//
//    while (true)
//    {
//        SDL_Event e;
//        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
//            break;
//
//        currentTime = SDL_GetTicks(); // ���� �ð�
//        float deltaTime = (currentTime - startTime) / static_cast<float>(ANIMATION_DURATION); // ��� �ð� ���� ���
//
//        // ��� �ð��� ���� ���� �� ������Ʈ
//        alpha = deltaTime;
//        if (alpha > 1.0f) // �ִϸ��̼� ���� �� �ݺ��ǵ��� ����
//            alpha = fmod(deltaTime, 1.0f);
//
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ����� ���������� ����
//        SDL_RenderClear(renderer);
//
//        SDL_SetTextureAlphaMod(objectTexture, static_cast<Uint8>(alpha * 255));  // �ؽ�ó�� ������ �߾� �������� ������
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
//        std::cout << "SDL �ʱ�ȭ ����" << std::endl;
//        return 1;
//    }
//    if (!loadMedia())
//    {
//        std::cout << "�̵�� �ε� ����" << std::endl;
//        closeSDL();
//        return 1;
//    }
//
//    renderAnimation();
//
//    closeSDL();
//    return 0;
//}