#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Collider.h"

class Game
{
public:
	Game();

	void run();

	

private:

	void get_input(); //Recieve input
	void update_logic(sf::Time timeSinceLastFrame); //Check Colisions, Move etc
	void update_screen(); //Render all

private:
	sf::RenderWindow mWindow;
	Player mPlayer;
	Collider mDebugCollider;

	//Player and asteroid vars;






};




