#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

class ResourceManager {
public:
	void loadFont(const std::string& id, const std::string& path);
	sf::Font& getFont(const std::string& id);


private:
	std::unordered_map<std::string, sf::Font> m_Fonts;
};