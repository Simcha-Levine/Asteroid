#include "Game.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(1700, 900), "Astroid"), gameAction(&currentScene)
{
    // window.setPosition(sf::Vector2i(800, 100));
    window.setVerticalSyncEnabled(true);
    currentScene = Scenes::GAME_ACTION;
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        update(clock.getElapsedTime());
        // std::cout << clock.restart().asMilliseconds() << '\n';
        clock.restart();
        draw();
    }
}

void Game::update(sf::Time deltaTime)
{
    switch (currentScene)
    {
    case Scenes::GAME_ACTION:
        gameAction.update(deltaTime);
        break;

        // case Scenes::MENU:
        //     gameAction.update(deltaTime);
        //     break;
    default:
        break;
    }
}

void Game::draw()
{
    switch (currentScene)
    {
    case Scenes::GAME_ACTION:
        gameAction.draw(window);
        break;

        // case Scenes::MENU:
        //     gameAction.update(deltaTime);
        //     break;
    default:
        break;
    }
}