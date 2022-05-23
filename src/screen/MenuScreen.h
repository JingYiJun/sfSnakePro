#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"

namespace sfSnake
{
    class MenuScreen : public Screen
    {
    public:
        MenuScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Font font_;
        sf::Text titleText_;
        sf::Text optionText_;
    };
}