#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include <unordered_map>
#include <string>

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
        sf::Texture titleTexture_;
        sf::Sprite titleSprite_;
        std::unordered_map<std::string, sf::Texture> buttonTexture_;
        std::unordered_map<std::string, sf::Sprite> buttonSprite_;
        std::unordered_map<std::string, bool> buttonFocused_;
    };
}