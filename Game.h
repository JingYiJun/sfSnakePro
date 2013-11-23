#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Snake.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	static const int Width = 640;
	static const int Height = 480;

private:
	sf::RenderWindow window_;

	Snake snake_;

	static const sf::Time TimePerFrame;
};
}


#endif