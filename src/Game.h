#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <cmath>

#include "screen/Screen.h"
#include "element/TitleSprite.h"

namespace sfSnake
{
    class Game
    {
    public:
        Game();
        ~Game() = default;

        void run();

    private:
        void handleInput();
        void update(sf::Time delta);
        void render();

    public:
        /* Global Color settings
         * 全局颜色设置
         */
        class Color
        {
        public:
            static const sf::Color Yellow;
            static const sf::Color Green;
            static const sf::Color Background[3];
            static const sf::Color Grid[3];
            static const sf::Color NotSeleted;
            static const sf::Color Fruit[5];
        };

        static sf::VideoMode initVideoMode_();

        static sf::VideoMode GlobalVideoMode;

        static sf::Font GlobalFont;
        static TitleSprite GlobalTitle;

        static std::shared_ptr<Screen> MainScreen;
        static std::shared_ptr<Screen> TmpScreen;
        static std::shared_ptr<Screen> TmpGameScreen;

        static int GridVisibility;
        static int GridColor;
        static int BackgroundColor;

        static bool mouseButtonLocked;
        static sf::Clock mouseButtonClock;
        static sf::Time mouseButtonCDtime;

        static bool keyboardLocked;
        static sf::Clock keyboardClock;
        static sf::Time keyboardCDtime;

        static bool ifShowedHelp;

    private:
        sf::RenderWindow window_;

        sf::Time TimePerFrame_;

        sf::Music bgMusic_;
    };

    /**
     * @brief set any shape's origin to its middle.
     * @param shape any shape
     *
     * @code {.c++}
     * setOriginMiddle(titleSprite_);
     * @endcode
     *
     * @return sf::FloatRect shapeBounds
     *
     */
    template <typename T>
    inline sf::FloatRect setOriginMiddle(T &shape)
    {
        sf::FloatRect shapeBounds = shape.getLocalBounds();
        shape.setOrigin(shapeBounds.left + shapeBounds.width / 2,
                        shapeBounds.top + shapeBounds.height / 2);
        return shapeBounds;
    }

    /**
     * @brief calculate the distance between two nodes
     *
     * @param node sf::Vector2
     *
     * @return double
     */
    template <typename T1, typename T2>
    inline double dis(
        sf::Vector2<T1> node1,
        sf::Vector2<T2> node2) noexcept
    {
        return std::sqrt(
            std::pow(
                (
                    static_cast<double>(node1.x) -
                    static_cast<double>(node2.x)),
                2) +
            std::pow(
                (
                    static_cast<double>(node1.y) -
                    static_cast<double>(node2.y)),
                2));
    }

    /**
     * @brief calculate the length of a vector
     *
     * @param node sf::Vector2
     *
     * @return double
     */
    template <typename T>
    inline double length(sf::Vector2<T> node) noexcept
    {
        return std::sqrt(
            std::pow(static_cast<double>(node.x), 2) +
            std::pow(static_cast<double>(node.y), 2));
    }
}