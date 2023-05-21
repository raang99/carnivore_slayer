#include "Game.h"
#include "Sprite.h"


const int EFFECT_COUNT = 1;
#define ENEMY_DEAD 0;

struct effect {
	int x, y;
	Sprite* effect;
};
class EffectManager {
public:
	EffectManager();
	~EffectManager();
	void render();
	void update(int input[5]);
	void add(int num, int x, int y);
private:
	std::string effects[EFFECT_COUNT];
	std::list<effect> effect_list;
};
bool isEnd(effect e);