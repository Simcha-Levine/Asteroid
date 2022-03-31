#include "VectorConverter.hpp"

b2Vec2 toBox2dVec(sf::Vector2f vec, int scale)
{
    return b2Vec2(vec.x / scale, vec.y / scale);
}

sf::Vector2f toSfmlVec(b2Vec2 vec, int scale)
{
    return sf::Vector2f(vec.x * scale, vec.y * scale);
}