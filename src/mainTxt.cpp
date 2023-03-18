//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "jeu.h"

int main(int argc, char *argv[])
{
    for(int i = 0; i < 30; i++) {
        cout << "\x1B[2J\x1B[H";
    }
    Jeu j;
    j.boucleJeuTxt ();
    return 0;
}