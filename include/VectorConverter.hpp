#ifndef VECTORCONVERTER
#define VECTORCONVERTER

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

b2Vec2 toBox2dVec(sf::Vector2f vec, int scale);

sf::Vector2f toSfmlVec(b2Vec2 vec, int scale);

#endif