#include "Game.h"
#include "Outro.h"

Outro::Outro()
{
    button = new Texture("Resource/outro_button.png");
    background = new Texture("Resource/outro_back.png");
    back_win = new Texture("Resource/outro_win.png");

    button->set_srect(0, 0, 1008, 280);
    button->set_drect(200, 250, 400, 100);

    background->set_srect(0, 0, 1200, 675);
    background->set_drect(0, 0, 800, 600);

    back_win->set_srect(0, 0, 800, 600);
    back_win->set_drect(0, 0, 800, 600);
    bg_sound_happy = Mix_LoadMUS("Resource/sound/GoodEndBgm2.mp3");
    if (bg_sound_happy == 0) {
        std::cout << "Mix_LoadMUS(\"Resource/sound/GoodEndBgm2.mp3\"): " << Mix_GetError() << std::endl;
    }
}
Outro::~Outro() {
    button->~Texture();
    background->~Texture();
    back_win->~Texture();
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
            SDL_Rect button_rect = button->get_drect();
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
    if (!sound_started) {
        if (user_dead) {
            background->render();
        }
        else {
            Mix_FadeInMusic(bg_sound_happy, 1, 2000);
            back_win->render();
        }
        sound_started = true;
    }
}

void Outro::Render() {
    if (user_dead) {
        background->render();
    }
    else {
        back_win->render();
    }
    button->render();

    SDL_RenderPresent(renderer);
}