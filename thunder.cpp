#include "Thunder.h"

Thunder::Thunder()
	:stateoff(true)
{
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/thunder.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/b.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	s_rect = { 0,0,30,30 };
	d_rect = { 0,0,30,30 };
	s_cen = { 15,15 };
	gen_timer = 1000.0f;
	gen_cycle = 1000.0f;
	gen_quantity = 1;
	damage = 20;
	

	skill_type = SkillType::Thunder;


}

Thunder::~Thunder() {
	SDL_DestroyTexture(texture_);
}

void Thunder::update(std::list<SDL_Rect> enemies, int input[5]) {
	if (stateoff) {
		gen_timer -= 250;
		if (gen_timer < 0) {
			gen_timer = gen_cycle;
			d_rect.x = setRandom(400);
			d_rect.y = setRandom2(300);
			des.posX = d_rect.x;
			des.posY = d_rect.y;
			pos_list.push_back(des);
			stateoff = false;
		}
	}
}

void Thunder::render() {
	SDL_RenderCopy(renderer, texture_, &s_rect, &d_rect);
}

/*void Thunder::add_pos(std::list<SDL_Rect> enemies) {
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
}*/


int Thunder::get_damage() {
	//데미지 주기
	return damage;
}

/*bool Thunder::collider(Pos e) {
	Pos cen;
	cen.posX = SCREEN_CENTER_X;
	cen.posY = SCREEN_CENTER_Y;
	float lean = (des.posY - cen.posY) / (des.posX - cen.posX);
	double dx = length_h * cos(des.angle); //사거리 끝의 점
	double dy = length_h * sin(des.angle);

	if (cen.posX - 100 <= e.posX <= cen.posX + 100 && cen.posY - 100 <= e.posY <= cen.posY + 100)
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

}*/

double setRandom(int a) {
	double rnd = (rand() % a) + SCREEN_CENTER_X - (a/2);
	//printf("%f",rnd);
	return rnd;
}
double setRandom2(int a) {
	double rnd = (rand() % a) + SCREEN_CENTER_Y - (a / 2);
	//printf("%f", rnd);
	return rnd;
}