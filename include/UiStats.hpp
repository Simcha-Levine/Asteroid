#include <SFML/Graphics.hpp>

class UiStats : public sf::Drawable
{
private:
    sf::RectangleShape lifeBar;
    float length = 400.f;
    float thickness = 30.f;
    sf::View view;
    sf::Font font;
    sf::Text text;

public:
    UiStats();

    void update(float fraction, int score);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
