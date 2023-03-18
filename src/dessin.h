#ifndef DESSIN_H
#define DESSIN_H

#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
using namespace std;

//les constantes utiles à l'animation

const int DOWN = 0;
const int UP = 1;
const int RIGHT = 2;
const int LEFT = 3;

const int IDLE = 0;
const int WALK = 1;

const int TIME_BETWEEN_2_FRAMES_PLAYER = 7;
const float TIME_BETWEEN_2_FRAMES_SWORD = 1;

//les fonctions de chargement des spritesheet
//et d'initialisation des variables utiles pour SFML

void loadPlayer(Player &player);
void initPlayer(Player &player);

//les petites fonctions de dessin

void updatePlayer(Player &player, int dir);

//les fonctions de dessin principales, une pour chaque classe

void drawPlayer(Map &map, sf::RenderWindow &window, Player &player);
void drawMap(int layer, sf::RenderWindow &window);
void drawMain(sf::RenderWindow &window, Map &map, Player &player);

#endif