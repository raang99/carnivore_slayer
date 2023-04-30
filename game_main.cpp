#include "Game.h"
#include "Intro.h"
#include "Stage1.h"
SDL_Window* window;
SDL_Renderer* renderer;
bool g_running;
int cur_phase;
int main(int argc, char* argv[]) {
	Uint32 last_time, cur_time;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("First Window", 200, 200, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}
	InitGame();
	PhaseInterface* phase[3];
	phase[0] = new Intro();
	phase[1] = new Stage1();

	cur_phase = STAGE1;
	last_time = SDL_GetTicks();
	while (g_running) {

		cur_time = SDL_GetTicks();

		if (cur_time - last_time < 33)
			continue;

		phase[cur_phase]->HandleEvents();
		phase[cur_phase]->Update();
		phase[cur_phase]->Render();

		last_time = cur_time;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
