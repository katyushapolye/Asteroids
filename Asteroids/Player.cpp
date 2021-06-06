#include "Player.h"
#include <iostream>
const float PI = 3.1415;

Player::Player():
	pTexture(),
	pPositionX(),
	pPositionY(),
	pVelocity(100),
	pSprite(),
	pIsMovingDown(),
	pIsMovingUp(),
	pIsTurningLeft(),
	pIsTurningRight(),
	pTimeSinceLastFrame(),
	Collider(22,0,0)
{
	pTexture.loadFromFile("Assets/Player/gShip.png");
	pSprite.setTexture(pTexture);
	pSprite.setOrigin(25, 25);
	pSprite.setScale(1, 1);
	this->set_rotation(0);
	this->set_position(300, 300);
	this->update_collider_position(pPositionX, pPositionY);

}


sf::Sprite& Player::get_sprite() {
	return pSprite;
}

void Player::set_position(float x,float y){
	pPositionX = x;
	pPositionY = y;
	pSprite.setPosition(sf::Vector2<float>(pPositionX,pPositionY));
}

sf::Vector2<float> Player::get_position() {
	sf::Vector2<float> pPosition(pPositionX, pPositionY);
	return pPosition;
}

void Player::change_position(float offSetX, float offSetY) {
	pPositionX = pPositionX + offSetX;
	pPositionY = pPositionY + offSetY;
	pSprite.move(offSetX, offSetY);
}

void Player::change_position(sf::Vector2<float> offSetVector) {
	pPositionX = pPositionX + offSetVector.x;
	pPositionY = pPositionY + offSetVector.y;

	pSprite.move(offSetVector);
}

float Player::get_rotation() {

	return pAngle;
}

void Player::set_rotation(float angle) {
	
	if (angle >= 360 || angle <= -360) {
		int newAngle = (int)angle % 360;
		pAngle = newAngle;
		
	}
	else {
		pAngle = angle;
		pSprite.setRotation(pAngle);
	}
	


}

void Player::change_rotation(float angleOffSet) {
	pSprite.rotate(angleOffSet);
	pAngle = pSprite.getRotation();

}

void Player::send_input(sf::Keyboard::Key pKey,bool pIspressed) {
	handle_input(pKey, pIspressed); //Maybe send the gameclock aswell, for frame independent movement
}

void Player::handle_input(sf::Keyboard::Key pKey, bool pIspressed) {
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

sf::Vector2<float> Player::calculate_velocity_resultant() {
	sf::Vector2<float> vResultant{ pVelocity * sin((pAngle*PI)/180),
								  (pVelocity* cos((pAngle*PI)/180)) };
	return vResultant;
}

void Player::update_player(sf::Time frameTime) {
	sf::Vector2<float> pVelocity = calculate_velocity_resultant();
	float deltaTime = frameTime.asSeconds();
	std::cout << get_rotation() << std::endl;
	std::cout << "VELOCITY_X = " << pVelocity.x << std::endl;
	std::cout << "VELOCITY_Y = " << pVelocity.y << std::endl;
	if (pIsMovingUp) {
		change_position(pVelocity.x*deltaTime,-pVelocity.y * deltaTime);
	}
	if (pIsMovingDown) {
		change_position(-pVelocity.x * deltaTime,+pVelocity.y * deltaTime);
	}
	if (pIsTurningLeft) {
		change_rotation(-50* frameTime.asSeconds());
	}
	if (pIsTurningRight) {
		change_rotation(50 * frameTime.asSeconds());
	}
	update_collider_position(pPositionX, pPositionY);

	
}

//overrides the oncollision parent class method

void Player::on_collision_enter(){
	Collider::on_collision_enter();

	return;

}

void Player::on_collision_exit() {
	Collider::on_collision_exit();
	return;
}




