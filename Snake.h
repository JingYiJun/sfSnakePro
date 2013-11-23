#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

#include <vector>

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
	void move();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	sf::Vector2f position_;
	Direction direction_;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize = 15;
};
}

#endif