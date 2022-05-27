#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Button.h"
#include "element/OptionButton.h"
#include "Game.h"

#include <vector>
#include <string>

namespace sfSnake
{
    class PauseScreen : public Screen
    {
    public:
        PauseScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Font font_;
        sf::Texture titleTexture_;
        sf::Sprite titleSprite_;
        std::vector<Button> button_;
        Button returnButton_;
        OptionButton helpButton_;
        OptionButton aboutButton_;
    };
}