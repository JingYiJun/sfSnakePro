#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class OptionButton
    {
    private:
        sf::Text text_;
        sf::Color originColor_;

    public:
        OptionButton() = default;
        ~OptionButton() = default;

        void settings(
            sf::String content,
            sf::Font &font,
            float setCharacterSize,
            sf::Color color,
            sf::Vector2f position);
        void clear();
        void focused();
        void seleted();

        void render(sf::RenderWindow &window);

        template <typename T>
        bool contains(sf::Vector2<T> point);
    };

    template <typename T>
    bool OptionButton::contains(sf::Vector2<T> point)
    {
        return text_.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
    }
}