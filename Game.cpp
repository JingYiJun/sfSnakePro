#include <SFML/Graphics.hpp>

#include <random>
#include <ctime>

#include "Game.h"
#include "Fruit.h"

using namespace sfSnake;


const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake"),
snake_()
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

	snake_.handleInput();
}

void Game::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);
}

void Game::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}

void Game::render()
{
	window_.clear();
	snake_.render(window_);

	for (auto fruit : fruit_)
		fruit.render(window_);

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