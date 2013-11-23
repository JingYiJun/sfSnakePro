#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Green);
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	shape_.setPosition(position_);
	window.draw(shape_);
}