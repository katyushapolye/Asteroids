#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Collider.h"
#include "Asteroid.h"

class Game
{
public:
	Game();
	void 									run();



private:

	void 									get_input(); //Recieve input
	void 									update_logic(sf::Time timeSinceLastFrame); //Check Colisions, Move etc
	void 									update_screen(); //Render all



private:
	sf::RenderWindow 						mWindow;
	Player 									mPlayer;
	Asteroid 								mDebugAsteroid;






	//Player and asteroid vars;






};




