//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#ifndef JEU_H
#define JEU_H

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "input.h"
#include "player.h"
#include "map.h"
#include "dessin.h"
#include "windowTxt.h"
#include "jeu.h"
#include "monster.h"
#include "music.h"

using namespace std;
using namespace sf;

//Nombre max de monstres gérés
const int MONSTRES_MAX = 50;

class Jeu {

private:
    
    //Instanciation des classes
    Input input;
    Map map;
    Map terrain { 15, 15 };
    Player player;
    Monster monster[MONSTRES_MAX];
    Musics musics;

public:
    //Constructeur
    Jeu ();
    Jeu (bool musically);

    //Fonctions
    void boucleJeu ();
    void boucleJeuTxt ();
    void winTextAff(WindowTXT &win);
    void boucleJeuDefil();
    Map& getMap ();
    Player& getPlayer ();
    void update(int dir, Player &player);
    void update(RenderWindow &window, Musics &musics, bool isDefil);
    void draw(sf::RenderWindow &window);
    void draw2(sf::RenderWindow &window);

    // Taille de la fenêtre : 800x480 pixels
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 480;
    
};

#endif