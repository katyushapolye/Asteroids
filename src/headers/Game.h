#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Collider.h"
#include "Asteroid.h"
#include "TextureManager.h"


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
	TextureManager					mTextureManager;
	Player 									mPlayer;
	Asteroid 								mDebugAsteroid;
	std::vector<Asteroid>                   mAsteroids;






	//Player and asteroid vars;






};




