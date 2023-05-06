#include "SkillChoice.h"

SkillChoice::SkillChoice() {
	font_ = TTF_OpenFont("Resource/arose.ttf", 24);
    if (font_ == nullptr)
    {
        SDL_Log("폰트 열기 실패: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        SDL_Quit();
        exit(-1);
    }
    int totalWidth = BUTTON_PADDING * (BUTTON_COUNT + 1);
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        int buttonX = (SCREEN_WIDTH - totalWidth) / 2 + BUTTON_PADDING * (i + 1) + BUTTON_WIDTH * i;
        int buttonY = SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
        buttons_[i] = { buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_LABELS[i] };
    }
}
SkillChoice::~SkillChoice() {
    TTF_CloseFont(font_);
}
void SkillChoice::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            for (int i = 0; i < BUTTON_COUNT; i++)
            {
                if (mouseX >= buttons_[i].x && mouseX <= buttons_[i].x + buttons_[i].width &&
                    mouseY >= buttons_[i].y && mouseY <= buttons_[i].y + buttons_[i].height)
                {
                    printf("%s\n", buttons_[i].label.c_str());
                    break;
                }
            }
        }
        break;
        }
    }
}

void SkillChoice::render() {
    /*SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);*/
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        SDL_Rect rect = { buttons_[i].x, buttons_[i].y, buttons_[i].width, buttons_[i].height };
        SDL_RenderFillRect(renderer, &rect);

        SDL_Surface* labelSurface = TTF_RenderUTF8_Blended(font_, buttons_[i].label.c_str(), { 255, 255, 255 });
        if (labelSurface != nullptr)
        {
            SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
            if (labelTexture != nullptr)
            {
                SDL_Rect labelRect = { buttons_[i].x + (buttons_[i].width - labelSurface->w) / 2, buttons_[i].y + (buttons_[i].height - labelSurface->h) / 2, labelSurface->w, labelSurface->h };
                SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
                SDL_DestroyTexture(labelTexture);
            }
            SDL_FreeSurface(labelSurface);
        }
    }
    SDL_RenderPresent(renderer);
}