#pragma once

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual void handleInput(sf::RenderWindow &window) = 0;
	virtual void update(sf::Time delta) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
};