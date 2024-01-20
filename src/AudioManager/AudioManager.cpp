#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager(Bus& bus):
BusListener{bus}
{
    std::cout << "Loading sounds..." << std::endl;

    //Entity explosion sound
    entityExplosionSoundBuf.loadFromFile("./assets/audio/explosion1.wav");
    entityExplosionSound.setBuffer(entityExplosionSoundBuf);
    entityExplosionSound.setVolume(20);

    //Player laser shot sound
    allyShotSoundBuf.loadFromFile("./assets/audio/laser_shot1.wav");
    allyShotSound.setBuffer(allyShotSoundBuf);
    allyShotSound.setVolume(10);

    //Enemy laser shot sound
    enemyShotSoundBuf.loadFromFile("./assets/audio/laser_shot2.wav");
    enemyShotSound.setBuffer(enemyShotSoundBuf);
    enemyShotSound.setVolume(15);

    //Music
    music.openFromFile("./assets/audio/8-Bit-Mayhem.ogg");
    music.setVolume(50);
    music.setLoop(true);
}

void AudioManager::startMusic(){
    music.play();
}

void AudioManager::notify(Message msg){
    switch(msg.getType()){
        case Message::Type::ENTITY_DEATH:
        entityExplosionSound.play();
        break;

        case Message::Type::BLUE_ENTITY_SHOT:
        allyShotSound.play();
        break;

        case Message::Type::RED_ENTITY_SHOT:
        enemyShotSound.play();
        break;

        default:
        break;
    }
}