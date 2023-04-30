#include "Game.h"

void InitGame() {
	g_running = true;
	srand(static_cast<unsigned int>(time(nullptr)));
}
