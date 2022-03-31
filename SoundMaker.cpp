#include "SoundMaker.hpp"
#include <iostream>

SoundMaker::SoundMaker()
{
    soundBuffers["explosion"].loadFromFile("assets/bangLarge.wav");
    soundBuffers["fire"].loadFromFile("assets/fire.wav");
    soundBuffers["knock"].loadFromFile("assets/knock.wav");
}

void SoundMaker::play(std::string soundName)
{
    auto sound = new sf::Sound();
    sound->setBuffer(soundBuffers[soundName]);
    sound->play();
    sounds.push_back(sound);
}

void SoundMaker::update()
{
    std::vector<size_t> dead;
    for (size_t i = 0; i < sounds.size(); i++)
    {
        auto sound = sounds[i];

        if (sound->getStatus() == sf::SoundSource::Status::Stopped)
        {
            delete sound;
            dead.push_back(i);
        }
    }
    std::sort(dead.begin(), dead.end(), std::greater<>());
    for (auto i : dead)
    {
        sounds.erase(sounds.begin() + i);
    }
}
