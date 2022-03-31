#ifndef GSHIP
#define GSHIP

#include <SFML/Graphics.hpp>
#include "GJet.hpp"

class GShip : public sf::Drawable
{
private:
    sf::Vector2f dimensions;
    sf::VertexArray shape;
    bool isPropultionOn = false;
    GJet jet;

public:
    GShip(sf::Vector2f dim);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime);
};

#endif