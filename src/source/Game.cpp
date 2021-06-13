#include <headers/Game.h>
#include <headers/Player.h>
#include <filesystem>
#include <iostream>
Game::Game() : mWindow(sf::VideoMode(mScreenX, mScreenY), "Asteroid"),	
			   mTextureManager(),
			   mPlayer(mTextureManager.get_texture(PlayerTexture),
			   mTextureManager.get_texture(MissileTexture)),
			   mAsteroids(),
			   mFont(),
			   tScore(),
			   tScoreNumber(),
			   tLiveScore(),
			   tLiveScoreText(),
			   tGameName(),
			   tPressStart(),
			   tDeathText(),
			   tLevelClearText(),
			   aExplosion(),
			   pDeath(),
			   mIsPlayerAlive(false),
			   gameStop(true),
			   pScore(0),
			   pLevel(1)
			   

{

	init_ui();
	init_sound();

	mWindow.setFramerateLimit(60);

	mWindow.clear(sf::Color::Black);

}
/*===========================================TO DO======================================

3-Make Asteroids Generate on random, but not on the Playerexlusion zone
*/

//ToDo


void Game::init_ui(){
	mFont.loadFromFile("Assets/Font/gFont.TTF");
	tScore.setFont(mFont);

	tGameName.setFont(mFont);
	tPressStart.setFont(mFont);
	tScore.setFont(mFont);
	tScoreNumber.setFont(mFont);
	tLiveScore.setFont(mFont);
	tLiveScoreText.setFont(mFont);
	tDeathText.setFont(mFont);
	tLevelClearText.setFont(mFont);

	tGameName.setString("A S T E R O I D S");
	tPressStart.setString("PRESS SPACE TO PLAY\n\nPRESS ESCAPE TO QUIT");
	tScore.setString("PAST SCORE");
	tLiveScoreText.setString("SCORE ");
	tScoreNumber.setString(std::to_string(pScore));
	tDeathText.setString("YOU ARE DEAD");
	tLevelClearText.setString("LEVEL CLEARED");

	tGameName.setCharacterSize(40);
	tPressStart.setCharacterSize(20);
	tScore.setCharacterSize(18);
	tScoreNumber.setCharacterSize(18);
	tLiveScore.setCharacterSize(12);
	tLiveScoreText.setCharacterSize(12);
	tDeathText.setCharacterSize(30);
	tLevelClearText.setCharacterSize(30);


	tGameName.setOrigin(tGameName.getLocalBounds().width/2,tGameName.getLocalBounds().height/2);
	tPressStart.setOrigin(tPressStart.getLocalBounds().width/2,tPressStart.getLocalBounds().height/2);
	tScore.setOrigin(tScore.getLocalBounds().width/2,tScore.getLocalBounds().height/2);
	tScoreNumber.setOrigin(tScoreNumber.getLocalBounds().width/2,tScoreNumber.getLocalBounds().height/2);
	tLiveScoreText.setOrigin(tLiveScoreText.getLocalBounds().width/2,tLiveScoreText.getLocalBounds().height/2);
	tDeathText.setOrigin(tDeathText.getLocalBounds().width/2,tDeathText.getLocalBounds().height/2);
	tLevelClearText.setOrigin(tLevelClearText.getLocalBounds().width/2,tLevelClearText.getLocalBounds().height/2);



	tGameName.setPosition(300,100);
	tPressStart.setPosition(300,400);
	tScore.setPosition(300,300);
	tScoreNumber.setPosition(300,330);
	tLiveScoreText.setPosition(510,20);
	tDeathText.setPosition(300,200);
	tLevelClearText.setPosition(300,200);

}


void Game::init_sound(){
	aExplosion.setBuffer(SoundManager::get_sound(AsteroidExplosionSound));
	pDeath.setBuffer(SoundManager::get_sound(PlayerDeathSound));
	aExplosion.setVolume(10);
}
//Level Initialization//
void Game::init_level_enemies(int eNumber){
	destroy_all_asteroids();
	for (int i = 0; i < eNumber; i++)
	{
		Asteroid aTemp(0 + (i*100),50,120,(i+2)*70,10+i*45,mTextureManager.get_texture(EnemyTexture));
		mAsteroids.push_back(std::move(aTemp));
		
	}
}

//Getting Input
void Game::get_input()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) //Returns a "list" and iterator to ALL events, must react to them all, and then update the logic
	{
		
		/*The input must be set using keyflags, to handle multiple keystrocks
		es at the same time, the movement is handled later at the logic update when t
		e keyflags are set
		Switch to Switch, too much events*/
		if (event.type == sf::Event::Closed)
		{
			mIsPlayerAlive = false;
			mWindow.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			mPlayer.send_input(event.key.code, true);
		}
		if (event.type == sf::Event::KeyReleased)
		{
			mPlayer.send_input(event.key.code, false);
		}
		if (event.type == sf::Event::LostFocus)
		{
			//reset player state
		}
	}
}

//Check Colisions
bool Game::check_player_collision(){
	for (size_t i = 0; i < mAsteroids.size(); i++)
	{
		if(mPlayer.check_colision(mAsteroids.at(i))){
			
			return true;

		}
	}
	return false;
}
void Game::check_all_asteroids_collision(){
	for (int i = 0; i < mPlayer.get_all_active_missiles().size(); i++)
	{
		for (int j = 0; j < mAsteroids.size(); j++)
		{
			if(mPlayer.get_all_active_missiles().at(i).check_colision(mAsteroids.at(j))){
				destroy_asteroid(j);
				aExplosion.play();
				
			}
		}
	}
}
//Destroy Collided Asteroid

void Game::destroy_asteroid(int cIndex){
	pScore += 100;
	if(mAsteroids.at(cIndex).get_radius() <= 30){
		mAsteroids.erase(mAsteroids.begin()+cIndex);
	}
	else{
		std::cout <<"ORIGINAL ASTEROID RAD:" <<mAsteroids.at(cIndex).get_radius() << std::endl;

		Asteroid tempA(mAsteroids.at(cIndex).get_position().X, 
					   mAsteroids.at(cIndex).get_position().Y,
					   mAsteroids.at(cIndex).get_radius()/2,
					   mAsteroids.at(cIndex).get_aproximate_velocity(),
					   mAsteroids.at(cIndex).get_angle()+90,
					   mTextureManager.get_texture(EnemyTexture));
		std::cout <<"DIVIDED ASTEROID RAD:" <<tempA.get_radius() << std::endl;
		Asteroid tempB(mAsteroids.at(cIndex).get_position().X, 
					   mAsteroids.at(cIndex).get_position().Y,
					   mAsteroids.at(cIndex).get_radius()/2,
					   mAsteroids.at(cIndex).get_aproximate_velocity(),
					   mAsteroids.at(cIndex).get_angle()-90,
					   mTextureManager.get_texture(EnemyTexture));
		mAsteroids.push_back(tempA);
		mAsteroids.push_back(tempB);
		mAsteroids.erase(mAsteroids.begin()+cIndex);
	}
	


}

void Game::destroy_all_asteroids(){
	mAsteroids.clear();
	mAsteroids.shrink_to_fit();
	
	
}
//Update Logic 
void Game::update_enemies(sf::Time timeSinceLastFrame){

	for (size_t i = 0; i < mAsteroids.size(); i++)
	{
		mAsteroids.at(i).update_asteroid(timeSinceLastFrame);
	}
}

void Game::update_logic(sf::Time frameTime)

{
	if(check_player_collision()){
		mIsPlayerAlive = false;
		pDeath.play();
		//RESET GAME STATE;
	}
	check_all_asteroids_collision(); 
	mPlayer.update_player(frameTime);
	update_enemies(frameTime);
	update_live_score();
}

void Game::update_live_score(){
	tLiveScore.setString(std::to_string(pScore));
	tLiveScore.setOrigin(tLiveScore.getLocalBounds().width/2,tLiveScore.getLocalBounds().height/2);
	tLiveScore.setPosition(570,20);

}

//Render All
void Game::render_enemies(bool debug){
	for (int i = 0; i < mAsteroids.size(); i++)
	{
		mWindow.draw(mAsteroids.at(i).get_sprite());
	}
	if(debug){
		for (int i = 0; i < mAsteroids.size(); i++)
	{
		mWindow.draw(mAsteroids.at(i).get_collider_visual());
	}
	}
}

void Game::render_missiles(bool debug){
	for (size_t i = 0; i < mPlayer.get_all_active_missiles().size(); i++)
	{
		mWindow.draw(mPlayer.get_all_active_missiles().at(i).get_sprite());
	}
	if(debug){
		for (size_t i = 0; i < mPlayer.get_all_active_missiles().size(); i++)
	{
		mWindow.draw(mPlayer.get_all_active_missiles().at(i).get_collider_visual());
	}
	}
	
}
//Draw All to Screen

void Game::update_screen()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(mPlayer.get_sprite());

	render_enemies(false);
	render_missiles(false);
	mWindow.draw(tLiveScore);
	mWindow.draw(tLiveScoreText);
	mWindow.display();
}


//MAIN LOOP FUNCION AND SUB ROUTINES -> //Level Transition and Cooldowns
void Game::run(){


	sf::Clock gClock;
	sf::Time timeSinceLastFrame;
	while(mWindow.isOpen()){

		if(gameStop){
			game_stop_state();
			gClock.restart();
			
		}

		else{
			while (mIsPlayerAlive)
			{
				get_input();
				update_logic(timeSinceLastFrame);
				update_screen();
				timeSinceLastFrame = gClock.restart();
				check_game_reset(gClock);
				
			}

		}

	}

}

void Game::await_menu_input(){
	sf::Event menuEvent;
	while(mWindow.pollEvent(menuEvent)){
		if(menuEvent.type == sf::Event::Closed){
			mWindow.close();
		}
		if(menuEvent.type == sf::Event::KeyPressed){
			if (menuEvent.key.code ==  sf::Keyboard::Space){
				mIsPlayerAlive = true;
				gameStop = false;
				init_level_enemies(pLevel);
				mPlayer.reset();
				return;
			}	
			if(menuEvent.key.code ==  sf::Keyboard::Escape){
				mWindow.close();
			}
		}
		if(menuEvent.type == sf::Event::Closed){
			mWindow.close();
		}
		
	}
	return;
}

void Game::game_stop_state(){
	render_menu();
	await_menu_input();
}

void Game::render_menu(){
	mWindow.clear();
	mWindow.draw(tGameName);
	mWindow.draw(tPressStart);
	mWindow.draw(tScore);
	mWindow.draw(tScoreNumber);
	mWindow.display();
	await_menu_input();
}

void Game::check_game_reset(sf::Clock& gClock){
	if(mAsteroids.size() == 0){
		player_level_reset(gClock);
		
	}
	if(mIsPlayerAlive == false){
		player_death_reset(gClock);
		return;
		
	}
}

void Game::player_death_reset(sf::Clock& gClock){
	
	sf::Clock aClock;
	sf::Time frameTime = gClock.restart() ;
	while (aClock.getElapsedTime().asSeconds() < 3)
	{
		mWindow.clear();
		update_enemies(frameTime);
		render_enemies(false);
		mWindow.draw(tDeathText);
		mWindow.display();
		frameTime = gClock.restart();
		
	}
	gameStop = true;
	pLevel = 1;
	destroy_all_asteroids();
	tScoreNumber.setString(std::to_string(pScore));
	tScoreNumber.setOrigin(tScoreNumber.getLocalBounds().width/2,tScoreNumber.getLocalBounds().height/2);
	tScoreNumber.setPosition(300,330);
	pScore = 0;

}

void Game::player_level_reset(sf::Clock& gClock){
	sf::Clock  aClock; //"animation clock"
	sf::Time frameTime = gClock.restart();
	while(aClock.getElapsedTime().asSeconds() < 3){
		get_input();
		update_logic(frameTime);
		mWindow.clear(sf::Color::Black);
		render_missiles(false);
		mWindow.draw(mPlayer.get_sprite());
		mWindow.draw(tLiveScore);
		mWindow.draw(tLiveScoreText);
		mWindow.draw(tLevelClearText);
		mWindow.display();
		
		frameTime = gClock.restart();
	}
	mWindow.clear();
	destroy_all_asteroids();
	pLevel ++;
	mPlayer.reset();
	init_level_enemies(pLevel);


}













