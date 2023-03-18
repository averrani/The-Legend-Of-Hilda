//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Map;
class Player;
class Musics;

class Monster
{
public:

//Constructeur
Monster();

//Accesseurs
int getType(void) const;
int getLife(void) const;
int getLifeMax(void) const;
int getX(void) const;
int getY(void) const;
int getW(void) const;
int getH(void) const;
float getDirX(void) const;
float getDirY(void) const;
int getFrameNumber(void) const;
int getFrameTimer(void) const;
int getFrameMax(void) const;
int getEtat(void) const;
int getDirection(void) const;
int getSaveX(void) const;
int getSaveY(void) const;
int getTimerMort(void) const;
int getIATimer(void) const;
int getInvincibleTimer(void) const;
int getisHurt(void) const;
int getHurtDirection(void) const;

//Mutateurs
void setLife(int valeur);
void setX(int valeur);
void setY(int valeur);
void setW(int valeur);
void setH(int valeur);
void setDirX(float valeur);
void setDirY(float valeur);
void setTimerMort(int valeur);
void setInvincibleTimer(int valeur);
void setisHurt(int valeur);
void setHurtDirection(int valeur);

//Fonctions
void initialize(int Atype, int x1, int y1);
void draw(Map &map, sf::RenderWindow &window);
int update(int monsterNumber, Map &map, Player &player, Monster monster[], Musics &musics);
void mapCollision(Map &map, Player &player);
bool collideBetweenMonsters(Monster &monster);
void copy(Monster &monster); // en cas de mort d'un monstre elle copie le dernier monstre du tableau à la place de celui mort et libere une place
bool collideWithPlayer(Player &player); // teste si le joueur entre en collision avec un monstre
void drawCoin(Map &map, sf::RenderWindow &window);
void getCoin(Player &player, Musics &musics);

private:

// Points de santé et chrono d'invicibilité

float life, lifeMax;
int invincibleTimer;

//type du monstre
int type;

// Pour ne pas récupérer des rubis à l'infini
bool Coined = 1;

//Si le monstre est touché
int isHurt;
int hurtDirection;


//Coordonnées du monstre

int x, y;

//Largeur, hauteur du monstre

int h, w;

// Checkpoint pour le héros (actif ou non)

int checkpointActif;

// coordonnées de respawn

int respawnX, respawnY;

// Numéro de la frame en cours et timer

int frameNumber, frameTimer, frameMax;

// état du sprite et direction dans laquelle il se déplace 

int etat, direction;

//Timer pour le monstre

int IATimer;

// chrono du monstre mort

int timerMort;


// vecteur de collision avec la map

float dirX, dirY;

//Sauvegarde des coordonnées de départ

int saveX, saveY;

//Spritesheet

sf::Texture Texture[2];
sf::Sprite Sprite[2];
sf::Texture coinTexture;
sf::Sprite coin;

int numberOfDifferentMonsters;

// Taille maxi de la map : 400 x 150 tiles 

const int MAX_MAP_X = 400;
const int MAX_MAP_Y = 150;

// Taille d'une tile (32 x 32 pixels) 

const int TILE_SIZE = 32;

// Constante pour l'animation 

const int TIME_BETWEEN_2_FRAMES_PLAYER = 4;

//Dimensions du monstre

const int MONSTER_WIDTH = 42;
const int MONSTER_HEIGTH = 42;

//Valeurs d'état

const int IDLE = 0;
const int WALK = 1;
const int DEAD = 4;
const int DOWN = 0;
const int UP = 1;
const int RIGHT = 2;
const int LEFT = 3;

const int IATime = 50;
const int TIME_BETWEEN_2_SHOTS = 30;
const int BACK_TIMER = 8;

// Taille de la fenêtre : 800x480 pixels

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

};

#endif

