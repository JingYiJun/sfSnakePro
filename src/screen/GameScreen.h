#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Snake.h"
#include "element/Fruit.h"
#include "element/Grid.h"

namespace sfSnake
{
    class GameScreen : public Screen
    {
    public:
        GameScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

        void generateFruit();

    private:
        Snake snake_;
        std::vector<Fruit> fruit_;
        Grid grid_;
    };
}

#endif