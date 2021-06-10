#include <headers/Game.h>
#include <headers/Player.h>
#include <filesystem>
#include <iostream>
Game::Game() : mWindow(sf::VideoMode(mScreenX, mScreenY), "Asteroid"),
			   mPlayer(),
			   mDebugAsteroid(150,150,120,45,90)



{

	mWindow.clear(sf::Color::Black);

}

void Game::run()
{
	sf::Clock gClock;
	sf::Time timeSinceLastFrame;
	while (mWindow.isOpen())
	{
		timeSinceLastFrame = gClock.restart();
		//Note that, react to input and update movement entc, must be not in the same loop
		get_input();
		update_logic(timeSinceLastFrame);
		update_screen();
	}
}





void Game::get_input()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) //Returns a "list" and iterator to ALL events, must react to them all, and then update the logic
	{
		/*The input must be set using keyflags, to handle multiple keystrok
		es at the same time, the movement is handled later at the logic update when t
		e keyflags are set
		Switch to Switch, too much events*/
		if (event.type == sf::Event::Closed)
		{
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
//Right now, we are rendering everything directly to the window, not another render target, we might change that later

void Game::update_screen()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(mPlayer.get_sprite());
	mWindow.draw(mPlayer.get_collider_visual());
	mWindow.draw(mDebugAsteroid.get_sprite());
	mWindow.draw(mDebugAsteroid.get_collider_visual());

	mWindow.display();
}

void Game::update_logic(sf::Time frameTime)

{

	mPlayer.update_player(frameTime);
	mDebugAsteroid.update_asteroid(frameTime);
	mPlayer.check_colision(mDebugAsteroid);

	//Check all colision;
}