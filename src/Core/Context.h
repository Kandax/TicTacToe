#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

struct Context {
	sf::RenderWindow* window;
	ResourceManager* resourceManager;
	sf::Vector2f mousePosition;
	bool* isRunning;
};