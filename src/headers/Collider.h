#pragma once
#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <math.h>

class Collider
{
public:
	Collider(float cRadius,float cInitX,float cInitY,ColliderTag cInitTag);
	bool										check_colision(Collider& cColision);
	void										update_collider_position(float nX, float xY);
	ColliderTag									get_colider_tag();
	sf::CircleShape&							get_collider_visual();


protected:

	bool										calculate_colision(Point sCollisionPosition, float sCollisionRadius);
	void virtual								on_collision_enter(ColliderTag cTag);
	void virtual								collision_state_reset(ColliderTag Tag); //State Reset




	// bool cNeedReset;


	sf::CircleShape								cColliderVisual;
	ColliderTag									cTag;
	float										cColliderX;
	float										cColliderY;
	float										cRadius;



};