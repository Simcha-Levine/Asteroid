#include <SFML/Graphics.hpp>

class UiStats : public sf::Drawable
{
private:
    sf::RectangleShape lifeBar;
    float firstLength = 400.f;
    float currentLength = 400.f;
    float stepingLength = 400.f;
    float step = 2.f;
    float thickness = 30.f;
    sf::View view;
    sf::Font font;
    sf::Text text;

public:
    UiStats();

    void update(float fraction, int score);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void restart();
};
