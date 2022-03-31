#include "Barrier.hpp"
#include <iostream>

Barrier::Barrier(float x, float y, float width, float hight, b2World &world, std::string n)
    : body(createBarrier(x, y, width, hight, world))
{
    name = "barrier";
    name.append(n);
}

void Barrier::onDetection(std::string) {}

void Barrier::onEndDetection(std::string) {}

void Barrier::onPreSolve(std::string otherName, const b2Manifold *) {}

void Barrier::onPostSolve(std::string otherName, const b2ContactImpulse *) {}

b2Body *Barrier::createBarrier(float x, float y, float width, float hight, b2World &world)
{

    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2Body *body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(width / 2, hight / 2);

    body->CreateFixture(&box, 0.f);
    body->GetFixtureList()[0].SetSensor(true);

    return body;
}