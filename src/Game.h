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

        static bool GridVisibility_;
        static sf::Color BackgroundColor_;
        static sf::Color GridColor_;

        static std::vector<int> ScoreList_;

        static bool mouseButtonLocked;
        static sf::Clock mouseButtonClock;
        static sf::Time mouseButtonCDtime;

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
}