#include "Entity.hpp"
#include "Detectable.hpp"

class Bullet : public Detectable, public Entity
{
private:
    int scale;
    float radius;
    sf::CircleShape circle;
    b2World &world;
    b2Body *body;
    sf::View &view;
    std::vector<std::string> contacts;
    float angle;
    int dieTime = 600;
    int time = 0;

public:
    Bullet(int scale, b2Vec2 pos, float angle, b2World &world, sf::View &view);
    ~Bullet();

    b2Body *createBody(b2Vec2 pos);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime);

    void onDetection(std::string otherName) override;

    void onEndDetection(std::string otherName) override;

    void onPreSolve(std::string otherName, const b2Manifold *oldManifold) override;

    void onPostSolve(std::string otherName, const b2ContactImpulse *impulse) override;

    void dealWithEdge();

    void syncPhisics();
};
