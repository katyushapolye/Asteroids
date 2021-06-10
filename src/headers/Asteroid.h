#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.h"
class Asteroid : public Collider
{
public:
	Asteroid(float initX, float initY, float initRadius,float initVelocity,float initAngle);
	//~Asteroid();
	sf::Sprite& 		get_sprite();
	float               get_position_debug();
	void 				update_asteroid(sf::Time frameTime);



	//~Asteroid();

private:
	void				set_position(float x, float y);
	Point				get_position();
	void				change_position(float offSetX, float offSetY);
	void				change_position(sf::Vector2<float> offSet);
	sf::Vector2<float>  calculate_velocity_resultant(float velocity);

	void 				check_asteroid_general_bounds();
	void 				check_asteroid_bounds_x();
	void 				check_asteroid_bounds_y();



	//void on_collision_enter(ColliderTag cTag) override;
	//void on_collision_exit(ColliderTag cTag) override;



	sf::Sprite 					aSprite;
	sf::Texture 				aTexture;
	sf::Text              		aDebugText;



	float 						aPositionX;
	float 						aPositionY;
	float 						aRadius;
	float 						aAngle;
	sf::Vector2<float> 			aVelocity;

};




