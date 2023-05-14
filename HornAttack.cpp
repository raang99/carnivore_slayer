#include "HornAttack.h"

HornAttack::HornAttack() 
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/horn.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/b.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	s_rect = {0,0,20,100};
	s_cen = {10,0};
	gen_timer = 1000.0f;
	gen_cycle = 1000.0f;
	gen_quantity = 1;
	damage = 20;
	duration_time = 1000.f;
	duration_cycle = 1000.f;
	length_h = 100.0f; //공격 콜라이더의 세로길이
	length_w = 10.0f; //공격 콜라이더의 가로길이의 반

	skill_type = SkillType::HornAttack;

	
}

HornAttack::~HornAttack() {
	SDL_DestroyTexture(texture_);
}

void HornAttack::update(std::list<SDL_Rect> enemies, int input[5]) {
	//생성 타이머
	/*if (state) {
		duration_time -= 33;
		if (duration_cycle < 0) {
			duration_time = duration_cycle;
			add_pos(enemies);
			state = false;
		}
	}
	else if(!state)
	{
		gen_timer -= 33;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			add_pos(enemies);
			state = true;
		}
	}*/
	gen_timer -= 20;
	if (gen_timer < 0) {
		gen_timer = gen_cycle;
		add_pos(enemies);
		state = false;
	}
}

void HornAttack::render() {
	for (auto& i : pos_list) {
		i.objectRect = { static_cast<int>(i.posX), static_cast<int>(i.posY), 20, 100 };
		SDL_RenderCopyEx(renderer, texture_, &s_rect, &i.objectRect, i.angle, &s_cen, SDL_FLIP_VERTICAL);
	}
}

void HornAttack::add_pos(std::list<SDL_Rect> enemies) {
	float min_distance = 1234123124.0f;
	Pos pos;
	pos.posX = SCREEN_CENTER_X;
	pos.posY = SCREEN_CENTER_Y;
	float min_dx, min_dy;
	float dx, dy, distance;
	for (auto& i : enemies) {
		dx = SCREEN_CENTER_X - i.x;
		dy = SCREEN_CENTER_Y - i.y;
		distance = std::sqrt(dx * dx + dy * dy);
		if (min_distance > distance) {
			min_distance = distance;
			min_dx = dx;
			min_dy = dy;
		}
	}
	des.posX = min_dx;
	des.posY = min_dy;
	des.angle = std::atan2(dy, dx);
	pos.cosAngle = min_dx / min_distance;
	pos.sinAngle = min_dy / min_distance;
	pos.angle = std::atan2(dy, dx) * 180.0f / M_PI;
	pos_list.push_back(pos);
}


int HornAttack::get_damage() {
	//데미지 주기
	return damage;
}

bool HornAttack::collider(Pos e) {
	Pos cen;
	cen.posX = SCREEN_CENTER_X;
	cen.posY = SCREEN_CENTER_Y;
	float lean = (des.posY - cen.posY) / (des.posX - cen.posX);
	double dx = length_h * cos(des.angle); //사거리 끝의 점
	double dy = length_h * sin(des.angle);

	if (cen.posX - 100 <= e.posX <= cen.posX + 100 && cen.posY -100 <= e.posY <= cen.posY +100)
	{
		// 점과 위에서 구한 기울기와 가장 가까운 적의 위치로 직선식을 만들고 그 식과 적의 거리를 공격거리의 가로길이의 반과 확인하는 콜라이더
		if (length_w * length_w == (lean * e.posX - e.posY + cen.posY - lean * cen.posX) / (lean * lean + 1))
		{
			return true; //맞음
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}