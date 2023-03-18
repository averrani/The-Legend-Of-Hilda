//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "monster.h"
#include "player.h"
#include "map.h"
#include "music.h"

using namespace std;
using namespace sf;

//Constructeur
Monster::Monster()
{
    numberOfDifferentMonsters = 2;
    for (int i = 0; i < numberOfDifferentMonsters; i++)
    {
        if (!Texture[i].loadFromFile("data/graphics/monster" + to_string(i + 1) + ".png"))
        {
            cout << "Erreur lors duchargement des monstres" << endl;
        }

        else
            Sprite[i].setTexture(Texture[i]);
    }
    if (!coinTexture.loadFromFile("data/graphics/piece.png"))
    {
        cout << "Erreur durant le chargement du sprite des pièces." << endl;
    }
    else
        coin.setTexture(coinTexture);

    type = 1;
    dirX = 0;
    dirY = 0;
    life = lifeMax = 1;
    invincibleTimer = 0;
    x = y = 0;
    h = w = 42;
    checkpointActif = respawnX = respawnY = 0;
    frameNumber = frameTimer = frameMax = 0;
    etat = direction = 0;
    timerMort = 0;
    dirX = dirY = 0;
    saveX = saveY = 0;
    IATimer = IATime;
}

//Accesseurs
int Monster::getType(void) const { return type; }
int Monster::getLife(void) const { return life; }
int Monster::getLifeMax(void) const { return lifeMax; }
int Monster::getX(void) const { return x; }
int Monster::getY(void) const { return y; }
int Monster::getW(void) const { return w; }
int Monster::getH(void) const { return h; }
float Monster::getDirX(void) const { return dirX; }
float Monster::getDirY(void) const { return dirY; }
int Monster::getFrameNumber(void) const { return frameNumber; }
int Monster::getFrameTimer(void) const { return frameTimer; }
int Monster::getFrameMax(void) const { return frameMax; }
int Monster::getEtat(void) const { return etat; }
int Monster::getDirection(void) const { return direction; }
int Monster::getSaveX(void) const { return saveX; }
int Monster::getSaveY(void) const { return saveY; }
int Monster::getTimerMort(void) const { return timerMort; }
int Monster::getIATimer(void) const { return IATimer; }
int Monster::getInvincibleTimer(void) const { return invincibleTimer; }
int Monster::getisHurt(void) const { return isHurt; }
int Monster::getHurtDirection(void) const { return hurtDirection; }

//Mutateurs
void Monster::setLife(int valeur) { life = valeur; }
void Monster::setX(int valeur) { x = valeur; }
void Monster::setY(int valeur) { y = valeur; }
void Monster::setW(int valeur) { w = valeur; }
void Monster::setH(int valeur) { h = valeur; }
void Monster::setDirX(float valeur) { dirX = valeur; }
void Monster::setDirY(float valeur) { dirY = valeur; }
void Monster::setTimerMort(int valeur) { timerMort = valeur; }
void Monster::setInvincibleTimer(int valeur) { invincibleTimer = valeur; }
void Monster::setisHurt(int valeur) { isHurt = valeur; }
void Monster::setHurtDirection(int valeur) { hurtDirection = valeur; }

//Fonctions
void Monster::initialize(int MonsterType, int x1, int y1)
{

    frameNumber = 0;
    frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
    frameMax = 8;
    type = MonsterType;

    if (type == 1)

        life = lifeMax = 2;

    else if (type == 2)

        life = lifeMax = 3;

    invincibleTimer = 0;

    direction = LEFT;
    x = x1;
    y = y1;
    w = MONSTER_WIDTH;
    h = MONSTER_HEIGTH;

    timerMort = 0;
    etat = 0;
    isHurt = 0;
    hurtDirection = 0;
}

void Monster::draw(Map &map, RenderWindow &window)

{
    if (frameTimer <= 0)

    {
        frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
        frameNumber++;
        if (frameNumber >= frameMax)
            frameNumber = 0;
    }

    else
        frameTimer--;
    Sprite[type - 1].setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));

    if (direction == LEFT)
    {
        Sprite[type - 1].setTextureRect(sf::IntRect(frameNumber * w, (etat * 3 * h + (direction - 1) * h),w, h));
        window.draw(Sprite[type - 1]);
    }

    else

    {
        Sprite[type - 1].setTextureRect(sf::IntRect((frameNumber + 1) * w,(etat * 3 * h + direction * h),-w, h));
        window.draw(Sprite[type - 1]);
    }

}

int Monster::update(int monsterNumber, Map &map, Player &player, Monster monster[], Musics &musics)

{   //même fonction que update de player
    if (timerMort == 0 && life > 0)
    {
        if (invincibleTimer > 0)
            invincibleTimer--;
        if (isHurt > 0)
            isHurt--;
        dirX = 0;
        dirY = 0;
        if (x == saveX && isHurt == 0)
        {
           if (direction == LEFT)
            {
                direction = RIGHT;
                if (y == saveY && direction == UP)
                    y += 1;
                else if (y == saveY && direction == DOWN)
                    y -= 1;
            }
            else if (direction == RIGHT)
            {
                direction = LEFT;
                if (y == saveY && direction == UP)
                    y += 1;
                else if (y == saveY && direction == DOWN)
                    y -= 1;
            }
        }

        else if (y == saveY)
        {
            if (direction == UP)
            {
                direction = DOWN;
                if (x == saveX && direction == LEFT)
                    x += 1;
                else if (x == saveX && direction == RIGHT)
                    x -= 1;
            }

            else if (direction == DOWN)
            {

                direction = UP;
                if (x == saveX && direction == LEFT)
                    x += 1;
                else if (x == saveX && direction == RIGHT)
                    x -= 1;
            }
        }

        if (IATimer <= 0 && isHurt == 0)

        {
            direction = rand() % 4;
            IATimer = IATime;
        }

        else
            IATimer--;

        if (isHurt > 0)

        {

            if (hurtDirection == LEFT)
                dirX -= 10;
            else if (hurtDirection == RIGHT)
                dirX += 10;
            else if (hurtDirection == UP)
                dirY -= 10;
            else if (hurtDirection == DOWN)
                dirY += 10;
        }

        else

        {
            if (direction == LEFT)
                dirX -= 1;
            else if (direction == RIGHT)
                dirX += 1;
            else if (direction == UP)
                dirY -= 1;
            else if (direction == DOWN)
                dirY += 1;
        }

        saveX = x;
        saveY = y;
        mapCollision(map, player);
    }

    // Détection des collisions avec le joueur 
    if (collideWithPlayer(player) && life > 0)
    {
        // Si il a plus d'un coeur, il est blessé
        if (player.getLife() >= 1)
        {
            player.HurtPlayer(musics);
        }
        else
        // Sinon il meurt
        {
            player.killPlayer(musics);
            player.setGold(player.getGold()-10);
            //ajouter animation mort
        }
    }
    
    //Si il y'a collision entre monstre et épée
    if (player.CollisionWithSword(x, y, w, h))
    {
        if (invincibleTimer == 0)
        {
            life--;
            if (life <= 0)
                timerMort = 1;
            invincibleTimer = TIME_BETWEEN_2_SHOTS;
            musics.PlaySound(musics.DESTROY);
        }

        // le monstre est touché, donc il recule avec la force de l'épée
        isHurt = BACK_TIMER;

        // Selon une direction précise
        if (player.getDirection() == DOWN)
            hurtDirection = DOWN;
        else if (player.getDirection() == UP)
            hurtDirection = UP;
        else if (player.getDirection() == RIGHT)
            hurtDirection = RIGHT;
        else if (player.getDirection() == LEFT)
            hurtDirection = LEFT;
    }

    for (int i = 0; i < map.getNombreMonstres(); i++)

    {
        if (i != monsterNumber)
            if (collideBetweenMonsters(monster[i]))
            {
                if (direction == UP)
                {
                    direction = DOWN;
                    y = monster[i].getY() + monster[i].getH() + 1;
                }
                else if (direction == DOWN)
                {
                    direction = UP;
                    y = monster[i].getY() - h - 1;
                }
                else if (direction == RIGHT)
                {
                    direction = LEFT;
                    x = monster[i].getX() - w - 1;
                }
                else if (direction == LEFT)
                {
                    direction = RIGHT;
                    x = monster[i].getX() + monster[i].getW() + 1;
                }
            }
    }

    if (timerMort > 0)

    {
        timerMort--;
        if (timerMort == 0)
            return 2;
        else
            return 0;
    }
    else
        return 0;
}

void Monster::mapCollision(Map &map, Player &player)

{
    int i, x1, x2, y1, y2;
    if (h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = h;
    for (;;)
    {
        x1 = (x + dirX) / TILE_SIZE;
        x2 = (x + dirX + w - 1) / TILE_SIZE;
        y1 = (y) / TILE_SIZE;
        y2 = (y + i - 1) / TILE_SIZE;
        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (dirX > 0)
            {
                if (map.getTile(y1, x2) == 1 || map.getTile(y2, x2) == 1)
                {
                    x = x2 * TILE_SIZE;
                    x -= (w + 1);
                    dirX = 0;
                }
            }
            else if (dirX < 0)
            {
                if (map.getTile(y1, x1) == 1 || map.getTile(y2, x1) == 1)
                {
                    x = (x1 + 1) * TILE_SIZE;
                    dirX = 0;
                }
            }
        }
        if (i == h)
        {
            break;
        }
        i += TILE_SIZE;
        if (i > h)
        {
            i = h;
        }
    }
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
                if (map.getTile(y2, x1) == 1 || map.getTile(y2, x2) == 1)
                {
                    y = y2 * TILE_SIZE;
                    y -= (h + 1);
                    dirY = 0;
                }
            }
            else if (dirY < 0)
            {
                if (map.getTile(y1, x1) == 1 || map.getTile(y1, x2) == 1)
                {
                    y = (y1 + 1) * TILE_SIZE;
                    dirY = 0;
                }
            }
        }
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
    x += dirX;
    y += dirY;
    if (x < 0)
        x = 0;
    else if (x + w >= map.getMaxX())
        x = map.getMaxX() - w;
    else if (y < 0)
        y = 0;
    else if (y + h > map.getMaxY())
        y = map.getMaxY() - h;
}

bool Monster::collideBetweenMonsters(Monster &monster)
{
    if ((monster.getX() >= x + w) || (monster.getX() + monster.getW() <= x)
        || (monster.getY() >= y + h) || (monster.getY() + monster.getH() <= y)
    )
        return false;
    else
        return true;
}

void Monster::copy(Monster &monster)

{
    type = monster.getType();
    life = monster.getLife();
    lifeMax = monster.getLifeMax();
    dirX = monster.getDirX();
    dirY = monster.getDirY();
    isHurt = monster.getisHurt();
    hurtDirection = monster.getHurtDirection();
    x = monster.getX();
    y = monster.getY();
    h = monster.getH();
    w = monster.getW();
    frameNumber = monster.getFrameNumber();
    frameTimer = monster.getFrameTimer();
    frameMax = monster.getFrameMax();
    etat = monster.getEtat();
    direction = monster.getDirection();
    saveX = monster.getSaveX();
    saveY = monster.getSaveY();
    timerMort = monster.getTimerMort();
    IATimer = monster.getIATimer();
    invincibleTimer = monster.getInvincibleTimer();
}

bool Monster::collideWithPlayer(Player &player)
{
    //Vérifie toutes les possibilités ou les coordonnées du joueur entrent en contact avec celles du monstre
    if ((player.getX() >= x + w) || (player.getX() + player.getW() <= x) || (player.getY() >= y + h) || (player.getY() + player.getH() <= y))
        return false;
    else
        return true;
}

void Monster::drawCoin(Map &map, RenderWindow &window)

{
    if (life==0)
    {
        coin.setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));
        window.draw(coin);
    }
                
}

void Monster::getCoin(Player &player, Musics &musics)

{
    if (collideWithPlayer(player) && life <= 0 && Coined == 1)
    {
        coin.setColor(sf::Color::Transparent);
        player.setGold(player.getGold()+ 1 + rand()%50);
        musics.PlaySound(musics.COIN);
        Coined = 0;
    }
                
}
