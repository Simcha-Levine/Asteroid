#include "Player.hpp"
#include "VectorConverter.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

Player::Player(int scale, b2Vec2 pos, b2World &world, sf::View &view, SoundMaker &sounds)
    : scale(scale),
      dimensions(2.2f, 4.5f),
      ship(toSfmlVec(dimensions, scale)),
      world(world),
      body(createBody()),
      view(view),
      sounds(sounds)
{
    setPosition(toSfmlVec(pos, scale));

    shape.push_back(b2Vec2(0.f, dimensions.y * 0.5));
    shape.push_back(b2Vec2(dimensions.x * 0.75, -dimensions.y * 0.5));
    shape.push_back(b2Vec2(-(dimensions.x * 0.75), -dimensions.y * 0.5));

    createShape();

    name = "player";

    thrustBuffer.loadFromFile("assets/thrust.wav");
    thrust.setBuffer(thrustBuffer);
    thrust.setLoop(true);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(ship, states);

    for (size_t i = 0; i < bullets.size(); i++)
    {
        target.draw(*bullets[i]);
    }
}

void Player::update(sf::Time deltaTime)
{
    isDead = life < 0;
    if (!isDead)
    {
        dealWithInput(deltaTime);
    }

    std::vector<size_t> dead;
    for (size_t i = 0; i < bullets.size(); i++)
    {
        bullets[i]->update(deltaTime);
        if (bullets[i]->isDead)
        {
            dead.push_back(i);
        }
    }
    std::sort(dead.begin(), dead.end(), std::greater<>());
    for (auto i : dead)
    {
        delete bullets[i];
        bullets.erase(bullets.begin() + i);
    }

    dealWithEdge();

    syncPhisics();

    if (!isDead)
    {
        ship.update(deltaTime);
    }
}

b2Body *Player::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Vec2 p = toBox2dVec(getPosition(), scale);
    bodyDef.position.Set(p.x, p.y);
    bodyDef.linearDamping = .2f;
    bodyDef.angularDamping = 5.f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2Body *body = world.CreateBody(&bodyDef);

    return body;
}

void Player::createShape()
{
    b2Vec2 ver[3];
    ver[0] = shape[0];
    ver[1] = shape[1];
    ver[2] = shape[2];

    b2PolygonShape poly;
    poly.Set(ver, 3);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &poly;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;

    body->CreateFixture(&fixtureDef);
}

void Player::syncPhisics()
{
    sf::Vector2f pos = toSfmlVec(body->GetPosition(), scale);
    setPosition(pos);
    float deg = body->GetAngle() * (180.f / M_PI);
    setRotation(deg);
}

void Player::onDetection(std::string) {}

void Player::onEndDetection(std::string otherName)
{
    contacts.push_back(otherName);
}

void Player::onPreSolve(std::string, const b2Manifold *) {}

void Player::onPostSolve(std::string otherName, const b2ContactImpulse *impulse)
{
    if (otherName == "astroid")
    {
        life -= impulse->normalImpulses[0];
        sounds.play("knock");
    }
}

void Player::dealWithEdge()
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

void Player::dealWithInput(sf::Time deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        float force = 2.f;
        b2Vec2 fVec;
        float angle = body->GetAngle() + (90.f * M_PI / 180.f);
        fVec.x = force * cos(angle);
        fVec.y = force * sin(angle);
        body->ApplyLinearImpulseToCenter(fVec, true);

        if (thrust.getStatus() == 0 || thrust.getStatus() == 1)
        {
            thrust.play();
        }
    }
    else
    {
        if (thrust.getStatus() == sf::SoundSource::Status::Playing)
        {
            thrust.pause();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        body->ApplyAngularImpulse(-2, true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        body->ApplyAngularImpulse(2, true);
    }
    stime += deltaTime.asMilliseconds();
    rtime += deltaTime.asMilliseconds();
    if (rtime > reloadTime)
    {
        magazine = 3;
        rtime = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (magazine > 0 && stime > shootTime)
        {
            float angle = body->GetAngle() + (90.f * M_PI / 180.f);
            float top = dimensions.y * 0.5;
            b2Vec2 p = b2Vec2(top * cos(angle), top * sin(angle)) + body->GetPosition();
            bullets.push_back(new Bullet(scale, p, angle, world, view));
            sounds.play("fire");
            shots++;
            magazine--;
            stime = 0;
            rtime = 0;
        }
    }
    else
    {
        stime += shootTime;
    }
}

void Player::restart()
{
    life = fullLife;
    isDead = false;
    body->SetTransform(b2Vec2(0, 0), 0);
    body->SetAngularVelocity(0);
    body->SetLinearVelocity(b2Vec2(0, 0));
}
