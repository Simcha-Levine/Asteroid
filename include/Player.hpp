#ifndef PLAYER
#define PLAYER

#include "Entity.hpp"
#include "GShip.hpp"
#include <vector>
#include "Detectable.hpp"
#include "Bullet.hpp"
#include <SFML/Audio.hpp>
#include "SoundMaker.hpp"

class Player : public Detectable, public Entity
{
private:
    int scale;
    b2Vec2 dimensions;
    std::vector<b2Vec2> shape;
    GShip ship;
    b2World &world;
    b2Body *body;
    sf::View &view;
    std::vector<std::string> contacts;
    std::vector<Bullet *> bullets;
    int shootTime = 300;
    int reloadTime = 400;
    int stime = 0;
    int rtime = 0;
    SoundMaker &sounds;
    sf::SoundBuffer thrustBuffer;
    sf::Sound thrust;
    int magazine = 3;

public:
    float fullLife = 400;
    float life = fullLife;
    int shots = 0;

    Player(int scale, b2Vec2 pos, b2World &world, sf::View &view, SoundMaker &sounds);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime) override;

    b2Body *createBody();
    void createShape();

    void syncPhisics();

    void onDetection(std::string otherName) override;

    void onEndDetection(std::string otherName) override;

    void onPreSolve(std::string otherName, const b2Manifold *oldManifold) override;

    void onPostSolve(std::string otherName, const b2ContactImpulse *impulse) override;

    void dealWithEdge();

    void dealWithInput(sf::Time deltaTime);

    void restart();
};

#endif