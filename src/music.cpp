//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "music.h"
 
using namespace std;
using namespace sf;
 
//Constructeur
Musics::Musics()
{
    if (!destroy.loadFromFile("data/music/destroy.wav"))
        cout << "Erreur durant le chargement des musiques." << endl;
    soundDestroy.setBuffer(destroy);

    if (!hurt.loadFromFile("data/music/hurt.wav"))
        cout << "Erreur durant le chargement des musiques." << endl;
    soundHurt.setBuffer(hurt);

    if (!coin.loadFromFile("data/music/coin.wav"))
        cout << "Erreur durant le chargement des musiques." << endl;
    soundCoin.setBuffer(coin);

    if (!music.openFromFile("data/music/village1.ogg"))
        cout << "Erreur durant le chargement des musiques." << endl;

    if (!music2.openFromFile("data/music/village2.ogg"))
        cout << "Erreur durant le chargement des musiques." << endl;
}

void Musics::PlayMusic(bool valeur, bool musical)
{
    if (musical == 1)
    {     
        music.setLoop(true);

        if (valeur)
            music.play();
        else
            music.stop();
    }else {
        music2.setLoop(true);

        if (valeur)
            music2.play();
        else
            music2.stop();
    }

}

void Musics::PlaySound(int type)
{
    switch (type)
    {

    case BUMPER:
        soundBumper.play();
        break;

    case DESTROY:
        soundDestroy.play();
        break;

    case HURT:
        soundHurt.play();
        break;

    case COIN:
        soundCoin.play();
        break;
    }
}
 