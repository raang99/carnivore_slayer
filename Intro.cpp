#include "Game.h"
#include "Intro.h"

Intro::Intro() 
{
	start_button = new Texture("Resource/intro_button.png");
	background = new Texture("Resource/intro_back.png");

    start_button->set_srect(0, 0, 512, 268);
    start_button->set_drect(300, 250, 200, 100);

    background->set_drect(0, 0, 800, 600);
    background->set_srect(0, 0, 900, 506);
}
Intro::~Intro() {
	delete start_button;
	delete background;
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
                cur_phase = STAGE1;
            }
            break;
        }
    }
}

void Intro::Update() {
}

void Intro::Render() {
    
    background->render();
    start_button->render();

    SDL_RenderPresent(renderer);
}