//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "player.h"
#include "music.h"

using namespace std;
using namespace sf;

//Constructeur

Player::Player()
{
    //Chargement de la spritesheet du héros et de l'épée
    //et initialisation des variables d'animation
    loadPlayer(*this);

    //Initialisation des autres variables
    dirX = 0;
    dirY = 0;
    life = 3;
    invincibleTimer = 0;
    x = y = h = w = 0;
    dirX = dirY = 0;
    timerMort = 0;
    saveX = saveY = 0;
}

//Accesseurs
int Player::getX(void) const { return x; }
int Player::getY(void) const { return y; }
int Player::getW(void) const { return w; }
int Player::getH(void) const { return h; }
float Player::getDirX(void) const { return dirX; }
float Player::getDirY(void) const { return dirY; }
int Player::getLife(void) const { return life; }
int Player::getGold(void) const { return gold; }
int Player::getDirection(void) const { return direction; }

//Mutateurs
void Player::setX(int valeur) { x = valeur; }
void Player::setY(int valeur) { y = valeur; }
void Player::setW(int valeur) { w = valeur; }
void Player::setH(int valeur) { h = valeur; }
void Player::setDirX(float valeur) { dirX = valeur; }
void Player::setDirY(float valeur) { dirY = valeur; }
void Player::setGold(int valeur) { gold = valeur; }

//Fonctions
void Player::initialize(Map &map)
{
    // Initialise les variables utiles à l'animation
    initPlayer(*this);

    //PV à 3 coeurs
    life = 3;

    //Timer d'invincibilité à 0
    invincibleTimer = 0;

    //On démarre au début de la map
    x = map.getBeginX();
    y = map.getBeginY();

    //On place l'épée par rapport au joueur
    swordX = x + 30;
    swordY = y + 45;

    //On initialise la caméra
    map.setStartX(0);
    map.setStartY(0);

    /* Hauteur et largeur de notre héros */
    w = PLAYER_WIDTH;
    h = PLAYER_HEIGTH;

    //Variables nécessaires au fonctionnement de la gestion des collisions
    timerMort = 0;
    isAttacking = 0;
    map.setNombreMonstres(0);
    map.setWarpDirection(-1);
}

void Player::update(Input &input, Map &map)
{
    //On rajoute un timer au cas où notre héros mourrait lamentablement...
    //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
    //on réinitialise.
    //C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0.
    if (timerMort == 0)
    {
        //On gère le timer de l'invincibilité
        if (invincibleTimer > 0)
            invincibleTimer--;

        //On réinitialise nos vecteurs de déplacement, pour éviter que le perso
        //ne fonce de plus en plus vite pour atteindre la vitesse de la lumière ! ;)
        //Essayez de le désactiver pour voir !
        dirX = 0;
        dirY = 0;

        //Gestion de la course en appuyant sur la touche courir
        if (input.getButton().run)
            isrunning = 1;
        else
            isrunning = 0;

        //Voilà, au lieu de changer directement les coordonnées du joueur, on passe par un vecteur
        //qui sera utilisé par la fonction mapCollision(), qui regardera si on peut ou pas déplacer
        //le joueur selon ce vecteur et changera les coordonnées du player en fonction.
        if (input.getButton().left == true)
        {
            dirX -= PLAYER_SPEED + isrunning;

            // Appel à la fonction qui modifie les variables concernées
            // et gère la boucle d'animation
            updatePlayer(*this, LEFT);
        }

        //Si on détecte un appui sur la touche fléchée droite
        else if (input.getButton().right == true)
        {
            //On augmente les coordonnées en x du joueur
            dirX += PLAYER_SPEED + isrunning;
            updatePlayer(*this, RIGHT);
        }

        //Si on détecte un appui sur la touche fléchée haut
        else if (input.getButton().up == true)
        {
            //On augmente les coordonnées en x du joueur
            dirY -= PLAYER_SPEED + isrunning;

            // Appel à la fonction qui modifie les variables concernées
            // et gère la boucle d'animation
            updatePlayer(*this, UP);
        }

        //Si on détecte un appui sur la touche fléchée bas
        else if (input.getButton().down == true)
        {
            //On augmente les coordonnées en x du joueur
            dirY += PLAYER_SPEED + isrunning;

            // Appel à la fonction qui modifie les variables concernées
            // et gère la boucle d'animation
            updatePlayer(*this, DOWN);
        }

        //Si on n'appuie sur rien, on charge l'animation marquant l'inactivité (Idle)
        else if (input.getButton().right == false && input.getButton().left == false &&
                 input.getButton().up == false && input.getButton().down == false)
        {
            updatePlayer(*this, -1);
        }

        // Si le joueur appuie sur la touche d'attaque
        if (input.getButton().attack)
        {
            isAttacking = 1;
            input.setButton(attack, false);
        }

        //On rajoute notre fonction de détection des collisions qui va mettre à
        //jour les coordonnées de notre héros.
        mapCollision(map);

        //On gère le scrolling (fonction ci-dessous)
        centerScrolling(map);

    }

    //Gestion de la mort :
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
    // timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (timerMort > 0)
    {
        timerMort--;

        if (timerMort == 0)
        {

            // Si on est mort, on réinitialise le niveau
            map.changeLevel();
            initialize(map);
        }
    }
}

/*void Player::ennemyCollision(Monster &monster)
{
    // on teste si un ennemi est en contact avec Link
    // le cas échéant, on enlève un coeur à Link
    if(x );
}*/

void Player::centerScrolling(Map &map)
{
    // Nouveau scrolling à sous-boîte limite :
    //Pour éviter les effets de saccades dus à une caméra qui se
    //centre automatiquement et constamment sur le joueur (ce qui
    //peut en rendre malade certains...), on crée une "boîte" imaginaire
    //autour du joueur. Quand on dépasse un de ses bords (en haut, en bas,
    //à gauche ou à droite), on scrolle.
    //Mais là encore, au lieu de centrer sur le joueur, on déplace simplement
    //la caméra jusqu'à arriver au joueur. On a changé ici la valeur à 4 pixels
    //pour que le jeu soit plus rapide.
    int cxperso = x + w / 2;
    int cyperso = y + h / 2;
    int xlimmin = map.getStartX() + LIMITE_X;
    int xlimmax = xlimmin + LIMITE_W;
    int ylimmin = map.getStartY() + LIMITE_Y;
    int ylimmax = ylimmin + LIMITE_H;

    //Effet de retour en arrière quand on est mort :
    //Si on est très loin de la caméra, plus loin que le bord
    //de la map, on accélère le scrolling :
    if (cxperso < map.getStartX())
    {
        map.setStartX(map.getStartX() - 30);
    }

    //Si on dépasse par la gauche, on recule la caméra
    else if (cxperso < xlimmin)
    {
        map.setStartX(map.getStartX() - 3 - isrunning);
    }

    //Effet de retour en avant quand on est mort (au
    //cas où le joueur s'amuse à faire le niveau à rebours
    //après une checkpoint) :
    //Si on est très loin de la caméra, plus loin que le bord
    //de la map, on accélère le scrolling :
    if (cxperso > map.getStartX() + SCREEN_WIDTH)
    {
        map.setStartX(map.getStartX() + 30);
    }

    //Si on dépasse par la droite, on avance la caméra
    else if (cxperso > xlimmax)
    {
        map.setStartX(map.getStartX() + 3 + isrunning);
    }

    //Si on arrive au bout de la map à gauche, on stoppe le scrolling
    if (map.getStartX() < 0)
    {
        map.setStartX(0);
    }

    //Si on arrive au bout de la map à droite, on stoppe le scrolling à la
    //valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (map.getStartX() + SCREEN_WIDTH >= map.getMaxX())
    {
        map.setStartX(map.getMaxX() - SCREEN_WIDTH);
    }

    //Si on dépasse par le haut, on remonte la caméra
    if (cyperso < ylimmin)
    {
        map.setStartY(map.getStartY() - 3 - isrunning);
    }

    //Si on dépasse par le bas, on descend la caméra
    if (cyperso > ylimmax)
    {
        map.setStartY(map.getStartY() + 3 + isrunning);
    }

    //Si on arrive au bout de la map en haut, on stoppe le scrolling
    if (map.getStartY() < 0)
    {
        map.setStartY(0);
    }

    //Si on arrive au bout de la map en bas, on stoppe le scrolling à la
    //valeur Max de la map - la moitié d'un écran (pour ne pas afficher du noir).
    else if (map.getStartY() + SCREEN_HEIGHT >= map.getMaxY())
    {
        map.setStartY(map.getMaxY() - SCREEN_HEIGHT);
    }
}
void Player::mapCollision(Map &map)
{

    int i, x1, x2, y1, y2;

    /* Ensuite, on va tester les mouvements horizontaux en premier
(axe des X). On va se servir de i comme compteur pour notre boucle.
En fait, on va découper notre sprite en blocs de tiles pour voir
quelles tiles il est susceptible de recouvrir.
On va donc commencer en donnant la valeur de Tile_Size à i pour qu'il
teste la tile où se trouve le x du joueur mais aussi la suivante SAUF
dans le cas où notre sprite serait inférieur à la taille d'une tile.
Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
Et on testera ensuite 2 fois la même tile. Mais comme ça notre code
sera opérationnel quelle que soit la taille de nos sprites ! */

    if (h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = h;

    //On lance alors une boucle for infinie car on l'interrompra selon
    //les résultats de nos calculs
    for (;;)
    {
        //On va calculer ici les coins de notre sprite à gauche et à
        //droite pour voir quelle tile ils touchent.
        x1 = (x + dirX) / TILE_SIZE;
        x2 = (x + dirX + w - 1) / TILE_SIZE;

        //Même chose avec y, sauf qu'on va descendre au fur et à mesure
        //pour tester toute la hauteur de notre sprite, grâce à notre
        //fameuse variable i.
        y1 = (y) / TILE_SIZE;
        y2 = (y + i - 1) / TILE_SIZE;

        //De là, on va tester les mouvements initiés dans updatePlayer
        //grâce aux vecteurs dirX et dirY, tout en testant avant qu'on
        //se situe bien dans les limites de l'écran.
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite
            if (dirX > 0)
            {
                //On vérifie si les tiles recouvertes sont solides
                if (map.getTile(y1, x2) == MUR || map.getTile(y2, x2) == MUR)
                {
                    // Si c'est le cas, on place le joueur aussi près que possible
                    // de ces tiles, en mettant à jour ses coordonnées. Enfin, on
                    //réinitialise son vecteur déplacement (dirX).

                    x = x2 * TILE_SIZE;
                    x -= (w + 1);
                    dirX = 0;
                }
            }

            //Même chose à gauche
            else if (dirX < 0)
            {
                if (map.getTile(y1, x1) == MUR || map.getTile(y2, x1) == MUR)
                {
                    x = (x1 + 1) * TILE_SIZE;
                    dirX = 0;
                }
            }
        }

        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == h)
        {
            break;
        }

        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TILE_SIZE;

        if (i > h)
        {
            i = h;
        }
    }

    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if (w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = w;

    for (;;)
    {
        x1 = (x) / TILE_SIZE;
        x2 = (x + i) / TILE_SIZE;

        y1 = (y + dirY) / TILE_SIZE;
        y2 = (y + dirY + h) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (dirY > 0)
            {
                // Déplacement en bas
                if (map.getTile(y2, x1) == MUR || map.getTile(y2, x2) == MUR)
                {
                    //Si la tile est une tile solide, on y colle le joueur
                    y = y2 * TILE_SIZE;
                    y -= (h + 1);
                    dirY = 0;
                }
            }

            else if (dirY < 0)
            {

                // Déplacement vers le haut
                if (map.getTile(y1, x1) == MUR || map.getTile(y1, x2) == MUR)
                {
                    y = (y1 + 1) * TILE_SIZE;
                    dirY = 0;
                }
            }
        }

        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
        if (i == w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > w)
        {
            i = w;
        }
    }

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    x += dirX;
    y += dirY;
    swordX += dirX;
    swordY += dirY;

    //Si on touche les bords de l'écran, on warp au niveau indiqué
    //si celui-ci est différent de 0
    if (x < 0)
    {
        //On stoppe le joueur
        x = 0;

        //On teste si on doit warper à gauche
        if (map.getWarpLeft() > 0)
        {
            //On enregistre la direction du warp et les coordonnées du joueur
            map.setWarpDirection(LEFT);
            map.setWarp_coming_from_x(x);
            map.setWarp_coming_from_y(y);

            //On change de level
            map.setLevel(map.getWarpLeft());
            map.changeLevel();
            reinitialize(map);
        }
    }

    else if (x + w >= map.getMaxX())
    {
        //On stoppe le joueur
        x = map.getMaxX() - w;

        //On teste si on doit warper à droite
        if (map.getWarpRight() > 0)
        {
            //On enregistre la direction du warp et les coordonnées du joueur
            map.setWarpDirection(RIGHT);
            map.setWarp_coming_from_x(x);
            map.setWarp_coming_from_y(y);

            //On change de level
            map.setLevel(map.getWarpRight());
            map.changeLevel();
            reinitialize(map);
        }
    }

    else if (y < 0)
    {
        //On stoppe le joueur
        y = 0;

        //On teste si on doit warper en haut
        if (map.getWarpUp() > 0)
        {
            //On enregistre la direction du warp et les coordonnées du joueur
            map.setWarpDirection(UP);
            map.setWarp_coming_from_x(x);
            map.setWarp_coming_from_y(y);

            //On change de level
            map.setLevel(map.getWarpUp());
            map.changeLevel();
            reinitialize(map);
        }
    }

    else if (y + h > map.getMaxY())
    {
        //On stoppe le joueur
        y = map.getMaxY() - h;

        //On teste si on doit warper en bas
        if (map.getWarpDown() > 0)
        {
            //On enregistre la direction du warp et les coordonnées du joueur
            map.setWarpDirection(DOWN);
            map.setWarp_coming_from_x(x);
            map.setWarp_coming_from_y(y);

            //On change de level
            map.setLevel(map.getWarpDown());
            map.changeLevel();
            reinitialize(map);
        }
    }
}

void Player::reinitialize(Map &map)
{

    // Coordonnées de démarrage de notre héros selon la direction de warp
    //Si on n'a pas warpé, alors on commence aux coordonnées de départ de la map
    if (map.getWarpDirection() == -1)
    {
        x = map.getBeginX();
        y = map.getBeginY();

        //On recentre la caméra
        map.setStartX(map.getBeginX() - (SCREEN_WIDTH / 2));
        map.setStartY(map.getBeginY() - (SCREEN_HEIGHT / 2));
    }
    //Si on a warpé en haut
    else if (map.getWarpDirection() == UP)
    {
        //On change la valeur en y du héros pour qu'il se
        //trouve en bas de la map
        y = map.getMaxY() - h - 1;

        //On recentre la caméra
        map.setStartY(map.getMaxY() - SCREEN_HEIGHT);
    }
    //Si on a warpé en bas
    else if (map.getWarpDirection() == DOWN)
    {
        //On change la valeur en y du héros pour qu'il se
        //trouve en haut de la map
        y = 1;

        //On recentre la caméra
        map.setStartY(0);
    }
    //Si on a warpé à gauche
    else if (map.getWarpDirection() == LEFT)
    {
        //On change la valeur en x du héros pour qu'il se
        //trouve à droite de la map
        x = map.getMaxX() - w - 1;

        //On recentre la caméra
        map.setStartX(map.getMaxX() - SCREEN_WIDTH);
    }
    //Si on a warpé à droite
    else if (map.getWarpDirection() == RIGHT)
    {
        //On change la valeur en x du héros pour qu'il se
        //trouve à gauche de la map
        x = 1;

        //On recentre la caméra
        map.setStartX(0);
    }
    map.setNombreMonstres(0);
}

void Player::UpdateSword(Map &map, RenderWindow &window)
{

    // Partie qui s'occupe de placer l'épée au repos par rapport au joueur
    if (direction == DOWN)
    {
        swordX = x + 20 - map.getStartX();
        swordY = y + 30 - map.getStartY();
    }
    else if (direction == UP)
    {
        swordX = x + 24 - map.getStartX();
        swordY = y + 28 - map.getStartY();
    }
    else if (direction == RIGHT)
    {
        swordX = x + 20 - map.getStartX();
        swordY = y + 44 - map.getStartY();
    }
    else if (direction == LEFT)
    {
        swordX = x + 20 - map.getStartX();
        swordY = y + 24 - map.getStartY();
    }

    sword.setPosition(swordX, swordY);

    //Partie qui s'occupe de la rotation de l'épée en fonction de la direction
    sword.setOrigin(0, 0);

    if (direction == DOWN)

        sword.setRotation(  swordRotation);

    else if (direction == UP)

        sword.setRotation(swordRotation - 200);

    else if (direction == RIGHT)

        sword.setRotation(swordRotation - 135);

    else if (direction == LEFT)

        sword.setRotation(swordRotation + 45);

    window.draw(sword);

    // Partie qui s'occupe de remettre en place l'épée après l'attaque
    if (swordTimer <= 0)
    {
        swordTimer = TIME_BETWEEN_2_FRAMES_SWORD;

        swordRotation += 10; // 10 degrés, pour pas que le mouvement de l'épée soit trop rapide

        if (swordRotation > 80) // arret de l'attaque
        {
            swordRotation = 0;
            isAttacking = 0;
        }
    }
    else
        swordTimer--;
}

void Player::killPlayer(Musics &musics)
{
    timerMort = 1;

    musics.PlaySound(musics.HURT);
}

void Player::HurtPlayer(Musics &musics)
{
    if (invincibleTimer == 0)
    {
        life--;
        invincibleTimer = 80;
        musics.PlaySound(musics.HURT);
    }
}

bool Player::CollisionWithSword(int x1, int y1, int w1, int h1)
{
    // Coordonnées du rectangle représentant l'épée qui sera pris en compte pour les collisions
    int swordX, swordY, swordW, swordH;

    if (isAttacking)
    {
        if (direction == UP)
        {
            swordX = x - 10;
            swordY = y - 28;
            swordW = w + 20;
            swordH = 28;
        }
        else if (direction == DOWN)
        {
            swordX = x - 10;
            swordY = y + h;
            swordW = w + 20;
            swordH = 28;
        }
        if (direction == RIGHT)
        {
            swordX = x + w;
            swordY = y - 10;
            swordW = 28;
            swordH = h + 20;
        }
        else if (direction == LEFT)
        {
            swordX = x - 28;
            swordY = y - 10;
            swordW = 28;
            swordH = h + 20;
        }

        if ((swordX >= x1 + w1) || (swordX + swordW <= x1) || (swordY >= y1 + h1) || (swordY + swordH <= y1))
            return false;
        else
            return true;
    }
    else
        return false;
}