#include <GameSettings.h>

using namespace sfSnake;

GameSettings::GameSettings()
    :windowName_{"sfSnake"}, ifShowGrid_{false}
{
    setBackgroundColor(backgroundColor::White);
    setGridColor(GridColor::White);
}

void GameSettings::setBackgroundColor(backgroundColor color)
{
    switch (color)
    {
    case backgroundColor::White:
        backgroundColor_ = sf::Color(0xfbfbfbff);
        break;

    case backgroundColor::Grey:
        backgroundColor_ = sf::Color(0x5a351dff);
        break;

    case backgroundColor::Black:
        backgroundColor_ = sf::Color(0x313131ff);
        break;

    default:
        break;
    }
}

void GameSettings::setBackgroundColor(sf::Color &color)
{
    backgroundColor_ = color;
}

sf::Color &GameSettings::getBackgroundColor()
{
    return backgroundColor_;
}

void GameSettings::setGridColor(GridColor color)
{
    switch (color)
    {
    case GridColor::White:
        backgroundColor_ = sf::Color(0xeaeaeaee);
        break;

    case GridColor::Grey:
        backgroundColor_ = sf::Color(0x9f6133ff);
        break;

    case GridColor::Black:
        backgroundColor_ = sf::Color(0x747474ff);
        break;

    default:
        break;
    }
}

void GameSettings::setGridColor(sf::Color &color)
{
    gridColor_ = color;
}

sf::Color &GameSettings::getGridColor()
{
    return gridColor_;
}