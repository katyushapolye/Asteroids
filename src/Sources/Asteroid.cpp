#include "Headers/Asteroid.h"
#include <iostream>

const float PI = 3.1415;


Asteroid::Asteroid(float initX, float initY, float initRadius,float initVelocity,float initAngle):
		Collider(initRadius - (18 * (initRadius / 60)), 0, 0, EnemyCollider),
		aSprite(),
		aTexture(),
		aSoundDestroy(),
		aSoundDestroyBuffer(),
		aPositionX(initX),
		aPositionY(initY),
		aRadius(initRadius - 10),
		aAngle(initAngle),
		aVelocity(calculate_velocity_resultant(initVelocity))

{
	//Loading Resources
	if ((aTexture.loadFromFile("Assets/Asteroid/gAsteroid.png")))
	{
		std::cout << "Failed To Load Texture";
	}

	aTexture.loadFromFile("Assets/Asteroid/gAsteroid.png");
	aSprite.setTexture(aTexture);
	aSoundDestroyBuffer.loadFromFile("Assets/Asteroid/aExplosion.ogg"); //Make one static sound buffer
	aSoundDestroy.setBuffer(aSoundDestroyBuffer);
	aSoundDestroy.setLoop(false);

	//Setting Variables


	//Setting Visuals
	float scale = initRadius / 60;
	aSprite.setOrigin(44.5, 49);
	aSprite.setScale(scale, scale);
	this->set_position(aPositionX, aPositionY);
	this->update_collider_position(aPositionX, aPositionY);
}

sf::Vector2<float>  Asteroid::calculate_velocity_resultant(float velocity){

	sf::Vector2<float> vResultant{velocity * sin((aAngle * PI) / 180),
								  (velocity * cos((aAngle * PI) / 180))};
	return vResultant;
}

void Asteroid::set_position(float x, float y)
{
	aPositionX = x;
	aPositionY = y;
	aSprite.setPosition(aPositionX, aPositionY);
}

sf::Sprite& Asteroid::get_sprite()
{
	return aSprite;
}

Point Asteroid::get_position()
{
	return Point(aPositionX, aPositionY);
}
//reset position on edge
void Asteroid::change_position(sf::Vector2<float> offSet)
{
	aPositionX = aPositionX + offSet.x;
	aPositionY = aPositionY + offSet.y;
	aSprite.move(offSet);
}

void Asteroid::change_position(float offSetX, float offSetY)
{
	aPositionX = aPositionX + offSetX;
	aPositionY = aPositionY + offSetX;
	aSprite.move(offSetX, offSetY);
}

void Asteroid::update_asteroid(sf::Time frameTime)
{
	change_position(aVelocity*frameTime.asSeconds());
	check_asteroid_general_bounds();
	update_collider_position(aPositionX, aPositionY);
}

void Asteroid::check_asteroid_general_bounds(){
	check_asteroid_bounds_x();
	check_asteroid_bounds_y();
	return;


}
void Asteroid::check_asteroid_bounds_x(){
	if(aPositionX > mScreenX + aRadius + 20){
		set_position(-aRadius-15,aPositionY);
	}
	if(aPositionX< -20-aRadius){
		set_position(mScreenX + aRadius +15,aPositionY);
	}

}
void Asteroid::check_asteroid_bounds_y(){
	if(aPositionY > mScreenY + aRadius+30){
		set_position(aPositionX,-15-aRadius);
	}
	if(aPositionY< -20-aRadius){
		set_position(aPositionX,mScreenY + aRadius +15);
	}

}




void Asteroid::play_destruction_sound(){
	aSoundDestroy.setPlayingOffset(sf::seconds(0.2));
	aSoundDestroy.play();

}









