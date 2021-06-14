#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Collider.h"
#include "Missile.h"
#include "SoundManager.h"



class Player : public Collider //derives from collider and takes its public function as well as the atributes, if not public, then all would be private, and only the class could acess
{
public:
	Player(sf::Texture& pTexture,sf::Texture& mInitTexture);
	sf::Sprite&                     get_sprite();
	std::vector<Missile>&           get_all_active_missiles();
	void                            send_input(sf::Keyboard::Key pKey, bool sIsPressed);
	void                            update_player(sf::Time frameTime);
	void							reset();






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

	//Physics
	void 							 update_momentum();
	void 						     add_force();



	bool                             check_player_cooldown();
	void                             player_shoot();
	void 							 check_missiles_life();
	void 							 update_missiles(sf::Time frameTime);

	sf::Vector2<float>               calculate_velocity_resultant();

	void                             on_collision(ColliderTag cTag) override;
	







private:
	sf::Sprite 						pSprite;
	sf::Texture&					mTexture;
	std::vector<Missile>            pMissiles;
	sf::Sound                       pMissileLauchSound;
	sf::Clock 						pMissileCooldown;
	float							pPositionX;
	float							pPositionY;
	float							pAngle;


	//Physics
	int								pForce;
	float 							pAceleration;

	float 							pMass;
	float 							pXForce;
	float 							pYForce;
	float 							pXAceleration;
	float							pYAceleration;				


	bool						    pIsMovingUp;
	bool						    pIsMovingDown;
	bool							pIsTurningLeft;
	bool							pIsTurningRight;
	bool                            pShoot;

	sf::Time						pTimeSinceLastFrame;




};



