#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Game.h"

using namespace sfSnake;

float Fruit::Radius = 5.0f;

Fruit::Fruit(sf::Vector2f position, sf::Color color, int score)
    : score_(score)
{
    shape_.setRadius(Fruit::Radius);
    setOriginMiddle(shape_);
    shape_.setPosition(position);
    shape_.setFillColor(color);
}

void Fruit::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}
