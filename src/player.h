//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "input.h"
#include "dessin.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Map;
class Input;
class Musics;

class Player
{

public:
    //Structures
    struct POINT
    {
        int x, y;
    };

    //Constructeur
    Player();

    //Accesseurs
    int getX(void) const;
    int getY(void) const;
    int getW(void) const;
    int getH(void) const;
    float getDirX(void) const;
    float getDirY(void) const;
    int getLife(void) const;
    int getGold(void) const;
    int getDirection(void) const;

    //Mutateurs
    void setX(int valeur);
    void setY(int valeur);
    void setW(int valeur);
    void setH(int valeur);
    void setDirX(float valeur);
    void setDirY(float valeur);
    void setGold(int valeur);

    //Fonctions
    void initialize(Map &map);
    void update(Input &input, Map &map);
    void centerScrolling(Map &map);
    void mapCollision(Map &map);
    void reinitialize(Map &map);
    //void ennemyCollision(Monster &monster);
    void UpdateSword(Map &map, sf::RenderWindow &window);
    void killPlayer(Musics &musics);
    void HurtPlayer(Musics &musics);
    bool CollisionWithSword(int x1, int y1, int w1, int h1);

private:
    //Variables de la classe en accès privé

    // On ajoute les fonctions de dessin du joueur en tant qu'amies
    // pour faciliter les opérations et changements de variables
    friend void loadPlayer(Player &player);
    friend void initPlayer(Player &player);
    friend void updatePlayer(Player &player, int dir);
    friend void updateSword(Player &player, bool dejaEnTrainDAttaquer);
    friend void drawPlayer(Map &map, sf::RenderWindow &window, Player &player);
    

    // Points de vie/santé + chrono d'invicibilité
    int life, invincibleTimer;

    //Or
    int gold;

    // Coordonnées du sprite
    int x, y;

    // Largeur, hauteur du sprite
    int h, w;

    // Variables utiles pour l'animation :
    // Numéro de la frame (= image) en cours + timer
    int frameNumber, frameTimer, frameMax;
    // Nombre max de frames, état du sprite et direction
    // dans laquelle il se déplace (gauche / droite)
    int etat, direction;
    int isrunning;
    int isAttacking;

    // Variables utiles pour la gestion des colisions :
    //Est-il sur le sol, chrono une fois mort
    int timerMort;

    //Vecteurs de déplacement temporaires avant détection
    //des collisions avec la map
    float dirX, dirY;
    //Sauvegarde des coordonnées de départ
    int saveX, saveY;

    //Spritesheet du héros et son épée
    sf::Texture heroTexture;
    sf::Sprite hero;
    sf::Texture swordTexture;
    sf::Sprite sword;

    //Gestion de l'épée
    int swordX, swordY;
    int swordTimer;
    int swordRotation;

    /******************/
    /* Constantes */
    /******************/

    /* Taille maxi de la map : 400 x 150 tiles */
    const int MAX_MAP_X = 400;
    const int MAX_MAP_Y = 150;

    /* Taille d'une tile (32 x 32 pixels) */
    const int TILE_SIZE = 32;

    /* Taille du sprite de notre héros (largeur = width et hauteur = heigth) */
    const int PLAYER_WIDTH = 40;
    const int PLAYER_HEIGTH = 48;

    //Vitesse de déplacement en pixels du sprite
    const int PLAYER_SPEED = 3;

    //Valeurs attribuées aux états/directions
    const int DEAD = 4;

    // Taille de la fenêtre : 800x480 pixels
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 480;

    //Constantes pour les limites de la caméra avant scrolling
    const int LIMITE_X = 400;
    const int LIMITE_Y = 220;
    const int LIMITE_W = 100;
    const int LIMITE_H = 80;

    //Enum pour les boutons
    enum
    {
        up,
        down,
        right,
        left,
        attack,
        run,
        enter
    };

    //Nombre max de levels
    const int LEVEL_MAX = 2;
    const int MUR = 1;
};
#endif