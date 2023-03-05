#ifndef GAMEACTION
#define GAMEACTION

#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include<box2d/box2d.h>
// #include "Entity.hpp"
#include "Player.hpp"
#include "Astroid.hpp"
#include "Barrier.hpp"
#include "ContactListener.hpp"
#include "SoundMaker.hpp"
#include "UiStats.hpp"

class GameAction : public Scene
{
private:
    sf::View view;
    int scale = 30;
    b2World b2_world;
    std::vector<Barrier *> barriers;
    std::vector<Astroid *> astroids;
    int startingAmount = 3;
    int astroidAmount = startingAmount;
    int astroidSpawnDelay = 500;
    int delayTime = 0;
    Player player;
    ContactListener listener;
    SoundMaker sounds;
    UiStats stats;
    int score = 0;

public:
    bool pause = false;

    GameAction(Scenes *scene, sf::Vector2u winSize);

    void restart();

    void update(sf::Time deltaTime) override;

    void checkForDead(std::vector<size_t> dead);

    void draw(sf::RenderTexture &render) override;

    void spawnAstroids();
};

#endif