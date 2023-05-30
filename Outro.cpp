#include "Game.h"
#include "Outro.h"

Outro::Outro()
{
    background = new Sprite(renderer, "Resource/outro_back.png", 4, 200);

    back_win[0] = new Texture("Resource/outro_win1.png");
    back_win[1] = new Texture("Resource/outro_win2.png");
    back_win[2] = new Texture("Resource/outro_win3.png");
    back_win[3] = new Texture("Resource/outro_win4.png");
    back_win[4] = new Texture("Resource/outro_win5.png");
    back_win[5] = new Texture("Resource/outro_win6.png");
    back_win[6] = new Texture("Resource/outro_win7.png");
    back_win[7] = new Texture("Resource/outro_win8.png");
    back_win[8] = new Texture("Resource/outro_win9.png");
    back_win[9] = new Texture("Resource/outro_win10.png");

    for (int i = 0; i < 10; i++) {
        back_win[i]->set_srect(0, 0, 800, 600);
        back_win[i]->set_drect(0, 0, 800, 600);
    }
    
    win_cnt = 0;

    bg_sound_happy = Mix_LoadMUS("Resource/sound/GoodEndBgm2.mp3");
    if (bg_sound_happy == 0) {
        std::cout << "Mix_LoadMUS(\"Resource/sound/GoodEndBgm2.mp3\"): " << Mix_GetError() << std::endl;
    }
}
Outro::~Outro() {
    background->~Sprite();

    for (int i = 0; i < 10; i++) {
        back_win[i]->~Texture();
    }
}
void Outro::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_Rect button_rect;
            if (user_dead) {
                button_rect = {684, 492, 92, 88};
            }
            else {
                button_rect = {700, 14, 82, 78};
            }
            SDL_Point p;
            SDL_GetMouseState(&x, &y);
            p = { x, y };
            if (SDL_PointInRect(&p, &button_rect)) {
                cur_phase = INTRO;
                Mix_HaltMusic();
                sound_started = false;
            }
            break;
        }
    }
}

void Outro::Update() {
    if (user_dead) {
        if (!sound_started) {
            sound_started = true;
        }
        
        background->Update();
    }
    else {
        if (!sound_started) {
            Mix_FadeInMusic(bg_sound_happy, 1, 2000);
            sound_started = true;
        }

        win_cnt++;

        if (win_cnt > 9) {
            win_cnt = 0;
        }
    }
}

void Outro::Render() {
    if (user_dead) {
        background->Render(renderer, 0, 0);
    }
    else {
        for (int i = 0; i < 10; i++) {
            back_win[win_cnt]->render();
        }
    }

    SDL_RenderPresent(renderer);
}