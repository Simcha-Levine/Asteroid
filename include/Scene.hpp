#ifndef SCENE
#define SCENE

#include "Scenes.hpp"
#include <SFML/Graphics.hpp>

class Scene
{

public:
    Scenes *currentScene;

    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow &render) = 0;

    virtual ~Scene() = default;
};

#endif