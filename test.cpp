#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPRITE_SIZE_WIDTH = 64;
const int SPRITE_SIZE_HEIGHT = 128;
const int FRAME_RATE = 60;
const int FRAME_TIME = 1000 / FRAME_RATE;
const int TOTAL_FRAMES = 6;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gSpriteSheetTexture = NULL;
SDL_Rect gSpriteClips[TOTAL_FRAMES];
int gCurrentFrame = 0;

//bool init();
//bool loadMedia();
//void close();
//
//bool init() {
//    bool success = true;
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
//        success = false;
//    }
//    else {
//        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
//            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
//        }
//        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//        if (gWindow == NULL) {
//            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
//            success = false;
//        }
//        else {
//            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//            if (gRenderer == NULL) {
//                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
//                success = false;
//            }
//            else {
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                int imgFlags = IMG_INIT_PNG;
//                if (!(IMG_Init(imgFlags) & imgFlags)) {
//                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
//                    success = false;
//                }
//            }
//        }
//    }
//    return success;
//}
//
//bool loadMedia() {
//    bool success = true;
//    SDL_Surface* spriteSurface = IMG_Load("test.png");
//    if (spriteSurface == NULL) {
//        std::cout << "Unable to load image " << "spritesheet.png" << "! SDL_image Error: " << IMG_GetError() << std::endl;
//        success = false;
//    }
//    else {
//        gSpriteSheetTexture = SDL_CreateTextureFromSurface(gRenderer, spriteSurface);
//        if (gSpriteSheetTexture == NULL) {
//            std::cout << "Unable to create texture from " << "spritesheet.png" << "! SDL Error: " << SDL_GetError() << std::endl;
//            success = false;
//        }
//        else {
//            for (int i = 1; i < TOTAL_FRAMES; i++) {
//                gSpriteClips[i].x = i * SPRITE_SIZE_WIDTH;
//                gSpriteClips[i].y = 0;
//                gSpriteClips[i].w = SPRITE_SIZE_WIDTH;
//                gSpriteClips[i].h = SPRITE_SIZE_HEIGHT;
//            }
//            SDL_FreeSurface(spriteSurface);
//        }
//    }
//    return success;
//}
//
//void close() {
//    SDL_DestroyTexture(gSpriteSheetTexture);
//    gSpriteSheetTexture = NULL;
//    SDL_DestroyRenderer(gRenderer);
//    gRenderer = NULL;
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    IMG_Quit();
//    SDL_Quit();
//}
//
//int main(int argc, char* args[]) {
//    if (!init()) {
//        std::cout << "Failed to initialize!" << std::endl;
//        return -1;
//    }
//    if (!loadMedia()) {
//        std::cout << "Failed to load media!" << std::endl;
//        return -1;
//    }
//
//    bool quit = false;
//    SDL_Event e;
//    int frameStartTime = 0;
//    int frameEndTime = 0;
//
//    while (!quit) {
//        frameStartTime = SDL_GetTicks();
//        while (SDL_PollEvent(&e) != 0) {
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//        gCurrentFrame++;
//        if (0 == (gCurrentFrame / (FRAME_RATE / TOTAL_FRAMES)))
//            continue;
//        SDL_RenderClear(gRenderer);
//        SDL_Rect currentClip = gSpriteClips[gCurrentFrame / (FRAME_RATE / TOTAL_FRAMES)];
//        SDL_RenderCopy(gRenderer, gSpriteSheetTexture, &currentClip, NULL);
//        SDL_RenderPresent(gRenderer);
//
//        if (gCurrentFrame / (FRAME_RATE / TOTAL_FRAMES) >= TOTAL_FRAMES) {
//            gCurrentFrame = 0;
//        }
//
//        frameEndTime = SDL_GetTicks();
//        int frameTimeDiff = frameEndTime - frameStartTime;
//        if (frameTimeDiff < FRAME_TIME) {
//            SDL_Delay(FRAME_TIME - frameTimeDiff);
//        }
//    }
//
//    close();
//
//    return 0;
//}