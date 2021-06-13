#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <math.h>

class Collider
{
public:
	Collider(float cRadius,float cInitX,float cInitY,ColliderTag cInitTag);
	bool										check_colision(Collider& cColision);
	
	ColliderTag									get_colider_tag();
	sf::CircleShape&							get_collider_visual();


protected:
	void										update_collider_position(float nX, float xY);

	bool										calculate_colision(Point sCollisionPosition, float sCollisionRadius);
	void virtual								on_collision(ColliderTag cTag);
	




	// bool cNeedReset;


	sf::CircleShape								cColliderVisual;
	ColliderTag									cTag;
	float										cColliderX;
	float										cColliderY;
	float										cRadius;



};