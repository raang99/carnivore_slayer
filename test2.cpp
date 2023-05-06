#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;
const std::string BUTTON_LABELS[] = { "선택지 1", "선택지 2", "선택지 3" };
const int BUTTON_COUNT = sizeof(BUTTON_LABELS) / sizeof(BUTTON_LABELS[0]);
const int BUTTON_PADDING = 20;

//struct Button
//{
//    int x;
//    int y;
//    int width;
//    int height;
//    std::string label;
//};
//
//int main(int argc, char** argv)
//{
//    if (SDL_Init(SDL_INIT_VIDEO) != 0)
//    {
//        SDL_Log("SDL 초기화 실패: %s", SDL_GetError());
//        return 1;
//    }
//
//    if (TTF_Init() != 0)
//    {
//        SDL_Log("SDL_ttf 초기화 실패: %s", TTF_GetError());
//        SDL_Quit();
//        return 1;
//    }
//
//    SDL_Window* window = SDL_CreateWindow("SDL 선택지 예제", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
//    if (window == nullptr)
//    {
//        SDL_Log("윈도우 생성 실패: %s", SDL_GetError());
//        TTF_Quit();
//        SDL_Quit();
//        return 1;
//    }
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (renderer == nullptr)
//    {
//        SDL_Log("렌더러 생성 실패: %s", SDL_GetError());
//        SDL_DestroyWindow(window);
//        TTF_Quit();
//        SDL_Quit();
//        return 1;
//    }
//
//    TTF_Font* font = TTF_OpenFont("Resource/arose.ttf", 24);
//    if (font == nullptr)
//    {
//        SDL_Log("폰트 열기 실패: %s", TTF_GetError());
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        TTF_Quit();
//        SDL_Quit();
//        return 1;
//    }
//
//    Button buttons[BUTTON_COUNT];
//    int totalWidth = BUTTON_PADDING * (BUTTON_COUNT + 1);
//    for (int i = 0; i < BUTTON_COUNT; i++)
//    {
//        int buttonX = (SCREEN_WIDTH - totalWidth) / 2 + BUTTON_PADDING * (i + 1) + BUTTON_WIDTH * i;
//        int buttonY = SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
//        buttons[i] = { buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_LABELS[i] };
//    }
//    SDL_Event event;
//    bool isRunning = true;
//    while (isRunning)
//    {
//        while (SDL_PollEvent(&event))
//        {
//            switch (event.type)
//            {
//            case SDL_QUIT:
//                isRunning = false;
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//            {
//                int mouseX = event.button.x;
//                int mouseY = event.button.y;
//                for (int i = 0; i < BUTTON_COUNT; i++)
//                {
//                    if (mouseX >= buttons[i].x && mouseX <= buttons[i].x + buttons[i].width &&
//                        mouseY >= buttons[i].y && mouseY <= buttons[i].y + buttons[i].height)
//                    {
//                        printf("%s\n", buttons[i].label.c_str());
//                        break;
//                    }
//                }
//            }
//            break;
//            }
//        }
//
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//        for (int i = 0; i < BUTTON_COUNT; i++)
//        {
//            SDL_Rect rect = { buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height };
//            SDL_RenderFillRect(renderer, &rect);
//
//            SDL_Surface* labelSurface = TTF_RenderUTF8_Blended(font, buttons[i].label.c_str(), { 255, 255, 255 });
//            if (labelSurface != nullptr)
//            {
//                SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
//                if (labelTexture != nullptr)
//                {
//                    SDL_Rect labelRect = { buttons[i].x + (buttons[i].width - labelSurface->w) / 2, buttons[i].y + (buttons[i].height - labelSurface->h) / 2, labelSurface->w, labelSurface->h };
//                    SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
//                    SDL_DestroyTexture(labelTexture);
//                }
//                SDL_FreeSurface(labelSurface);
//            }
//        }
//
//        SDL_RenderPresent(renderer);
//    }
//
//    TTF_CloseFont(font);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    TTF_Quit();
//    SDL_Quit();
//    return 0;
//}