#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <math.h>

class Collider: sf::NonCopyable
{
public:
	Collider(float cRadius,float cInitX,float cInitY);
	bool check_colision(Collider& cColision);


	void update_collider_position(float nX, float xY);

	sf::CircleShape& get_collider_visual();


protected:
	
	bool calculate_colision(Point sCollisionPosition, float sCollisionRadius);
	void virtual on_collision_enter();

	void virtual on_collision_exit();

	sf::CircleShape cColliderVisual;
	float cColliderX;
	float cColliderY;
	float cRadius;



};