#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <deque>

#include "Fruit.h"

namespace sfSnake
{
    typedef sf::Vector2f Direction;
    typedef sf::Vector2f SnakePathNode;

    class Snake
    {
    public:
        Snake();

        void handleInput(sf::RenderWindow &window);
        void update(sf::Time delta);
        void render(sf::RenderWindow &window);

        void checkFruitCollisions(std::deque<Fruit> &fruits);

        bool hitSelf() const;

        unsigned getScore() const;

        void printhead() const;

    private:
        void initNodes();

        void grow(int score);
        void move();

        void checkOutOfWindow();
        void checkSelfCollisions();

        template <typename T>
        void renderNode(sf::Vector2f &nowPosition, T &shape, sf::RenderWindow &window, int offset);

        SnakePathNode toWindow(SnakePathNode node);
        bool hitSelf_;
        bool speedup_;

        Direction direction_;
        float nodeRadius_;
        std::deque<SnakePathNode> path_;
        unsigned tailOverlap_;

        sf::CircleShape nodeShape;
        sf::RectangleShape nodeMiddle;
        sf::Texture headTexture;
        sf::Sprite headSprite;

        static const int InitialSize;
        unsigned int score_;

        sf::SoundBuffer pickupBuffer_;
        sf::Sound pickupSound_;

        sf::SoundBuffer dieBuffer_;
        sf::Sound dieSound_;
    };
}