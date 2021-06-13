#pragma once
#include <SFML/Audio.hpp>
#include "Utility.h"
#include <map>

class SoundManager{
    public:
    static void                                         load_all_sounds();
        
    static sf::SoundBuffer&                             get_sound(SoundID sID);

    private:
    static inline std::map<SoundID,sf::SoundBuffer>        sMap;
    static void                                     load_sound(SoundID sID);


};