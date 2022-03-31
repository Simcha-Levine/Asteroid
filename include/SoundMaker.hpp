#ifndef SOUNDMAKER
#define SOUNDMAKER

#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <string>

class SoundMaker
{
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::vector<sf::Sound *> sounds;

public:
    SoundMaker();

    void play(std::string soundName);

    void update();
};
#endif