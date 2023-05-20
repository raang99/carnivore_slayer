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
	{//attack
	attack_list.push_back(new BasicAttack());
	attack_list.push_back(new HornAttack());
	attack_list.push_back(new ElectricField());
	attack_list.push_back(new Freeze());
	attack_list.push_back(new Thunder());
	}
	time = new TTF("Resource/arial.ttf", 40);
}
Stage1::~Stage1() {
}

void Stage1::HandleEvents() {
	if (user_.levelup_flag) {
		sk_ch.handleEvents(&user_, &attack_list);
		if (!user_.levelup_flag) {
			for (int i = 0; i < 5; i++)
				input[i] = 0;
		}
		return;
	}
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
	if (user_.levelup_flag) 
		return;
	g_elapsed_time_ms += 33;
	std::list<SDL_Rect> enemy_drect_list = enemy.get_drect_list();
	user_hitted(enemy_drect_list);
	user_.update(input);
	for (auto& i : attack_list) {
		i->update(enemy_drect_list, input);
	}
	for (auto it = exp_list.begin(); it != exp_list.end();) {
		(*it)->update(input);
		if (isOverlap(user_.search_rect, (*it)->get_drect())) {
			user_.add_exp();
			(*it)->~Exp();
			exp_list.erase(it);
		}
		++it;
	}
	enemy.update(input, &attack_list, &exp_list);
	
}

void Stage1::Render() {
	if (user_.levelup_flag) {
		sk_ch.render(&user_, &attack_list);
		return;
	}
	map_.setCamera(user_.xPos, user_.yPos);
	map_.render();
	user_.render();
	{//time
		wchar_t tmp[10];
		int seconds = int(g_elapsed_time_ms / 1000.0f);
		wsprintf(tmp, L"%02d:%02d", seconds / 60, seconds % 60);
		time->set_text(tmp, white);
		time->render(350, 20);
	}
	
	enemy.render();
	for(auto& i : attack_list)
		i->render();
	for (auto& i : exp_list)
		i->render();
	SDL_RenderPresent(renderer);
}

void Stage1::user_hitted(std::list<SDL_Rect> enemy_drect_list) {
	if (user_.get_hit_delay() < 0) {
		for (auto& i : enemy_drect_list) {
			if (isOverlap(user_.drect_, i)) {
					user_.sub_hp(10);
			}
		}
		user_.reset_hit_delay();
	}
}