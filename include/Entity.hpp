#ifndef ENTITY
#define ENTITY

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
    bool isDead = false;
    virtual void update(sf::Time deltaTime) = 0;
};

#endif
