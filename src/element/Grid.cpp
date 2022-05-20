#include "element/Grid.h"
#include "Game.h"

using namespace sfSnake;

Grid::Grid()
    : gridVline(sf::Vector2f(Game::VideoMode_.width / 500.0f, Game::VideoMode_.height)),
      gridHline(sf::Vector2f(Game::VideoMode_.width, Game::VideoMode_.width / 500.0f))
{
}

void Grid::render(sf::RenderWindow &window)
{
    gridVline.setFillColor(Game::GridColor_);
    gridHline.setFillColor(Game::GridColor_);
    window.draw(gridVline);
    window.draw(gridHline);
}
