#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "screen/Screen.h"
#include "screen/GameScreen.h"
#include "element/Grid.h"
#include "element/Button.h"
#include "element/OptionButton.h"

namespace sfSnake
{
    class OptionScreen : public Screen
    {
    public:
        OptionScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        std::vector<OptionButton> optionName_;
        std::vector<OptionButton> GridShowOptions_;
        std::vector<OptionButton> GridColorOptions_;
        std::vector<OptionButton> BGColorOptions_;

        int GridShowfocused_;
        int GridColorfocused_;
        int BGColorfocused_;

        Grid grid_;

        Button returnButton_;
    };
}