#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class Grid
    {
    private:
        sf::RectangleShape gridVline;   // Verical line
        sf::RectangleShape gridHline;   // Horizon Line
    public:
        Grid();
        ~Grid() = default;
        void render(sf::RenderWindow &window);
    };
    
    
}