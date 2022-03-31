#ifndef BARRIER
#define BARRIER

#include "Detectable.hpp"
#include <box2d/box2d.h>

class Barrier : public Detectable
{
private:
    b2Body *body;

public:
    Barrier(float x, float y, float width, float hight, b2World &world, std::string n);

    void onDetection(std::string otherName) override;

    void onEndDetection(std::string otherName) override;

    void onPreSolve(std::string otherName, const b2Manifold *oldManifold) override;

    void onPostSolve(std::string otherName, const b2ContactImpulse *impulse) override;

    b2Body *createBarrier(float x, float y, float width, float hight, b2World &world);
};

#endif