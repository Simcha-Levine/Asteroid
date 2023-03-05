#include "GameAction.hpp"
#include <string>
#include "VectorConverter.hpp"
#include "Player.hpp"
#include "Astroid.hpp"
#include "math.h"
#include <iostream>

b2Vec2 getRandomPos(b2Vec2 size);

GameAction::GameAction(Scenes *scene, sf::Vector2u winSize)
    : view(sf::FloatRect(0, 0, winSize.x * 2.f, winSize.y * 2.f * -1.f)),
      b2_world(b2Vec2(0, 0)),
      astroids(),
      player(scale, b2Vec2(0, 0), b2_world, view, sounds),
      listener()
{
    srand(time(nullptr));

    currentScene = scene;

    b2_world.SetContactListener(&listener);

    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    view.setCenter(sf::Vector2f(0, 0));

    b2Vec2 size = toBox2dVec(view.getSize(), scale);
    b2Vec2 pos = toBox2dVec(view.getCenter(), scale);

    barriers.push_back(new Barrier(pos.x, size.y / 2 - 10, size.x, 0.2, b2_world, "Bottom"));
    barriers.push_back(new Barrier(pos.x, -size.y / 2 + 10, size.x, 0.2, b2_world, "Top"));
    barriers.push_back(new Barrier(size.x / 2 + 10, pos.y, 0.2, size.x, b2_world, "Right"));
    barriers.push_back(new Barrier(-size.x / 2 - 10, pos.y, 0.2, size.x, b2_world, "Left"));

    spawnAstroids();
}

void GameAction::restart()
{
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    view.setCenter(sf::Vector2f(0, 0));

    for (auto &&astroid : astroids)
    {
        delete astroid;
    }
    astroids.clear();

    player.restart();

    astroidAmount = startingAmount;
    spawnAstroids();

    stats.restart();
}

b2Vec2 getRandomPos(b2Vec2 size)
{
    float x = -(size.x / 2) + float(std::rand()) / float(RAND_MAX / (size.x));
    float y = -(size.y / 2) + float(std::rand()) / float(RAND_MAX / (size.y));
    return b2Vec2(x, y);
}

void GameAction::update(sf::Time deltaTime)
{
    if (pause)
    {
        return;
    }

    player.update(deltaTime);

    std::vector<size_t> dead;
    for (size_t i = 0; i < astroids.size(); i++)
    {
        auto astroid = astroids[i];
        astroid->update(deltaTime);

        if (astroid->isDead)
        {
            dead.push_back(i);
        }
    }
    checkForDead(dead);
    if (astroids.size() == 0)
    {
        delayTime += deltaTime.asMilliseconds();
        if (delayTime > astroidSpawnDelay)
        {
            astroidAmount += 2;
            spawnAstroids();
            delayTime = 0;
        }
    }

    b2_world.Step(1.0f / 60.0f, 6, 2);

    sounds.update();

    if (player.life < 0)
    {
        restart();
        score = 0;
    }

    if (score > 0)
    {
        score -= player.shots * 3;
    }
    player.shots = 0;
    stats.update(player.life / player.fullLife, score);
}

void GameAction::checkForDead(std::vector<size_t> dead)
{
    std::sort(dead.begin(), dead.end(), std::greater<>());
    for (auto index : dead)
    {
        auto astroid = astroids[index];

        score += 90 / (astroid->breakingStage + 1);

        if (astroid->breakingStage > 0)
        {
            for (int j = 0; j < 2; j++)
            {
                b2Vec2 pos = astroid->body->GetPosition();
                pos.x += (astroid->radius / 2 * (j * 2 - 1));
                astroids.push_back(new Astroid(scale,
                                               astroid->radius / 2,
                                               pos,
                                               astroid->breakingStage - 1,
                                               b2_world, view, sounds));
                b2Vec2 v = astroid->body->GetLinearVelocity();
                int a = rand();
                v.x *= 2.2f * cos(a);
                v.y *= 2.2f * sin(a);
                astroids.back()->body->SetLinearVelocity(v);
            }
        }

        delete astroid;
        astroids.erase(astroids.begin() + index);
    }
}

void GameAction::draw(sf::RenderTexture &render)
{
    render.setView(view);

    render.clear(sf::Color::Black);

    render.draw(player);
    for (auto &&astroid : astroids)
    {
        render.draw(*astroid);
    }

    render.draw(stats);

    render.display();
}

void GameAction::spawnAstroids()
{
    b2Vec2 size = toBox2dVec(view.getSize(), scale);

    for (int i = 0; i < astroidAmount; i++)
    {
        b2Vec2 p1 = getRandomPos(size);
        b2Vec2 p2 = toBox2dVec(player.getPosition(), scale);
        int dic = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
        while (dic < 20)
        {
            p1 = getRandomPos(size);
            dic = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
        }

        astroids.push_back(new Astroid(scale, 6.75f, getRandomPos(size), 2, b2_world, view, sounds));
        astroids.back()->push(1000);
    }
}