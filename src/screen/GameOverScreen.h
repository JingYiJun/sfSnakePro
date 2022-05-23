#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"

namespace sfSnake
{
    class GameOverScreen : public Screen
    {
    public:
        GameOverScreen(std::size_t score);

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Font font_;
        sf::Text text_;

        unsigned score_;
    };
}