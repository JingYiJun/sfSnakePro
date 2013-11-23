#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

#include <list>

#include "SnakeNode.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};

class Snake
{
public:
	Snake();

	void handleInput();
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

private:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	sf::Vector2f position_;
	Direction direction_;

	std::list<SnakeNode> nodes_;
};
}

#endif