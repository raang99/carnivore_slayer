#include "Game.h"
#include "Intro.h"
#include "Stage1.h"
#include "Outro.h"
SDL_Window* window;
SDL_Renderer* renderer;
bool g_running;
int cur_phase;
int time_speed = 33;
int speed = 5;
bool stage_end;
bool user_dead;
int main(int argc, char* argv[]) {
	Uint32 last_time, cur_time;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("First Window", 500, 400, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}
	InitGame();
	PhaseInterface* phase[3];
	phase[0] = new Intro();
	phase[1] = new Stage1();
	phase[2] = new Outro();

	cur_phase = INTRO;
	stage_end = false;
	last_time = SDL_GetTicks();
	
	while (g_running) {

		cur_time = SDL_GetTicks();

		if (cur_time - last_time < time_speed)
			continue;

		phase[cur_phase]->HandleEvents();
		phase[cur_phase]->Update();
		phase[cur_phase]->Render();

		if (stage_end && cur_phase == INTRO) {
			phase[1]->~PhaseInterface();
			phase[1] = new Stage1();
			stage_end = false;
		}
		last_time = cur_time;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
