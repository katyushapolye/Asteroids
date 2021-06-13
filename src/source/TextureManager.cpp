#include <headers/TextureManager.h>

TextureManager::TextureManager():
	tMap()
{
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		set_texture(TextureID(i));
	}

}
void TextureManager::set_texture(TextureID tID){
	sf::Texture tempTexture;
	switch (tID)
	{
	case PlayerTexture:
		tempTexture.loadFromFile("Assets/Player/gShip.png");
		//add check to avoid multiple textures
		tMap.insert(std::pair<TextureID,sf::Texture>(PlayerTexture,tempTexture));
		break;

	case EnemyTexture:
		tempTexture.loadFromFile("Assets/Asteroid/gAsteroid.png");
		tMap.insert(std::pair<TextureID,sf::Texture>(EnemyTexture,tempTexture));
		break;

	case MissileTexture:
		tempTexture.loadFromFile("Assets/Missile/gMissile.png");
		tMap.insert(std::pair<TextureID,sf::Texture>(MissileTexture,tempTexture));
		break;
	default:
		printf("TEXTURE NOT FOUND -- ERROR CODE 4");
		break;
	}
	return;

}
sf::Texture& TextureManager::get_texture(TextureID tID){
	std::map<TextureID,sf::Texture>::iterator it;
	it = tMap.find(tID);
	return it->second;


}