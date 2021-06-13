#include <SFML/Graphics.hpp>
#include "headers/Game.h"
int main()
{
	SoundManager::load_all_sounds();
	Game game;
	game.run();
	return 0;
}