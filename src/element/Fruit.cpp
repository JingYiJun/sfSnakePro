#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Game.h"

using namespace sfSnake;

Fruit::Fruit(sf::Vector2f position, sf::Color color, int score)
    : score_(score)
{
    shape_.setRadius(Game::GlobalVideoMode.width / 256.0f);
    setOriginMiddle(shape_);
    shape_.setPosition(position);
    shape_.setFillColor(color);
}

void Fruit::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}
