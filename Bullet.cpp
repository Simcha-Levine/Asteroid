#include "Bullet.hpp"
#include "VectorConverter.hpp"
#include <iostream>

Bullet::Bullet(int scale, b2Vec2 pos, float angle, b2World &world, sf::View &view)
    : scale(scale),
      radius(0.2),
      circle(radius * scale),
      world(world),
      body(createBody(pos)),
      view(view),
      angle(angle)
{
    setOrigin(radius * scale, radius * scale);
    name = "bullet";

    float force = 20.f;
    b2Vec2 fVec;
    fVec.x = force * cos(angle);
    fVec.y = force * sin(angle);
    body->ApplyLinearImpulseToCenter(fVec, true);
}

Bullet::~Bullet()
{
    world.DestroyBody(body);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(circle, states);
}

void Bullet::update(sf::Time deltaTime)
{
    time += deltaTime.asMilliseconds();
    if (time > dieTime)
    {
        isDead = true;
    }
    dealWithEdge();
    syncPhisics();
}

b2Body *Bullet::createBody(b2Vec2 pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.bullet = true;

    b2Body *body = world.CreateBody(&bodyDef);

    b2CircleShape poly;
    poly.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;

    body->CreateFixture(&fixtureDef);

    return body;
}

void Bullet::syncPhisics()
{
    sf::Vector2f pos = toSfmlVec(body->GetPosition(), scale);
    setPosition(pos);
    float deg = body->GetAngle() * (180.f / M_PI);
    setRotation(deg);
}

void Bullet::onDetection(std::string)
{
}

void Bullet::onEndDetection(std::string otherName)
{
    contacts.push_back(otherName);
    isDead = otherName == "astroid";
}

void Bullet::onPreSolve(std::string, const b2Manifold *) {}

void Bullet::onPostSolve(std::string, const b2ContactImpulse *) {}

void Bullet::dealWithEdge()
{
    for (auto &&contact : contacts)
    {
        if (contact == "barrierTop")
        {
            b2Vec2 v = toBox2dVec(sf::Vector2f(body->GetPosition().x, view.getSize().y / 2), scale);
            body->SetTransform(v, body->GetAngle());
        }
        else if (contact == "barrierBottom")
        {
            b2Vec2 v = toBox2dVec(sf::Vector2f(body->GetPosition().x, -view.getSize().y / 2), scale);
            body->SetTransform(v, body->GetAngle());
        }
        else if (contact == "barrierLeft")
        {
            b2Vec2 v = toBox2dVec(sf::Vector2f(view.getSize().x / 2, body->GetPosition().y), scale);
            body->SetTransform(v, body->GetAngle());
        }
        else if (contact == "barrierRight")
        {
            b2Vec2 v = toBox2dVec(sf::Vector2f(-view.getSize().x / 2, body->GetPosition().y), scale);
            body->SetTransform(v, body->GetAngle());
        }
    }
    contacts.clear();
}