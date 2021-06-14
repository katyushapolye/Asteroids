#include "headers/Player.h"
#include <math.h>
#include <iostream>
const float PI = 3.1415;

Player::Player(sf::Texture& pTexture,sf::Texture& mInitTexture): 
				Collider(20, 0, 0, PlayerCollider),
				pSprite(),
				mTexture(mInitTexture),
				pMissiles(),
				pMissileLauchSound(),
				pMissileCooldown(),
				pPositionX(),
				pPositionY(),
				pIsMovingUp(false),
				pIsMovingDown(false),
				pIsTurningLeft(false),
				pIsTurningRight(false),
				pShoot(false),
				pTimeSinceLastFrame(),
				pForce(0),
				pAceleration(0),
				pXForce(0),
				pYForce(0),
				pMass(0.005)

{
	pMissileLauchSound.setBuffer(SoundManager::get_sound(MissileSound));
	pMissileLauchSound.setVolume(50);
	pSprite.setTexture(pTexture);
	pSprite.setOrigin(25, 30);
	pSprite.setScale(1, 1);
	this->set_rotation(0);
	this->set_position(300, 300);
	this->update_collider_position(pPositionX, pPositionY);
}

void Player::reset(){
	set_position(300,300);
	set_rotation(0);
	pShoot = false;
	pIsMovingDown = false;
	pIsMovingUp = false;
	pIsTurningLeft = false;
	pIsTurningRight = false;
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

std::vector<Missile>& Player::get_all_active_missiles(){
	return pMissiles;
}

void Player::change_rotation(float angleOffSet)
{
	pSprite.rotate(angleOffSet);
	pAngle = pSprite.getRotation();
}

bool Player::check_player_cooldown(){
	if(pMissileCooldown.getElapsedTime().asSeconds()>0.5f){
		return true;
	}
	return false;
}

void Player::player_shoot(){
	if( check_player_cooldown()){
		pMissileCooldown.restart();
		Missile temp(pPositionX,pPositionY,pAngle,mTexture);
		pMissileLauchSound.play();
		pMissiles.push_back(temp);

	}
}

void Player::update_missiles(sf::Time frameTime){
	
	for (size_t i = 0; i < pMissiles.size(); i++)
	{
		pMissiles.at(i).update_missile(frameTime);
		if(pMissiles.at(i).get_missile_lifetime().asSeconds() > 1.0f || pMissiles.at(i).mNeedsDestruction == true){
			pMissiles.erase(pMissiles.begin()+i);

		}
	}
	


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
	case sf::Keyboard::Left :
		pIsTurningLeft = pIspressed;
		break;
	case sf::Keyboard::Right:
		pIsTurningRight = pIspressed;
		break;
	case sf::Keyboard::Down:
		pIsMovingDown = pIspressed;
		break;
	case sf::Keyboard::Up:
		pIsMovingUp = pIspressed;
		break;
	case sf::Keyboard::Space:
		pShoot = pIspressed;
		break;	
	default:
		break;
	}
}


//reset position

void Player::update_player(sf::Time frameTime)
{


	update_momentum();
	add_force();
	float deltaTime = frameTime.asSeconds();

	change_position( (pXAceleration* (frameTime.asSeconds()*frameTime.asSeconds()))/2,
					  (-pYAceleration* (frameTime.asSeconds()*frameTime.asSeconds()))/2
	  );
	if (pIsTurningLeft)
	{
		change_rotation(-100 * frameTime.asSeconds());
	}
	if (pIsTurningRight)
	{
		change_rotation(100 * frameTime.asSeconds());
	}
	if(pShoot){
		player_shoot();

	}
	check_general_player_bounds();
	update_collider_position(pPositionX, pPositionY);
	update_missiles(frameTime);
}

//overrides the oncollision parent class method

void Player::on_collision(ColliderTag cTag)
{	
	Collider::on_collision(cTag);
}


void Player::update_momentum(){

	//Natural loss of momentum
	if((pIsMovingDown == false && pIsMovingUp == false && pForce != 0) || (pIsMovingDown == true && pIsMovingUp == true && pForce != 0) ){
		if(pForce > 0){
			pForce -= 1;
		}
		else if(pForce < 0){
			pForce += 1;
		}		
	}
	

	//decompose Velocity Vector;
	pXForce =   pForce * sin((pAngle * PI) / 180);
	pYForce =   pForce * cos((pAngle * PI) / 180);
	//Set y and x acceleration
	pXAceleration = pXForce/pMass;
	pYAceleration = pYForce/pMass;
	//Second Newton's Law F = m * a, and a/2 *(t²) = d;
}

void Player::add_force(){
	if(pIsMovingUp == true && pForce <= 100){
		pForce +=5;
		if(pForce > 100){
			pForce = 100;
		}

	}
	if(pIsMovingDown == true && pForce >= -100){
		pForce -=5 ;
		if(pForce < -100){
			pForce = -100;
		}

	}	
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
