#include "Game.h"
#include "User.h"

User::User() {
	srect_ = { 403, 443, 200, 130 };
	drect_ = { 0, 0, 64, 64 };
	drect_.x = SCREEN_WIDTH / 2 - drect_.w / 2;
	drect_.y = SCREEN_HEIGHT / 2 - drect_.h / 2;
	xPos = drect_.x;//나중에 중앙 정렬할 수 있게 수정
	yPos = drect_.y;
	hit_box.x = drect_.x + 10;
	hit_box.y = drect_.y + 10;
	hit_box.w = drect_.w - 20;
	hit_box.h = drect_.h - 20;
	max_exp = 100;
	cur_exp = 0;
	max_hp = 200;
	cur_hp = max_hp;
	texture[UP] = new Sprite(renderer, "Resource/user/up.png", 10, 200);
	texture[DOWN] = new Sprite(renderer, "Resource/user/down.png", 10, 200);
	texture[LEFT] = new Sprite(renderer, "Resource/user/left.png", 12, 200);
	texture[RIGHT] = new Sprite(renderer, "Resource/user/right.png", 12, 200);
	dead_effect = new Sprite(renderer, "Resource/user/dead.png", 20, 200);
	direct = DOWN;
	search_rect = drect_;
}

User::~User() {
}

void User::render() {
	if (user_dead) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect tmp = { 0,0,800,600 };
		SDL_RenderFillRect(renderer, &tmp);
		dead_effect->Render(renderer, drect_.x, drect_.y);
		return;
	}
	texture[direct]->Render(renderer, drect_.x, drect_.y);
	//	Bright Yellow - exp bar
	{
		int point = static_cast<int>((cur_exp / max_exp) * 100.0);
		SDL_SetRenderDrawColor(renderer, 255, 234, 0, 255);
		SDL_Rect exp_rect = { drect_.x - 16, drect_.y - 20, point, 5 };
		SDL_RenderFillRect(renderer, &exp_rect);
	}
	// Blood Red - hp bar
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect hp_rect = { drect_.x - 16, drect_.y + 70, 100, 5 };
		SDL_RenderFillRect(renderer, &hp_rect);
		int point = static_cast<int>((cur_hp / max_hp) * 100.0);
		SDL_SetRenderDrawColor(renderer, 136, 8, 8, 255);
		hp_rect.w = point;
		SDL_RenderFillRect(renderer, &hp_rect);
	}
	hit_delay -= 22;
}

void User::update(int input[5]) {
	if (user_dead) {
		dead_effect->Update();
		if (dead_effect->currentFrame_ >= 19) {
			stage_end = true;
			cur_phase = END;
		}
		return;
	}
	
	heal_delay -= 33;
	if (cur_hp <= 0) {
		/*stage_end = true;
		cur_phase = END;*/
		user_dead = true;
	}
	if (heal_delay < 0) {
		if (cur_hp < max_hp) {
			cur_hp += heal_point;
			if (cur_hp > max_hp)
				cur_hp = max_hp;
		}
		heal_delay = 1000.0f;
	}
	set_direct(input);
	for(int i = 0; i < 4; i++)
		texture[i]->Update();

	if (input[UP]) {
		yPos -= speed;
	}
	if (input[DOWN]) {
		yPos += speed;
	}
	if (input[LEFT]) {
		xPos -= speed;
	}
	if (input[RIGHT]) {
		xPos += speed;
	}
	//level up
	if (cur_exp >= max_exp) {
		levelup_flag = true;
		cur_exp = 0;
		max_exp *= 1.1;
	}
}

void User::add_exp() {
	cur_exp += exp;
}

void User::sub_hp(int damage) {
	cur_hp -= damage;
}

double User::get_hit_delay() {
	return hit_delay;
}
void User::reset_hit_delay() {
	hit_delay = 100.0f;
}

void User::set_direct(int input[5]) {
	if (input[UP] && !input[DOWN] && !input[LEFT] && !input[RIGHT])
		direct = UP;
	else if (!input[UP] && input[DOWN] && !input[LEFT] && !input[RIGHT])
		direct = DOWN;
	else if (!input[UP] && !input[DOWN] && input[LEFT] && !input[RIGHT])
		direct = LEFT;
	else if (!input[UP] && !input[DOWN] && !input[LEFT] && input[RIGHT])
		direct = RIGHT;
}

void User::hp_max() {
	max_hp *= 1.1;
}

void User::heal() {
	heal_point += 5.0f;
}

void User::speed_up() {
	speed += 1;
}

void User::search() {
	search_rect.x -= 20;
	search_rect.y -= 20;
	search_rect.w += 40;
	search_rect.h += 40;
}

void User::growth() {
	exp *= 1.1;
	printf("exp : %f\n", exp);
}