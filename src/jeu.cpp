//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "jeu.h"

Jeu::Jeu () {

    //On commence au premier niveau
    map.setLevel(1);
    map.changeLevel();

    //On initialise le player
    player.initialize(map);
    player.setGold(100);

}

Jeu::Jeu (bool musically) {

    musics.PlayMusic(true, musically);
    //On commence au premier niveau
    map.setLevel(1);
    map.changeLevel();

    //On initialise le player
    player.initialize(map);
    player.setGold(100);

}

void Jeu::boucleJeu () {

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "The Legend Of Hilda");
    window.setVerticalSyncEnabled(true);

    // Boucle principale, du jeu
    while (window.isOpen())
    {

        // Gestion des inputs
        input.getInput(window);
        //Updates
        update(window, musics, 1);
        // Dessin - draw
        draw(window);
        window.display();
    }
}

void Jeu::boucleJeuDefil () {

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "The Legend Of Hilda");
    window.setVerticalSyncEnabled(true);

    // Boucle principale, du jeu
    while (window.isOpen())
    {  
        // Gestion des inputs
        input.getInput(window);
        //Updates
        map.testDefilement();
        update(window, musics, 0);
        // Dessin - draw
        draw(window);
        window.display();
    }
}

void Jeu::boucleJeuTxt () {
    // Création d'une fenetre pour l'affichage en mode texte
    // Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WindowTXT win (terrain.getDimTxtX(), terrain.getDimTxtY());

    bool isOpen = true;
    player.setX(1);
    player.setY(1);

	while (isOpen)
    {
        
        // Affichage de l'etat actuel de la fenetre
        winTextAff(win);

        // Gestion des inputs

        int c = win.getCh();
        int dir;
        switch (c) {
			case 'q':
                dir = 3;
				break;
			case 'd':
                dir = 2;
				break;
			case 's':
                dir = 1;
				break;
			case 'z':
                dir = 0;
				break;
			case 'p':
				isOpen = false;
				break;
		}
        //Updates de la fenetre
        update(dir, player); 
        dir = -1;
    }

}

void Jeu::winTextAff(WindowTXT &win) {

	win.clear();

    // Affichage des murs et des pastilles
	for(int x=0;x<terrain.getDimTxtX();++x)
		for(int y=0;y<terrain.getDimTxtY();++y)
            if(terrain.getTileTxt(x, y) == 0)
                win.print(x, y, '.');
			else
                win.print(x, y, '+');

    // Affichage de Hilda
	win.print(player.getX(), player.getY(),'H');

	win.draw();
}

// Fonction du mise à jour du jeu en mode texte
void Jeu::update(int dir, Player &player) {
    switch(dir) {
        case 0:
            if(terrain.getTileTxt(player.getX(), player.getY() - 1) == 0) {
                player.setY(player.getY() - 1);
            }
            break;
        case 1:
            if(terrain.getTileTxt(player.getX(), player.getY() + 1) == 0) {
                player.setY(player.getY() + 1);
            }
            break;
        case 2:
            if(terrain.getTileTxt(player.getX() + 1, player.getY()) == 0) {
                player.setX(player.getX() + 1);
            }
            break;
        case 3:
            if(terrain.getTileTxt(player.getX() - 1, player.getY()) == 0) {
                player.setX(player.getX() - 1);
            }
            break;
    }
}

//Fonction de mise à jour du jeu : gère la logique du jeu
void Jeu::update(RenderWindow &window, Musics &musics, bool isDefil)
{
    
    if (isDefil == 1)
    {
        player.update(input, map);
    }
    for (int i = 0; i < map.getNombreMonstres(); i++)
    {
        
        if (monster[i].update(i, map, player, monster, musics) == 2) // si update renvoie 2, le monstre meurt et on appelle copy
        {

            map.setNombreMonstres(map.getNombreMonstres());
            
        }
    }
}

//Fonction de dessin du jeu : dessine tous les éléments
void Jeu::draw(RenderWindow &window)
{
    //On efface tout
    window.clear();

    // Affiche la map de tiles : layer 2 (couche du fond)
    map.draw(2, window, monster);

    // Affiche la map de tiles : layer 1 (couche active : sol, etc.)
    map.draw(1, window, monster);

    // Affiche le joueur
    drawPlayer(map, window, player);
    
    // Affiche les monstres
    
    for (int i=0; i<= map.getNombreMonstres(); i++)
    {    
        if (monster[i].getLife() > 0)
        monster[i].draw(map, window);
        monster[i].drawCoin(map, window);
        monster[i].getCoin(player, musics);
    }
    

    // Affiche la map de tiles : layer 3 (couche en foreground / devant)
    map.draw(3, window, monster);

    map.drawHud(player, window);
}
