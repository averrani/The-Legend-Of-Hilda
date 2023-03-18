//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "dessin.h"

using namespace std;
using namespace sf;

// Fonction appelée par le constructeur de la classe Player
void loadPlayer(Player &player)
{
    // Chargement des spritesheet du héros

    if (!player.heroTexture.loadFromFile("data/graphics/hero.png"))
    {
        cout << "Erreur durant le chargement du spritesheet du héros." << endl;
    }
    else
        player.hero.setTexture(player.heroTexture);

    // Et de ceux de l'épée

    if (!player.swordTexture.loadFromFile("data/graphics/sword.png"))
    {
        cout << "Erreur durant le chargement du sprite de l'épée." << endl;
    }
    else
        player.sword.setTexture(player.swordTexture);

    // Construction des variables utiles à l'animation

    player.frameNumber = player.frameTimer = player.frameMax = 0;
    player.etat = player.direction = 0;
    player.swordTimer = player.swordRotation = 0;
}

// Fonction appelée dans Player::initialize pour
// donner des valeurs utiles aux variables utiles à l'animation
void initPlayer(Player &player)
{

    // Indique dans quelle direction commencer
    player.direction = RIGHT;

    // Indique quelle boucle d'animation commencer
    player.etat = IDLE;

    // Indique le numéro de la player.frame où commencer
    player.frameNumber = 0;

    // Indique combien de temps attendre avant de
    // changer la player.frame du joueur
    player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

    // Indique au bout de combien de player.frame recommencer
    // la boucle d'animation
    player.frameMax = 8;

    // Indique quelle position et angle donner à l'épée
    player.swordTimer = 0;
    player.swordRotation = 0;
}

void updatePlayer(Player &player, int dir)
{
    if (dir == -1)
    {
        //On teste si le joueur n'était pas déjà inactif, pour ne pas recharger l'animation
        //à chaque tour de boucle
        if (player.etat != IDLE)
        {
            //On enregistre l'anim' de l'inactivité et on l'initialise à 0
            player.etat = IDLE;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 8;
        }
    }
    else
    {
        player.direction = dir;
        //Si le joueur n'était pas déjà en train de marcher
        if (player.etat != WALK)
        {
            //On enregistre l'anim' de la marche et on l'initialise à 0
            player.etat = WALK;
            player.frameNumber = 0;
            player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
            player.frameMax = 8;
        }
    }
}

void drawPlayer(Map &map, sf::RenderWindow &window, Player &player)
{
    /* Gestion du timer */
    // Si notre timer (un compte à rebours en fait) arrive à zéro
    if (player.frameTimer <= 0)
    {
        //On le réinitialise
        player.frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

        //Et on incrémente notre variable qui compte les player.frames de 1 pour passer à la suivante
        player.frameNumber++;

        //Mais si on dépasse la frame max, il faut revenir à la première :
        if (player.frameNumber >= player.frameMax)
            player.frameNumber = 0;
    }
    //Sinon, on décrémente notre timer
    else
    {
        if (player.etat != IDLE)
            player.frameTimer -= 1 + (player.isrunning * 2);
        else
            player.frameTimer--;
    }

    //On place le joueur correctement sur la map
    player.hero.setPosition(Vector2f(player.getX() - map.getStartX(), player.getY() - map.getStartY()));

    if (player.isAttacking == 1 && player.direction == UP) // permet de dessiner l'épée derrière Link quand celui ci regarde en haut
            player.UpdateSword(map, window);

    //Pour connaître le X de la bonne player.frame à dessiner, il suffit de multiplier
    //la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
    //On calcule le Y de la bonne frame à dessiner, selon la valeur de l'état du héros :
    //Aucun Mouvement (Idle) = 0, marche (walk) = 1, etc...
    //Tout cela en accord avec notre spritesheet, of course ;)

    //Si on a été touché et qu'on est invincible
    if (player.invincibleTimer > 0)
    {
        //On fait clignoter le héros une frame sur deux
        //Pour ça, on calcule si le numéro de la frame en
        //cours est un multiple de deux
        if (player.frameNumber % 2 == 0)
        {
            //Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche)
            if (player.direction == LEFT)
            {
                player.hero.setTextureRect(sf::IntRect(
                    player.frameNumber * player.getW(),
                    (player.etat * 3 * player.getH() + (player.direction - 1) * player.getH()
                    + player.isAttacking * 6 * player.getH()),
                    player.getW(), player.getH()));
                window.draw(player.hero);
            }
            else
            {
                //On n'a plus de flip auto en SFML, il faut donc tout calculer
                player.hero.setTextureRect(sf::IntRect(
                    (player.frameNumber + 1) * player.getW(),
                    (player.etat * 3 * player.getH() + player.direction * player.getH()
                    + player.isAttacking * 6 * player.getH()),
                    -player.getW(), player.getH()));
                window.draw(player.hero);
            }
        }
        //Sinon, on ne dessine rien, pour le faire clignoter
    }

    //Sinon, on dessine normalement
    else
    {
        //Gestion du flip (retournement de l'image selon que le sprite regarde à droite ou à gauche)
        if (player.direction == LEFT)
        {
            player.hero.setTextureRect(sf::IntRect(
                player.frameNumber * player.getW(),
                (player.etat * 3 * player.getH() + (player.direction - 1) * player.getH() + player.isAttacking * 6 * player.getH()),
                player.getW(), player.getH()));
            window.draw(player.hero);
        }
        else   
        {
            //On n'a plus de flip auto en SFML, il faut donc tout calculer
            player.hero.setTextureRect(sf::IntRect(
                (player.frameNumber + 1) * player.getW(),
                (player.etat * 3 * player.getH() + player.direction * player.getH() + player.isAttacking * 6 * player.getH()),
                -player.getW(), player.getH()));
            window.draw(player.hero);
        }
    }
    // Dessine l'épée apres le sprite du héros sauf lorsque il voit vers le haut (déjà fait en haut)
    if (player.isAttacking == 1 && player.direction != UP)
            player.UpdateSword(map, window);
}