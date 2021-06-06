#include "Collider.h"
#include <iostream>

Collider::Collider(float initRadius, float cInitX, float cInitY) :
	cRadius(initRadius),
	cColliderX(cInitX),
	cColliderY(cInitY),
	cColliderVisual(initRadius)
{
	cColliderVisual.setOrigin(initRadius,initRadius);
	cColliderVisual.setFillColor(sf::Color::Transparent);
	cColliderVisual.setOutlineColor(sf::Color::Red);
	cColliderVisual.setOutlineThickness(1.f);
	update_collider_position(cColliderX, cColliderY);
	

}

sf::CircleShape& Collider::get_collider_visual() {
	return cColliderVisual;
}
void Collider::update_collider_position(float nX, float nY) {
	cColliderX = nX;
	cColliderY = nY;
	cColliderVisual.setPosition(nX, nY);
}


bool Collider::check_colision(Collider& sCollision) {
	Point sColliderCenter;
	float sCollisionRadius = sCollision.cRadius;
	sColliderCenter.X = sCollision.cColliderX;
	sColliderCenter.Y = sCollision.cColliderY;
	bool IsColiding = calculate_colision(sColliderCenter, sCollisionRadius);
	if (IsColiding) {
		this->on_collision_enter();
		sCollision.on_collision_enter();
		return true;
	}
	else {
		this->on_collision_exit();
		sCollision.on_collision_exit();
		return false;
	}

	return true;

}

void Collider::on_collision_enter() {
	cColliderVisual.setOutlineColor(sf::Color::Green);
	return;
}
void Collider::on_collision_exit() {
	cColliderVisual.setOutlineColor(sf::Color::Red);
	return;
}



bool Collider::calculate_colision( Point sCollisionPosition,float sCollisionRadius){
	float distance = sqrt(pow(abs(this->cColliderX - sCollisionPosition.X), 2) + pow(abs(this->cColliderY - sCollisionPosition.Y), 2));
	std::cout << "DISTANCE BETWEEN TWO COLLIDERS: "<< distance << std::endl;
	if (distance > sCollisionRadius + this->cRadius) {
		return false;
	}
	else {
		return true;

	}


}
