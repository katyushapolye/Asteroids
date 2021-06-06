#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Collider.h"



class Player : public Collider //derives from collider and takes its public function as well as the atributes, if not public, then all would be private, and only the class could acess
{
public:
	Player();
	sf::Sprite&                     get_sprite();
	void                            send_input(sf::Keyboard::Key pKey, bool sIsPressed);
	void                            update_player(sf::Time frameTime);






private:
	void                             handle_input(sf::Keyboard::Key keycode, bool IsPressed);

	void                             set_position(float x, float y);
	sf::Vector2<float>               get_position();
	void                             change_position(float offSetX,float offSetY); 
	void                             change_position(sf::Vector2<float> offsetVector);

	float                            get_rotation();
	void                             set_rotation(float angle);
	void                             change_rotation(float angleOffSet);

	sf::Vector2<float>               calculate_velocity_resultant();

	void                             on_collision_enter() override;
	void							 on_collision_exit() override;





private:
	sf::Sprite pSprite;
	sf::Texture pTexture;
	float pPositionX;
	float pPositionY;
	float pVelocity;
	float pAngle;

	bool pIsMovingUp;
	bool pIsMovingDown;
	bool pIsTurningLeft;
	bool pIsTurningRight;

	sf::Time pTimeSinceLastFrame;




};



