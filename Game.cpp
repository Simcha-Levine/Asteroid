#include "Game.hpp"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(1700, 900), "Astroid", sf::Style::Fullscreen),
      gameAction(&currentScene, window.getSize())
{
    window.setVerticalSyncEnabled(true);
    currentScene = Scenes::GAME_ACTION;

    texture.create(window.getSize().x, window.getSize().y);

    if (!frag.loadFromFile("assets/screen.frag", sf::Shader::Fragment))
    {
        std::cout << "arrrrrrrrrrr\n";
    }
    frag.setUniform("texture", sf::Shader::CurrentTexture);
    frag.setUniform("u_resolution", sf::Glsl::Vec2{window.getSize()});
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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P)
            {
                gameAction.pause = !gameAction.pause;
            }
        }

        update(clock.getElapsedTime());
        clock.restart();
        draw();
    }
}

void Game::update(sf::Time deltaTime)
{

    gameAction.update(deltaTime);
    gameAction.draw(texture);
}

void Game::draw()
{
    sprite.setTexture(texture.getTexture());
    window.draw(sprite, &frag);
    window.display();
}