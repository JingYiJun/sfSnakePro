#include <SFML/Graphics.hpp>

#include "Game.h"

using namespace sfSnake;

// 60 frames per second.
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{

}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}
}

void Game::update(sf::Time delta)
{

}

void Game::render()
{
	window_.clear();

	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}