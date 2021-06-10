#include "headers/Player.h"
#include <iostream>
const float PI = 3.1415;

Player::Player(sf::Texture& pTexture) : 
				Collider(20, 0, 0, PlayerCollider),
				pSprite(),
				pPositionX(),
				pPositionY(),
				pVelocity(300),
				pIsMovingUp(),
				pIsMovingDown(),
				pIsTurningLeft(),
				pIsTurningRight(),
				pTimeSinceLastFrame()

{
	pSprite.setTexture(pTexture);
	pSprite.setOrigin(25, 30);
	pSprite.setScale(1, 1);
	this->set_rotation(0);
	this->set_position(300, 300);
	this->update_collider_position(pPositionX, pPositionY);
}

sf::Sprite &Player::get_sprite()
{
	return pSprite;
}

void Player::set_position(float x, float y)
{
	pPositionX = x;
	pPositionY = y;
	pSprite.setPosition(sf::Vector2<float>(pPositionX, pPositionY));
}

Point Player::get_position()
{
	Point pPosition(pPositionX, pPositionY);
	return pPosition;
}

void Player::change_position(float offSetX, float offSetY)
{
	pPositionX = pPositionX + offSetX;
	pPositionY = pPositionY + offSetY;
	pSprite.move(offSetX, offSetY);
}

void Player::change_position(sf::Vector2<float> offSetVector)
{
	pPositionX = pPositionX + offSetVector.x;
	pPositionY = pPositionY + offSetVector.y;

	pSprite.move(offSetVector);
}

float Player::get_rotation()
{

	return pAngle;
}

void Player::set_rotation(float angle)
{

	if (angle >= 360 || angle <= -360)
	{
		int newAngle = (int)angle % 360;
		pAngle = newAngle;
	}
	else
	{
		pAngle = angle;
		pSprite.setRotation(pAngle);
	}
}

void Player::change_rotation(float angleOffSet)
{
	pSprite.rotate(angleOffSet);
	pAngle = pSprite.getRotation();
}

void Player::send_input(sf::Keyboard::Key pKey, bool pIspressed)
{
	handle_input(pKey, pIspressed); //Maybe send the gameclock aswell, for frame independent movement
}

void Player::handle_input(sf::Keyboard::Key pKey, bool pIspressed)
{
	switch (pKey)
	{
		/*Set flags for key pressed and released, then moving the player,need to think more on how to handle multiple keys*/
	case sf::Keyboard::A:
		pIsTurningLeft = pIspressed;
		break;
	case sf::Keyboard::D:
		pIsTurningRight = pIspressed;
		break;
	case sf::Keyboard::S:
		pIsMovingDown = pIspressed;
		break;
	case sf::Keyboard::W:
		pIsMovingUp = pIspressed;
		break;
	default:
		break;
	}
}

sf::Vector2<float> Player::calculate_velocity_resultant()
{
	sf::Vector2<float> vResultant{pVelocity * sin((pAngle * PI) / 180),
								  (pVelocity * cos((pAngle * PI) / 180))};
	return vResultant;
}
//reset position

void Player::update_player(sf::Time frameTime)
{
	sf::Vector2<float> pVelocity = calculate_velocity_resultant();
	float deltaTime = frameTime.asSeconds();
	if (pIsMovingUp)
	{
		change_position(pVelocity.x * deltaTime, -pVelocity.y * deltaTime);
	}
	if (pIsMovingDown)
	{
		change_position(-pVelocity.x * deltaTime, +pVelocity.y * deltaTime);
	}
	if (pIsTurningLeft)
	{
		change_rotation(-100 * frameTime.asSeconds());
	}
	if (pIsTurningRight)
	{
		change_rotation(100 * frameTime.asSeconds());
	}
	check_general_player_bounds();
	update_collider_position(pPositionX, pPositionY);
}

//overrides the oncollision parent class method

void Player::on_collision_enter(ColliderTag cTag)
{
	Collider::on_collision_enter(cTag);
	if (cTag == EnemyCollider)
	{
		return;
	}
	else
	{
		return;
	}
}

void Player::collision_state_reset(ColliderTag cTag)
{
	Collider::collision_state_reset(cTag);
	return;
}

void Player::check_general_player_bounds()
{
	check_player_bounds_x();
	check_player_bounds_y();
	return;
}

void Player::check_player_bounds_x(){
	if(pPositionX > mScreenX + 30){
		set_position(-15,pPositionY);
	}
	if(pPositionX < -30){
		set_position(mScreenX + 15,pPositionY);
	}
}

void Player::check_player_bounds_y(){
	if(pPositionY > mScreenY + 30){
		set_position(pPositionX,-15);
	}
	if(pPositionY < -30){
		set_position(pPositionX,mScreenY + 15);
	}


}
