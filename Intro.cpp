#include "Game.h"
#include "Intro.h"

Intro::Intro() 
{
	start_button = new Texture("Resource/intro_button.png");
	background[0] = new Texture("Resource/intro_back1.png");
    background[1] = new Texture("Resource/intro_back2.png");
    background[2] = new Texture("Resource/intro_back3.png");
    background[3] = new Texture("Resource/intro_back4.png");
    background[4] = new Texture("Resource/intro_back5.png");
    background[5] = new Texture("Resource/intro_back6.png");
    background[6] = new Texture("Resource/intro_back7.png");
    background[7] = new Texture("Resource/intro_back8.png");
    background[8] = new Texture("Resource/intro_back9.png");
    background[9] = new Texture("Resource/intro_back10.png");
    background[10] = new Texture("Resource/intro_back11.png");
    background[11] = new Texture("Resource/intro_back12.png");
    background[12] = new Texture("Resource/intro_back13.png");

    start_button->set_srect(0, 0, 219, 67);
    start_button->set_drect(110, 223, 255, 100);

    for (int i = 0; i < 13; i++) {
        background[i]->set_srect(0, 0, 800, 600);
        background[i]->set_drect(0, 0, 800, 600);
    }

    cnt = 0;

    bg_sound = Mix_LoadMUS("Resource/sound/IntroBgm1.mp3");
    if (bg_sound == 0) {
        std::cout << "Mix_LoadMUS(\"Rinne - Holy war.mp3\"): " << Mix_GetError() << std::endl;
    }
    Mix_VolumeMusic(50);
    
}
Intro::~Intro() {
	delete start_button;
	
    for (int i = 0; i < 13; i++) {
        delete background[i];
    }
}
void Intro::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_Rect button_rect = start_button->get_drect();
            SDL_Point p;
            SDL_GetMouseState(&x, &y);
            p = { x, y };
            if (SDL_PointInRect(&p, &button_rect)) {
                Mix_HaltMusic();
                cur_phase = STAGE1;
                sound_started = false;
            }
            break;
        }
    }
}

void Intro::Update() {
    if (!sound_started) {
        Mix_FadeInMusic(bg_sound, -1, 2000);
        sound_started = true;
    }
    
    cnt++;

    if (cnt > 12) {
        cnt = 0;
    }
}

void Intro::Render() {
    
    for (int i = 0; i < 13; i++) {
        background[cnt]->render();
    }

    start_button->render();

    SDL_RenderPresent(renderer);
}