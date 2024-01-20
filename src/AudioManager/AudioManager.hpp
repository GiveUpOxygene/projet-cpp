#pragma once
#include <SFML/Audio.hpp>
#include "../Bus/BusListener.hpp"

class AudioManager : public BusListener{
    public:
    AudioManager(Bus& bus);
    void notify(Message msg) override;
    void startMusic();

    private:
    sf::Music music;

    sf::SoundBuffer entityExplosionSoundBuf;
    sf::Sound entityExplosionSound;

    sf::SoundBuffer allyShotSoundBuf;
    sf::Sound allyShotSound;

    sf::SoundBuffer enemyShotSoundBuf;
    sf::Sound enemyShotSound;
};