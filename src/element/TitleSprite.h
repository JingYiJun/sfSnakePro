#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class TitleSprite
    {
    private:
        sf::Texture titleTexture_;
        sf::Sprite titleSprite_;
        bool rotateDirection_;

    public:
        TitleSprite();

        void update(sf::Time delta);
        void render(sf::RenderWindow &window);
    };
}
