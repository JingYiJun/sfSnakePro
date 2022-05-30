#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    struct Fruit
    {
        sf::CircleShape shape_;
        int score_;

        Fruit(sf::Vector2f position, sf::Color color, int score);

        void render(sf::RenderWindow &window);
    };
}