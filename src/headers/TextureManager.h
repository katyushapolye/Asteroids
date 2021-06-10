#pragma once
#include <SFML/Graphics.hpp>
#include <headers/Utility.h>

class TextureManager
{
	public:
	TextureManager();
	sf::Texture& 									get_texture(TextureID tID);

	private:
	void 											set_texture(TextureID tID);


	private:
	std::map<TextureID,sf::Texture> 				tMap;



};

