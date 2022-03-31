#include "GJet.hpp"
#include <iostream>

GJet::GJet() : dimensions(), shape(sf::LineStrip, 4) {}

GJet::GJet(sf::Vector2f dim) : dimensions(dim), shape(sf::LineStrip, 4)
{
    set(dimensions);
}

void GJet::set(sf::Vector2f dim)
{
    dimensions = dim;
    shape[0].position = sf::Vector2f(0.f, -dimensions.y);
    shape[1].position = sf::Vector2f(dimensions.x * 0.75, 0);
    shape[2].position = sf::Vector2f(-(dimensions.x * 0.75), 0);
    shape[3].position = sf::Vector2f(0.f, -dimensions.y);
}

void GJet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (isOn && flicker)
    {
        target.draw(shape, states);
    }
}

void GJet::update(sf::Time deltaTime)
{
    time += deltaTime.asMilliseconds();
    flicker = time / millisPerFrame % 2;
}