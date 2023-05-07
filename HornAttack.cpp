#include "HornAttack.h"

HornAttack::HornAttack() {
	SDL_Surface* sheet_surface;
	sheet_surface = IMG_Load("Resource/b.png");
	if (!sheet_surface) {
		std::cout << "image file " << "Resource/b.png" << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
	gen_timer = 1000.0f;
	gen_cycle = 1000.0f;
	gen_quantity = 1;
	damage = 20;
	pic_time = 0.0f;
	pic_cycle = 700.0f;
	length = 100.0f;
}

HornAttack::~HornAttack() {
	SDL_DestroyTexture(texture_);
}

void HornAttack::update(std::list<SDL_Rect> enemies) {
	//���� Ÿ�̸�
	gen_timer -= 33;
	if (gen_timer < 0) {
		gen_timer = gen_cycle;
		for (int i = 0; i < gen_quantity; i++) {
			add_pos(enemies);
			pic_time = pic_cycle;
		}
	}
	pic_time -= 33;
	//�����ð����� ���̰� �����
	pos_list.remove_if(pic_time < 0);
}

void HornAttack::render() {
	for (auto& i : pos_list) {
		i.objectRect = { static_cast<int>(i.posX), static_cast<int>(i.posY), 40, 20 };
		SDL_RenderCopyEx(renderer, texture_, nullptr, &i.objectRect, i.angle, nullptr, SDL_FLIP_HORIZONTAL);
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
	//������ �ֱ�
	return damage;
}

void HornAttack::collider(std::list<SDL_Rect> enemies) {
	Pos cen;
	cen.posX = SCREEN_CENTER_X;
	cen.posY = SCREEN_CENTER_Y;
	float lean = (des.posY - cen.posY) / (des.posX - cen.posX);
	double dx = length * cos(des.angle); //��Ÿ� ���� ��
	double dy = length * sin(des.angle);
	//��� �� ����Ʈ�� �ҷ��ͼ� ���� ���� �ִ��� Ȯ��
	std::list<Pos> elist; //�������� �� �� ����Ʈ
	for (auto& i : enemies) {
		//���� �˰����� �ϼ����� �ʾƼ� �ӽ÷� ����
		Pos pos;
		pos.posX = i.x;
		pos.posY = i.y;
		if (i.x >= cen.posX) 
		{
			if (i.y >= cen.posY)
			{
				if (cen.posX <= i.x <= dx || cen.posY <= i.y <= dy)
				{
					elist.push_back(pos);
				}
			}
			else
			{
				if (cen.posX <= i.x <= dx || dy <= i.y <= cen.posY)
				{
					elist.push_back(pos);
				}
			}
		}
		else
		{
			if (i.y >= cen.posY)
			{
				if (dx <= i.x <= cen.posX || cen.posY <= i.y <= dy)
				{
					elist.push_back(pos);
				}
			}
			else
			{
				if (dx <= i.x <= cen.posX || dy <= i.y <= cen.posY)
				{
					elist.push_back(pos);
				}
			}
		}
		
	}
}