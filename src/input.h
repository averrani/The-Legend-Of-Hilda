//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

class Input
{
    //Structures
    struct Button
    {
        bool left, right, up, down, attack, run, enter;
    };

public:
    //Constructeur
    Input();

    //Accesseur
    Button getButton(void) const;

    //Mutateur
    void setButton(int bouton, bool etat);

    //Fonctions
    void getInput(sf::RenderWindow &window);

private:

    sf::Event event;
    Button button;

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
};
#endif