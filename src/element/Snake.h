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

        void handleInput();
        void update(sf::Time delta);
        void render(sf::RenderWindow &window);

        void checkFruitCollisions(std::vector<Fruit> &fruits);

        bool hitSelf() const;

        unsigned getScore() const;

    private:
        void initNodes();

        void grow();
        void move();

        void checkOutOfWindow();
        void checkSelfCollisions();

        void NodeRender(SnakePathNode last, SnakePathNode now, SnakePathNode middle, sf::RenderWindow &window);

        SnakePathNode toWindow(SnakePathNode node);
        bool hitSelf_;

        Direction direction_;
        float nodeRadius_;
        std::deque<SnakePathNode> path_;
        unsigned tailOverlap_;
        sf::CircleShape nodeShape;
        sf::RectangleShape nodeMiddle;

        static const int InitialSize;
        unsigned int score_;

        sf::SoundBuffer pickupBuffer_;
        sf::Sound pickupSound_;

        sf::SoundBuffer dieBuffer_;
        sf::Sound dieSound_;
    };
}