#include "ContactListener.hpp"
#include "Detectable.hpp"
#include <iostream>

void ContactListener::BeginContact(b2Contact *contact)
{
    auto bodyUserDataA = (Detectable *)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto bodyUserDataB = (Detectable *)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    bodyUserDataA->onDetection(bodyUserDataB->name);
    bodyUserDataB->onDetection(bodyUserDataA->name);
}

void ContactListener::EndContact(b2Contact *contact)
{
    auto bodyUserDataA = (Detectable *)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto bodyUserDataB = (Detectable *)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    bodyUserDataA->onEndDetection(bodyUserDataB->name);
    bodyUserDataB->onEndDetection(bodyUserDataA->name);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    auto bodyUserDataA = (Detectable *)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto bodyUserDataB = (Detectable *)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    bodyUserDataA->onPreSolve(bodyUserDataB->name, oldManifold);
    bodyUserDataB->onPreSolve(bodyUserDataA->name, oldManifold);
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    auto bodyUserDataA = (Detectable *)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto bodyUserDataB = (Detectable *)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    bodyUserDataA->onPostSolve(bodyUserDataB->name, impulse);
    bodyUserDataB->onPostSolve(bodyUserDataA->name, impulse);
}