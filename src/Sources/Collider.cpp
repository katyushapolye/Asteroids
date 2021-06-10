#include "Headers/Collider.h"
#include <iostream>

Collider::Collider(float initRadius, float cInitX, float cInitY, ColliderTag initTag) :
	cColliderVisual(initRadius),
	cTag(),
	cColliderX(cInitX),
	cColliderY(cInitY),
	cRadius(initRadius)

{
	cTag = initTag;
	cColliderVisual.setOrigin(initRadius, initRadius);
	cColliderVisual.setFillColor(sf::Color::Transparent);
	cColliderVisual.setOutlineColor(sf::Color::Red);
	cColliderVisual.setOutlineThickness(1.f);
	update_collider_position(cColliderX, cColliderY);
}

sf::CircleShape& Collider::get_collider_visual()
{
	return cColliderVisual;
}
void Collider::update_collider_position(float nX, float nY)
{
	cColliderX = nX;
	cColliderY = nY;
	cColliderVisual.setPosition(nX, nY);
}

bool Collider::check_colision(Collider& sCollision)
{
	Point sColliderCenter(sCollision.cColliderX, sCollision.cColliderY);
	float sCollisionRadius = sCollision.cRadius;
	bool IsColiding = calculate_colision(sColliderCenter, sCollisionRadius);
	if (IsColiding)
	{	//USE A FLAG TO AVOID MULTIPLE ENTERS
		this->on_collision_enter(sCollision.get_colider_tag());
		sCollision.on_collision_enter(this->get_colider_tag());
		return true;
	}
	else
	{
		//USE A FLAG TO AVOID MULTIPLE RESETS
		this->collision_state_reset(sCollision.get_colider_tag()); //Recieve the collisiontag
		sCollision.collision_state_reset(this->get_colider_tag()); //Pass my collidertag to the collision
		return false;
	}
}

void Collider::on_collision_enter(ColliderTag cTag)
{
	if(cTag ==  3){return;}
	cColliderVisual.setOutlineColor(sf::Color::Green);
	return;
}
void Collider::collision_state_reset(ColliderTag cTag)
{
	if(cTag ==  3){return;}
	cColliderVisual.setOutlineColor(sf::Color::Red);
	return;
}

bool Collider::calculate_colision(Point sCollisionPosition, float sCollisionRadius)
{
	float distance = sqrt(pow(abs(this->cColliderX - sCollisionPosition.X), 2) + pow(abs(this->cColliderY - sCollisionPosition.Y), 2));
	if (distance < sCollisionRadius + this->cRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ColliderTag Collider::get_colider_tag()
{
	return cTag;
}
