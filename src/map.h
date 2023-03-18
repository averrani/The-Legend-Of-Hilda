//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Player;
class Monster;

class Map
{

public:
    
    struct POINT
    {
        int x, y;
    };

    //Constructeur
    Map();
    Map(int, int);

    //Accesseurs
    int getBeginX(void) const;
    int getBeginY(void) const;
    int getStartX(void) const;
    int getStartY(void) const;
    int getMaxX(void) const;
    int getMaxY(void) const;
    int getTile(int y, int x) const;
    int getTileTxt(int x, int y) const;
    int getLevel(void) const;
    int getNombreMonstres(void) const;
    int getWarpUp(void) const;
    int getWarpDown(void) const;
    int getWarpLeft(void) const;
    int getWarpRight(void) const;
    int getWarpDirection(void) const;
    int getWarp_coming_from_x(void) const;
    int getWarp_coming_from_y(void) const;
    int getDimX(void) const;
    int getDimY(void) const;
    int getDimTxtX(void) const;
    int getDimTxtY(void) const;

    //Mutateurs
    void setLevel(int valeur);
    void setStartX(int valeur);
    void setStartY(int valeur);
    void setTile(int y, int x, int valeur);
    void setNombreMonstres(int valeur);
    void setWarpDirection(int valeur);
    void setWarp_coming_from_x(int valeur);
    void setWarp_coming_from_y(int valeur);

    //Fonctions
    void loadMap(std::string filename);
    void draw(int layer, sf::RenderWindow &window, Monster monster[]);
    void changeLevel(void);
    void testDefilement(void);
    void drawHud(Player &player, sf::RenderWindow &window);
    void drawText(sf::RenderWindow &window, std::string message, int size, int x, int y, sf::Color color); // permet de dessiner un texte en fonction des parametres et de la fonction text de sfml puis de l'afficher

private:
    //Variables de la classe en accès privé

    //Numéro du tileset à utiliser
    int tilesetAffiche;

    /* Coordonnées de départ du héros, lorsqu'il commence le niveau */
    int beginx, beginy;

    // dimensions de la fenêtre texte
    int dimTxtX, dimTxtY;

    /* Coordonnées de début, lorsqu'on doit dessiner la map */
    int startX, startY;

    /* Coordonnées max de fin de la map */
    int maxX, maxY;

    /* Tableau à double dimension représentant la map de tiles */
    int tile[80][80];

    //Deuxième couche de tiles
    int tile2[80][80];

    //Troisième couche de tiles
    int tile3[80][80];

    //Quatrième couche de tiles pour les collisions
    int tile4[80][80];

    /* Timer et numéro du tileset à afficher pour animer la map */
    int mapTimer, tileSetNumber;

    //Numéro du niveau en cours
    int level;

    //Variable pour testDefilement()
    int testdefil;

    //Nouvelles variables pour les A-RPG
    int warpUp, warpDown, warpLeft, warpRight;

    //Pour gérer les warps
    int warpDirection;
    int warp_coming_from_x;
    int warp_coming_from_y;

    //Tilesets
    sf::Texture tileSet1Texture;
    sf::Sprite tileSet1;
    sf::Texture tileSet1BTexture;
    sf::Sprite tileSet1B;

    //Nombre max de monstres à l'écran
    int nombreMonstres;

    //Police de caractères
    sf::Font font;

    //HUD (Informations affichées à l'écran, comme le nombre de coeurs, la magie, etc.)
    sf::Texture HUDTexture;
    sf::Sprite HUD;
    sf::Texture HUDHeartsTexture;
    sf::Sprite HUDHearts;

    /*******************/
    /* Constantes */
    /******************/

    // Taille de la fenêtre : 800x480 pixels
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 480;

    /* Taille maxi de la map : 400 x 150 tiles */
    const int MAX_MAP_X = 80;
    const int MAX_MAP_Y = 80;

    /* Taille d'une tile (32 x 32 pixels) */
    const int TILE_SIZE = 32;

    /* Constante pour l'animation */
    const int TIME_BETWEEN_2_FRAMES = 20;

    //Nombre max de monstres gérés
    const int MONSTRES_MAX = 50;

    //Directions
    const int DOWN = 0;
    const int UP = 1;
    const int RIGHT = 2;
    const int LEFT = 3;

    /*************************/
    /* VALEURS DES TILES */
    /************************/

    const int TILE_MONSTRE_DEBUT = 20;
    const int TILE_MONSTRE_FIN = 39;
};
#endif