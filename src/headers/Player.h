#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Collider.h"



class Player : public Collider //derives from collider and takes its public function as well as the atributes, if not public, then all would be private, and only the class could acess
{
public:
	Player(sf::Texture& pTexture);
	sf::Sprite&                     get_sprite();
	void                            send_input(sf::Keyboard::Key pKey, bool sIsPressed);
	void                            update_player(sf::Time frameTime);






private:
	void                             handle_input(sf::Keyboard::Key keycode, bool IsPressed);

	void                             set_position(float x, float y);
	Point			                 get_position();
	void                             change_position(float offSetX,float offSetY);
	void                             change_position(sf::Vector2<float> offsetVector);

	float                            get_rotation();
	void                             set_rotation(float angle);
	void                             change_rotation(float angleOffSet);
	void							 check_general_player_bounds();
	void							 check_player_bounds_x();
	void 							 check_player_bounds_y();

	sf::Vector2<float>               calculate_velocity_resultant();

	void                             on_collision_enter(ColliderTag cTag) override;
	void							 collision_state_reset(ColliderTag cTag) override;





private:
	sf::                            Sprite pSprite;
	float							pPositionX;
	float							pPositionY;
	float							pVelocity;
	float							pAngle;

	bool						    pIsMovingUp;
	bool						    pIsMovingDown;
	bool							pIsTurningLeft;
	bool							pIsTurningRight;

	sf::Time						pTimeSinceLastFrame;




};



