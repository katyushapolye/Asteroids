
#include <headers/SoundManager.h>


void SoundManager::load_all_sounds(){
    SoundManager::sMap = {};
    for (size_t i = 0; i < MAX_SOUNDS; i++)
    {
        load_sound(SoundID(i));
    }
    };

void SoundManager::load_sound(SoundID sID){
    sf::SoundBuffer tempS;
    switch (sID)
    {
    case PlayerDeathSound:
        tempS.loadFromFile("Assets/Sounds/pExplosion.ogg");
        SoundManager::sMap.insert(std::pair<SoundID,sf::SoundBuffer>(PlayerDeathSound,tempS));
        break;
    case MissileSound:
        tempS.loadFromFile("Assets/Sounds/pMissile.ogg");
        SoundManager::sMap.insert(std::pair<SoundID,sf::SoundBuffer>(MissileSound,tempS));
        break;
    case AsteroidExplosionSound:
        tempS.loadFromFile("Assets/Sounds/aExplosion.ogg");
        SoundManager::sMap.insert(std::pair<SoundID,sf::SoundBuffer>(AsteroidExplosionSound,tempS));
        break;    
    default:
        break;
    }


}

sf::SoundBuffer&  SoundManager::get_sound(SoundID sID){
    
    std::map<SoundID,sf::SoundBuffer>::iterator it;
    it = SoundManager::sMap.find(sID);
    return it->second;


}



