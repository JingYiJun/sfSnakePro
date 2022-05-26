#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace sfSnake
{
    class Button
    {
    private:
        sf::Texture texture_;
        sf::Sprite sprite_;
        bool focused_;

    public:
        Button();
        void update(std::string filename, float scale = 1 / 8.0f);
        void setPosition(float x, float y);

        void focused(bool status);
        bool focused() const;

        template <typename T>
        bool contain(sf::Vector2<T>) const;

        void render(sf::RenderWindow &window) const;
    };

    template <typename T>
    bool Button::contain(sf::Vector2<T> point) const
    {
        return dis(point, sprite_.getPosition()) < (sprite_.getGlobalBounds().width) / 2.0f;
    }
}