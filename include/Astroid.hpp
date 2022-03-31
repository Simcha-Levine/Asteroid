#ifndef ASTROID
#define ASTROID

#include "Entity.hpp"
#include "Detectable.hpp"
#include <box2d/box2d.h>
#include <SoundMaker.hpp>

class Astroid : public Detectable, public Entity
{
private:
public:
    int scale;
    float radius;
    sf::VertexArray vertexArray;
    std::vector<b2Vec2> shape;
    b2World &world;
    b2Body *body;
    sf::View &view;
    std::vector<std::string> contacts;
    SoundMaker &sounds;
    int breakingStage;
    sf::Texture texture;

    Astroid(int scale, float radius, b2Vec2 pos, int breakingStage, b2World &world, sf::View &view, SoundMaker &sounds);

    ~Astroid();

    void push(float force);

    void update(sf::Time deltaTime) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    b2Body *createBody(b2Vec2 pos);
    void createShape();

    void generateShape();

    void syncPhisics();

    void onDetection(std::string otherName) override;

    void onEndDetection(std::string otherName) override;

    void onPreSolve(std::string otherName, const b2Manifold *oldManifold) override;

    void onPostSolve(std::string otherName, const b2ContactImpulse *impulse) override;

    void dealWithCollsion();
    bool dealWithEdge(std::string contact);
    bool dealWithBullet(std::string contact);
};

#endif