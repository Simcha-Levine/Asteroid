#ifndef DETECTABLE
#define DETECTABLE

#include <string>
#include <box2d/box2d.h>

class Detectable
{
public:
    std::string name = "normal";

    virtual void onDetection(std::string otherName) = 0;

    virtual void onEndDetection(std::string otherName) = 0;

    virtual void onPreSolve(std::string otherName, const b2Manifold *oldManifold) = 0;

    virtual void onPostSolve(std::string otherName, const b2ContactImpulse *impulse) = 0;

    virtual ~Detectable() = default;
};

#endif
