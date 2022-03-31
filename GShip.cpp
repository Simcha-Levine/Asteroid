#include "GShip.hpp"

GShip::GShip(sf::Vector2f dim) : dimensions(dim),
                                 shape(sf::LineStrip, 4)
{
    shape[0].position = sf::Vector2f(0.f, dimensions.y * 0.5);
    shape[1].position = sf::Vector2f(dimensions.x * 0.75, -dimensions.y * 0.5);
    shape[2].position = sf::Vector2f(-(dimensions.x * 0.75), -dimensions.y * 0.5);
    shape[3].position = sf::Vector2f(0.f, dimensions.y * 0.5);

    jet.set(sf::Vector2f(dimensions.x * 0.45, dimensions.y * 0.4));
}

void GShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
    states.transform.translate(0, -dimensions.y * 0.5);
    target.draw(jet, states);
}

void GShip::update(sf::Time deltaTime)
{
    jet.update(deltaTime);

    jet.isOn = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}
