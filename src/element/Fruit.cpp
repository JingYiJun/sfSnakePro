#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Game.h"

using namespace sfSnake;

float Fruit::Radius = 5.0f;

Fruit::Fruit(sf::Vector2f position, sf::Color color, int score)
    : score_(score)
{
    shape_.setRadius(Fruit::Radius);
    sf::FloatRect shapeBounds = shape_.getLocalBounds();
    shape_.setOrigin(
        shapeBounds.left + shapeBounds.width / 2,
        shapeBounds.top + shapeBounds.height / 2);
    shape_.setPosition(position);
    shape_.setFillColor(color);
}

void Fruit::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}
