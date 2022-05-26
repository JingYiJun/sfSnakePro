#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <cmath>

#include "screen/Screen.h"
#include "element/Snake.h"

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
        static std::shared_ptr<Screen> TmpScreen_;
        static std::shared_ptr<Screen> TmpGameScreen_;

        static int GridVisibility_;
        static int BackgroundColor_;
        static int GridColor_;

        static bool mouseButtonLocked;
        static sf::Clock mouseButtonClock;
        static sf::Time mouseButtonCDtime;

        static bool keyboardLocked;
        static sf::Clock keyboardClock;
        static sf::Time keyboardCDtime;

        static int inputDevice; // 0 for keyboard, 1 for mouse, 2 for joystick

        class Color
        {
        public:
            static const sf::Color Yellow;
            static const sf::Color Green;
            static const sf::Color Background[3];
            static const sf::Color Grid[3];
            static const sf::Color NotSeleted;
        };

    private:
        sf::RenderWindow window_;

        sf::Time TimePerFrame;

        sf::Music bgMusic_;
    };

    template <typename T>
    sf::FloatRect setOriginMiddle(T &shape)
    {
        sf::FloatRect shapeBounds = shape.getLocalBounds();
        shape.setOrigin(shapeBounds.left + shapeBounds.width / 2,
                        shapeBounds.top + shapeBounds.height / 2);
        return shapeBounds;
    }

    template <typename T1, typename T2>
    double dis(sf::Vector2<T1> node1, sf::Vector2<T2> node2)
    {
        return std::sqrt(std::pow((node1.x - node2.x), 2) + std::pow((node1.y - node2.y), 2));
    }

    template <typename T>
    double length(sf::Vector2<T> node)
    {
        return std::sqrt(std::pow((node.x), 2) + std::pow((node.y), 2));
    }
}