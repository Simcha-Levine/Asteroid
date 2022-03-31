#ifndef GJET
#define GJET

#include <SFML/Graphics.hpp>

class GJet : public sf::Drawable
{
private:
    sf::Vector2f dimensions;
    sf::VertexArray shape;
    int millisPerFrame = 50;
    int time = 0;
    bool flicker = false;

public:
    GJet();
    GJet(sf::Vector2f dim);
    bool isOn = false;

    void set(sf::Vector2f dim);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime);
};

#endif