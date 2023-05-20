#include "EnemyManager.h"
#include "ElectricField.h"
#include "thunder.h"
#include "Freeze.h"
#include "Tide.h"

EnemyManager::EnemyManager() {
	for (int i = 0; i < 5; i++) {
		list.push_back(new Enemy());
	}
	gen_cycle = 3000.0f;
	gen_timer = gen_cycle;
	gen_quantity = 4;
}

EnemyManager::~EnemyManager() {
	for (auto& i : list)
		i->~Enemy();
	list.~list();
}

void EnemyManager::render() {
	for (auto& i : list)
		i->render();
}

void EnemyManager::update(int input[5], std::list<Attack*>* attack, std::list<Exp*>* exp_list) {
	gen_timer -= 33;
	if (gen_timer < 0) {
		for (int i = 0; i < gen_quantity; i++)
			list.push_back(new Enemy());
		gen_timer = gen_cycle;
	}
	int hp;
	for (auto& i : list) {
		i->update(input);
		hp = i->get_hp();

		for (auto& a : *attack) {
			if (isHitted(i, a)) {
				if (!i->isTideAttacked) {
					hp = i->get_hp();
					hp -= a->get_damage(); //damage;
					i->set_hp(hp);
					if (a->skill_type == SkillType::Tide) {
						i->isThrusted = false;
					}
				}
				if (a->skill_type == SkillType::Tide) {
					if (i->flag) {
						i->isTideAttacked = true;
						i->flag = false;
					}
				}
			}
		}

		if (hp <= 0)
			exp_list->push_back(new Exp(i->posX_, i->posY_));
	}

	list.remove_if(isDead);

	std::list<Attack*>::iterator iter = attack->begin();
	for (; iter != attack->end(); ++iter) {
		if ((*iter)->skill_type == SkillType::ElectricField) {
			dynamic_cast<ElectricField*>((*iter))->ClearPos();
		}
		else if ((*iter)->skill_type == SkillType::Thunder) {
			dynamic_cast<Thunder*>((*iter))->ClearPos();
		}
		else if ((*iter)->skill_type == SkillType::Freeze) {
			dynamic_cast<Freeze*>((*iter))->ClearPos();
		}
	}
}

std::list<SDL_Rect> EnemyManager::get_drect_list() {
	std::list<SDL_Rect> result;
	for (auto i : list)
		result.push_back(i->get_drect());
	return result;
}

bool isHitted(Enemy* e, Attack* Attack)
{
	std::list<Pos>* pos_list = &Attack->pos_list;

	SDL_Rect objectRect = e->get_drect();
	SDL_Rect bulletRect = { 0 };
	for (auto& i : *pos_list) {
		bulletRect = i.objectRect;
		if (isOverlap(objectRect, bulletRect)) {
			if (!isMultiattack(Attack)) {
				pos_list->remove(i);
			}
			if (Attack->skill_type == SkillType::Freeze) {
				e->isFrozen = true;
			}
			else {
				e->isHit = true;
			}
			return true;
		}
	}
	return false;
}

bool isDead(Enemy* e) {
	if (e->get_hp() <= 0) {
		e->~Enemy();
		return true;
	}
	else
		return false;
}

bool isOverlap(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y) {
		// 겹치는 부분이 있음
		return true;
	}
	// 겹치는 부분이 없음
	return false;
}

bool isMultiattack(Attack* Attack) {
	switch (Attack->skill_type) {
	case SkillType::ElectricField:
	case SkillType::Thunder:
	case SkillType::Freeze:
	case SkillType::Tide:
		return true;
	default:
		return false;
	}
}