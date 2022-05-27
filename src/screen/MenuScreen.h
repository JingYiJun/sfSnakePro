#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Button.h"
#include "element/OptionButton.h"

#include <vector>

namespace sfSnake
{
    class MenuScreen : public Screen
    {
    public:
        MenuScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

        void setRotation(float angle);

    private:
        sf::Font font_;
        sf::Texture titleTexture_;
        sf::Sprite titleSprite_;
        std::vector<Button> button_;
        OptionButton helpButton_;
        OptionButton aboutButton_;
    };
}