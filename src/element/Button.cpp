#include "element/Button.h"
#include "Game.h"

using namespace sfSnake;

Button::Button()
    : focused_{false}
{
}

void Button::update(std::string filename, float scale)
{
    if (!texture_.loadFromFile(filename))
        return;
    texture_.setSmooth(true);
    sprite_.setTexture(texture_);
    sf::FloatRect bounds = setOriginMiddle(sprite_);
    sprite_.setScale(Game::GlobalVideoMode.width / bounds.width * scale, Game::GlobalVideoMode.width / bounds.width * scale);
}

void Button::setPosition(float x, float y)
{
    sprite_.setPosition(x, y);
}

void Button::focused(bool status)
{
    focused_ = status;
    if (status)
        sprite_.setColor(sf::Color::Green);
    else
        sprite_.setColor(sf::Color::White);
}

bool Button::focused() const
{
    return focused_;
}

void Button::render(sf::RenderWindow &window) const
{
    window.draw(sprite_);
}

