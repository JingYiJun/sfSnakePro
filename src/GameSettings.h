#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace sfSnake
{
    enum class backgroundColor
    {
        Default,
        White,
        Black,
        Grey
    };

    enum class GridColor
    {
        Default,
        White,
        Black,
        Grey
    };

    struct GameSettings
    {
        /* data */
        std::string windowName_;
        
        sf::VideoMode videoMode;

        sf::Color backgroundColor_;

        bool ifShowGrid_;
        sf::Color gridColor_;

        GameSettings();
        ~GameSettings() = default;

        void setBackgroundColor(backgroundColor);
        void setBackgroundColor(sf::Color &);
        sf::Color &getBackgroundColor();

        void setGridColor(GridColor);
        void setGridColor(sf::Color &);
        sf::Color &getGridColor();
    };
}