#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "headers/Game.h"
int main()
{
	srand(time(NULL));
	SoundManager::load_all_sounds();
	Game game;
	game.run();
	return 0;
}