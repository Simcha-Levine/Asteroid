#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <GameAction.hpp>
// #include "Scenes.hpp"
class Game
{
private:
    sf::RenderWindow window;
    GameAction gameAction;
    Scenes currentScene;

public:
    Game();

    void run();

    void update(sf::Time deltaTime);

    void draw();
};

#endif