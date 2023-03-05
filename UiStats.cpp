#include "UiStats.hpp"
#include <iostream>
#include <string>

struct rgb
{
    float r = 0;
    float g = 0;
    float b = 0;
};

struct hsv
{
    float h = 0;
    float s = 0;
    float v = 0;
};

rgb hsv2rgb(hsv in);

UiStats::UiStats()
    : lifeBar(sf::Vector2f(firstLength, thickness)),
      view(sf::FloatRect(0, 0, 1700, 900))
{
    lifeBar.setPosition(20.f, 20.f);
    lifeBar.setFillColor(sf::Color::Green);

    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    font.loadFromFile("assets/HALO____.TTF");
    text.setFont(font);
    text.setPosition(sf::Vector2f(firstLength + 50.f, 10.f));
    text.setCharacterSize(50);
    text.setColor(sf::Color(250.f, 255.f, 255.f));
}

void UiStats::update(float fraction, int score)
{
    currentLength = firstLength * fraction;
    if ((stepingLength - step) >= currentLength)
    {
        stepingLength -= step;
    }

    lifeBar.setSize(sf::Vector2f(stepingLength, thickness));
    hsv hsvColor{80.f * (stepingLength / firstLength), 1.f, 1.f};
    rgb rgbColor = hsv2rgb(hsvColor);
    lifeBar.setFillColor(sf::Color(rgbColor.r * 255, rgbColor.g * 255, rgbColor.b * 255));

    text.setString(std::to_string(score));
}

void UiStats::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    target.setView(view);
    target.draw(lifeBar);
    target.draw(text);
}

void UiStats::restart()
{
    currentLength = 400.f;
    stepingLength = 400.f;
}

rgb hsv2rgb(hsv in)
{
    double hh, p, q, t, ff;
    long i;
    rgb out;

    if (in.s <= 0.0)
    { // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i)
    {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}