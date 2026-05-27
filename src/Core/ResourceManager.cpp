#include "ResourceManager.h"

void ResourceManager::loadFont(const std::string& id, const std::string& path)
{
	sf::Font font;
	//font.loadFromFile(path);
    if(font.openFromFile(path)){
		m_Fonts[id] = font;
	}else{
		std::cout<<"Couldnt open a font: "<< path<<std::endl;
	}
}

sf::Font& ResourceManager::getFont(const std::string& id)
{
	return m_Fonts.at(id);
}