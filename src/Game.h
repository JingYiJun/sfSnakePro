#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

#include "screen/Screen.h"
#include "GameSettings.h"

namespace sfSnake
{
    class Game
    {
    public:
        Game();

        void run();

        void handleInput();
        void update(sf::Time delta);
        void render();

        static sf::VideoMode initVideoMode_();

        static sf::VideoMode VideoMode_;
        static std::shared_ptr<Screen> Screen_;

    private:
        sf::RenderWindow window_;

        sf::Time TimePerFrame;

        sf::Music bgMusic_;
    };
}