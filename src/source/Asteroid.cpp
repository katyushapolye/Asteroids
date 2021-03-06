#include "headers/Asteroid.h"
#include <iostream>

const float PI = 3.1415;


Asteroid::Asteroid(float initX, float initY, float initRadius,
				   float initVelocity,float initAngle,sf::Texture& aTexture):
		Collider(initRadius - (18 * (initRadius / 60)), 0, 0, EnemyCollider),
		aSprite(),
		aPositionX(initX),
		aPositionY(initY),
		aRadius(initRadius - 10),
		aAngle(initAngle),
		aVelocity(calculate_velocity_resultant(initVelocity))

{
	aSprite.setTexture(aTexture);

	//Setting Visuals
	float scale = initRadius / 60;
	aSprite.setOrigin(44.5, 49);
	aSprite.setScale(scale, scale);
	aSprite.setRotation(initAngle);
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

float Asteroid::get_radius(){
	return aRadius;
}

float Asteroid::get_aproximate_velocity(){
	return aVelocity.x + aVelocity.y;
}

float Asteroid::get_angle(){
	return aAngle;
}

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
	check_asteroid_general_bounds();
	change_position(aVelocity*frameTime.asSeconds());
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













