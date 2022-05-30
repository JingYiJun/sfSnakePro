#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Button.h"

#include <vector>

namespace sfSnake
{
    class AboutScreen : public Screen
    {
    public:
        AboutScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        Button returnButton_;
        sf::Text text_;
    };
}