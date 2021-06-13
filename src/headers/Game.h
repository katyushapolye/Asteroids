#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Collider.h"
#include "Asteroid.h"
#include "TextureManager.h"
#include "Missile.h"
#include <random>


class Game
{
public:
	Game();
	void 									run();



private:                                   
	void 									game_stop_state();
	void 									await_menu_input();
	void									render_menu();
	
	
	
	
	void 									get_input(); //Recieve input

	

	void 									update_logic(sf::Time timeSinceLastFrame); //Check Colisions, Move etc
	void 									update_enemies(sf::Time timeSinceLastFrame);
	bool                                    check_player_collision();
	void                                    check_all_asteroids_collision();
	void 									destroy_asteroid(int cIndex);
	void 									destroy_all_asteroids();
	void 									update_live_score();

	void 									check_game_reset(sf::Clock& gClock);

	void									player_death_reset(sf::Clock& gClock);
	void 									player_level_reset(sf::Clock& gClock);

	


	void 									update_screen(); //Render all
	void 									render_enemies(bool debug);
	void 									render_missiles(bool debug);

	void 									init_level_enemies(int eNumber);
	void									init_ui();
	void									init_sound();


private:

	sf::RenderWindow 						mWindow;
	TextureManager							mTextureManager;
	Player 									mPlayer;
	std::vector<Asteroid>                   mAsteroids;
	sf::Font                                mFont;

	sf::Text                                tScore;
	sf::Text								tScoreNumber;
	sf::Text                                tLiveScoreText;
	sf::Text                                tLiveScore;
	sf::Text								tGameName;
	sf::Text								tPressStart;
	sf::Text                                tDeathText;
	sf::Text								tLevelClearText;

	sf::Sound								aExplosion;
	sf::Sound								pDeath;


	

	bool 									mIsPlayerAlive; 
	bool                                    gameStop;
	int 									pScore;
	int                                     pLevel;






	//Player and asteroid vars;






};




