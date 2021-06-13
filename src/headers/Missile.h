#pragma once
#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
#include "Collider.h"

class Missile : public Collider
{
    public:
    Missile(float initX,float initY,float initAngle,
            sf::Texture& mTexture);
    sf::Sprite&                                     get_sprite();
    sf::Time                                        get_missile_lifetime();  
    void                                            update_missile(sf::Time frameTime); 
    bool                                            mNeedsDestruction;
   
    private:
    void                                            set_position(float x, float y);
    void                                            set_rotation(float sAngle);
    Point                                           get_position();
    void                                            change_position(float offsetX,float offsetY);
    void                                            change_position(sf::Vector2<float> offset);
    sf::Vector2<float>                              calculate_velocity_resultant();

    void                                            on_collision(ColliderTag cTag) override;


    //void change_position();

    void                                            check_general_missile_bounds();
    void                                            check_x_missile_bounds();
    void                                            check_y_missile_bounds();

    //privfunction

    private:
    sf::Sprite                                      mSprite;
    float                                           mX;
    float                                           mY;
    float                                           mAngle;
    sf::Vector2<float>                              mVelocity;
    sf::Clock                                       mLifeClock;




};



