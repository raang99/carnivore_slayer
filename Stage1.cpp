#include "Stage1.h"

Stage1::Stage1() {
	{//attack
	attack_list.push_back(new BasicAttack());
	attack_list.push_back(new HornAttack());
	attack_list.push_back(new ElectricField());
	attack_list.push_back(new Freeze());
	attack_list.push_back(new Thunder());
	attack_list.push_back(new Tide());
	}
	time = new TTF("Resource/arial.ttf", 40);
	exp_sound = Mix_LoadWAV("Resource/sound/ExpGet.wav");
	if (exp_sound == 0) {
		std::cout << "Resource/sound/ExpGet.wav" << Mix_GetError() << std::endl;
	}
	user_sound = Mix_LoadWAV("Resource/sound/EnemyHit.wav");
	if (user_sound == 0) {
		std::cout << "Resource/sound/EnemyHit.wav" << Mix_GetError() << std::endl;
	}
	stage_end = false;
	user_dead = false;
	time_speed = 33;
	speed = 5;
}

Stage1::~Stage1() {
	user_.~User();
	map_.~Map();
	enemy.~EnemyManager();
	sk_ch.~SkillChoice();
	for (auto& i : attack_list)
		i->~Attack();
	for (auto& i : exp_list)
		i->~Exp();
	for (auto& i : effect_list)
		i->~Sprite();
	time->~TTF();
}

void Stage1::HandleEvents() {
	if (user_dead)
		return;
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
	set_enemyCycle();
	if (user_dead) {
		user_.update(input);
		return;
	}
	if (user_.levelup_flag) 
		return;
	g_elapsed_time_ms += 33;
	if (g_elapsed_time_ms > 1000.0 * 60.0 * 0.1 && boss_flag) {
		enemy.add_boss();
		boss_flag = false;
	}
	std::list<SDL_Rect> enemy_drect_list = enemy.get_drect_list();
	user_hitted(enemy_drect_list);
	user_.update(input);
	for (auto& i : attack_list) {
		i->update(enemy_drect_list, input);
	}
	for (auto it = exp_list.begin(); it != exp_list.end();) {
		(*it)->update(input);
		if (isOverlap(user_.search_rect, (*it)->get_drect())) {
			Mix_PlayChannel(-1, exp_sound, 0);
			user_.add_exp();
			(*it)->~Exp();
			exp_list.erase(it);
		}
		++it;
	}
	enemy.update(input, &attack_list, &exp_list);
	
}

void Stage1::Render() {
	if (user_dead) {
		user_.render();
		SDL_RenderPresent(renderer);
		return;
	}
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
			if (isOverlap(user_.hit_box, i)) {
					Mix_PlayChannel(-1, user_sound, 0);
					user_.sub_hp(10);
			}
		}
		user_.reset_hit_delay();
	}
}

void Stage1::set_enemyCycle() {
	int minute = (g_elapsed_time_ms / (1000.0 * 60.0));
	if (minute == 1) {
		enemy.set_cycle(4000.0f);
	}
	else if (minute == 2) {
		enemy.set_cycle(3000.0f);
	}
	else if (minute == 3) {
		enemy.set_cycle(2000.0f);
	}
	else if (minute == 4) {
		enemy.set_cycle(1000.0f);
	}
	else if (minute == 5) {
		enemy.set_cycle(500.0f);
	}
	else if (minute == 6) {
		enemy.set_cycle(200.0f);
	}
	else if (minute == 7) {
		enemy.set_cycle(100.0f);
	}
	else if (minute == 8) {
		enemy.set_cycle(66.0f);
	}
	else if (minute == 9) {
		enemy.set_cycle(33.0f);
	}
	else if (minute == 10) {
		enemy.set_cycle(33.0f);
	}
}