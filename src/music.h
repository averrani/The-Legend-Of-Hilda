//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#ifndef MUSIC_H
#define MUSIC_H
 
#include <SFML/Audio.hpp>
#include <iostream>

class Musics
{

public:

    Musics();

    void PlayMusic(bool valeur, bool music);
    void PlaySound(int type);

private:

    sf::SoundBuffer bumper;
    sf::SoundBuffer destroy;
    sf::SoundBuffer hurt;
    sf::SoundBuffer coin;

    sf::Sound soundBumper;
    sf::Sound soundDestroy;
    sf::Sound soundHurt;
    sf::Sound soundCoin;

    sf::Music music;
    sf::Music music2;

public:

    enum
    {
        BUMPER,
        DESTROY,
        HURT,
        COIN
    };
};
#endif