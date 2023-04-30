#include "Stage1.h"

Stage1::Stage1() {
	{ //User and Map
	plain = new Texture("Resource/plain.png");
	background = new Texture("Resource/back.png");
	plain->set_drect(300, 200, 100, 50);
	plain->set_srect(403, 443, 200, 130);
	background->set_srect(0, 0, 800, 600);
	background->set_drect(0, 0, 800, 600);
	}
	attack_list.push_back(new BasicAttack());
	
}
Stage1::~Stage1() {
}

void Stage1::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				input[LEFT] = 1;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				input[RIGHT] = 1;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				input[UP] = 1;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				input[DOWN] = 1;
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				input[SHOT] = 1;
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT) {
				input[LEFT] = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				input[RIGHT] = 0;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				input[UP] = 0;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				input[DOWN] = 0;
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				input[SHOT] = 0;
			}
			is_shot = false;
			break;

		default:
			break;
		}
	}
}

void Stage1::Update() {
	std::list<SDL_Rect> enemy_drect_list = enemy.get_drect_list();
	user_.update(input);
	for (auto& i : attack_list) {
		i->update(enemy_drect_list);
	}

	int hp;
	enemy.update(input, &attack_list);

	
}

void Stage1::Render() {
	map_.setCamera(user_.xPos, user_.yPos);
	map_.render();
	user_.render();
	
	enemy.render();
	for(auto& i : attack_list)
		i->render();
	SDL_RenderPresent(renderer);
}