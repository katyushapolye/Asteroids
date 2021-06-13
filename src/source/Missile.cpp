#include "headers/Missile.h"
#include <iostream>
const float PI = 3.1415;

Missile::Missile(float initX,float initY,float initAngle
                ,sf::Texture& mTexture):
            mSprite(),
            mNeedsDestruction(false),
            mX(initY),
            mY(initY),
            mAngle(initAngle),
            mVelocity(calculate_velocity_resultant()),
            mLifeClock(),
            Collider(10,initX,initY,MissileCollider)

{

    mSprite.setTexture(mTexture);
    mSprite.setRotation(45);
    mSprite.setOrigin(3.5,18.5);
    mSprite.setScale(0.75,0.75);


    set_position(initX,initY);
    set_rotation(initAngle);

}

void Missile::on_collision(ColliderTag cTag){
    if(cTag == EnemyCollider){
        mNeedsDestruction = true;
        return;
    }
}


sf::Sprite& Missile::get_sprite(){
    return mSprite;
}

void Missile::set_position(float x,float y){
    mX = x;
    mY = y;
    mSprite.setPosition(mX,mY);

}

sf::Time Missile::get_missile_lifetime(){
    return mLifeClock.getElapsedTime();
}


void Missile::set_rotation(float sAngle){
    mAngle = sAngle;
    mSprite.setRotation(mAngle);

}
Point Missile::get_position(){
    return Point(mX,mY);
}

void Missile::change_position(float offsetX,float offsetY){
    mX = mX + offsetX;
    mY = mY+ offsetY;
    mSprite.move(offsetX,offsetY);
}

void Missile::change_position(sf::Vector2<float> offset){
    mX = mX + offset.x;
    mY = mY+ offset.y;
    mSprite.move(offset);
}



sf::Vector2<float> Missile::calculate_velocity_resultant(){
    sf::Vector2<float> vResultant{500 * sin((mAngle * PI) / 180),
								  (500 * -cos((mAngle * PI) / 180))}; //need the minus cos because of how rotation is calculated on the sfml sprite
	return vResultant;
}


void Missile::check_general_missile_bounds(){
    check_x_missile_bounds();
    check_y_missile_bounds();
}

void Missile::check_x_missile_bounds(){
    if(mX > mScreenX + 10){
        set_position(-5,mY);

    }
    if(mX < -10){
        set_position(mScreenX+5,mY);
    }
}

void Missile::check_y_missile_bounds(){
    if(mY > mScreenY + 10){
        set_position(mX,5);
    }
    if(mY < -10){
        set_position(mX,mScreenY + 5);
    }
}
void Missile::update_missile(sf::Time frameTime){
    check_general_missile_bounds();
    change_position(mVelocity*frameTime.asSeconds());
    update_collider_position(mX,mY);


}