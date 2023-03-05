#include "Astroid.hpp"
#include "VectorConverter.hpp"
#include <iostream>
#include <math.h>

int corners = 8;

Astroid::Astroid(int scale, float radius, b2Vec2 pos, int breakingStage, b2World &world, sf::View &view, SoundMaker &sounds)
    : scale(scale),
      radius(radius),
      vertexArray(sf::LineStrip, corners + 1),
      world(world),
      body(createBody(pos)),
      view(view),
      sounds(sounds),
      breakingStage(breakingStage)
{
    setPosition(toSfmlVec(pos, scale));

    generateShape();
    createShape();
    int j = 0;
    for (int i = 0; i < (corners + 1); i += 1)
    {
        sf::Vector2f vec = toSfmlVec(shape[j], scale);
        vertexArray[i].position = vec;
        // vec = toSfmlVec(shape[j] - b2Vec2(shape[j].x * 0.05f, shape[j].y * 0.05f), scale);
        // vertexArray[i + 1].position = vec;
        j++;
    }

    name = "astroid";
}

void Astroid::push(float force)
{
    b2Vec2 fVec;
    float angle = float(std::rand()) / float(RAND_MAX / (M_PI * 2));
    fVec.x = force * cos(angle);
    fVec.y = force * sin(angle);
    body->ApplyLinearImpulseToCenter(fVec, true);
}

Astroid::~Astroid()
{
    world.DestroyBody(body);
}

void Astroid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertexArray, states);
}

void Astroid::update(sf::Time deltaTime)
{
    dealWithCollsion();
    syncPhisics();
}

b2Body *Astroid::createBody(b2Vec2 pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Vec2 p = pos;
    bodyDef.position.Set(p.x, p.y);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2Body *body = world.CreateBody(&bodyDef);

    return body;
}

void Astroid::generateShape()
{
    float firstAngle = 0;

    for (int i = 0; i < corners; i++)
    {

        float section = M_PI * 2 / corners;
        float range = section * 0.3;
        float add = -range + float(std::rand()) / float(RAND_MAX / (range * 2));
        double angle = section * i + add;
        shape.push_back(b2Vec2(radius * cos(angle), radius * sin(angle)));

        if (i == 0)
        {
            firstAngle = angle;
        }
    }
    shape.push_back(b2Vec2(radius * cos(firstAngle), radius * sin(firstAngle)));
}

void Astroid::createShape()
{
    b2Vec2 *ver = new b2Vec2[corners];
    for (int i = 0; i < corners; i++)
    {
        ver[i] = shape[i];
    }

    b2PolygonShape poly;
    poly.Set(ver, corners);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;

    body->CreateFixture(&fixtureDef);

    delete[] ver;
}

void Astroid::syncPhisics()
{
    sf::Vector2f pos = toSfmlVec(body->GetPosition(), scale);
    setPosition(pos);
    float deg = body->GetAngle() * (180.f / M_PI);
    setRotation(deg);
}

void Astroid::onDetection(std::string otherName)
{
    if (otherName == "bullet")
    {
        contacts.push_back(otherName);
    }
}

void Astroid::onEndDetection(std::string otherName)
{
    contacts.push_back(otherName);
}

void Astroid::onPreSolve(std::string, const b2Manifold *) {}

void Astroid::onPostSolve(std::string, const b2ContactImpulse *) {}

void Astroid::dealWithCollsion()
{
    for (auto &&contact : contacts)
    {
        if (!dealWithEdge(contact))
        {
            if (!dealWithBullet(contact))
            {
            }
        }
    }
    contacts.clear();
}

bool Astroid::dealWithEdge(std::string contact)
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
    else
    {
        return false;
    }
    return true;
}

bool Astroid::dealWithBullet(std::string contact)
{
    if (contact == "bullet")
    {

        isDead = true;
        sounds.play("explosion");

        return true;
    }
    return false;
}