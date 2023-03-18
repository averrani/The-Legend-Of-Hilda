//The Legend of Hilda - C++ / SFML 2
//Copyright / Droits d'auteur : ISSAD Aris / VAN GINNEKEN Salomon / DEGRANGE Jonathan

#include "input.h"

using namespace std;
using namespace sf;

//Constructeur
Input::Input()
{
    button.left = button.right = button.up = button.down = button.run =
        button.attack = button.enter = false;
}

//Accesseur
Input::Button Input::getButton(void) const { return button; }

//Mutateur
void Input::setButton(int bouton, bool etat)
{
    switch (bouton)
    {
    case up:
        button.up = etat;
        break;

    case down:
        button.down = etat;
        break;

    case right:
        button.right = etat;
        break;

    case left:
        button.left = etat;
        break;

    case attack:
        button.attack = etat;
        break;

    case run:
        button.run = etat;
        break;

    case enter:
        button.enter = etat;
        break;
    }
}

//Fonctions
void Input::getInput(RenderWindow &window)
{

    // Tant qu'il y a des évènements à traiter
    while (window.pollEvent(event))
    {
        // on regarde le type de l'évènement...
        switch (event.type)
        {
        // On ferme la fenêtre
        case Event::Closed:
            window.close();
            break;

        // Touche pressée
        case Event::KeyPressed:
            switch (event.key.code) // La touche qui a été pressée
            {
            case Keyboard::Escape: // Echap
                window.close();
                break;

            case Keyboard::LShift:
                button.run = true;
                break;

            case Keyboard::RShift:
                button.attack = true;
                break;

            case Keyboard::Q:
                button.left = true;
                break;

            case Keyboard::D:
                button.right = true;
                break;

            case Keyboard::S:
                button.down = true;
                break;

            case Keyboard::Z:
                button.up = true;
                break;

            case Keyboard::Return:
                button.enter = true;
                break;

            default:
                break;
            }
            break;

        // Touche relâchée
        case Event::KeyReleased:
            switch (event.key.code)
            {
            case Keyboard::LShift:
                button.run = false;
                break;

            case Keyboard::RShift:
                button.attack = false;
                break;

            case Keyboard::V:
                button.attack = false;
                break;

            case Keyboard::Q:
                button.left = false;
                break;

            case Keyboard::D:
                button.right = false;
                break;

            case Keyboard::S:
                button.down = false;
                break;

            case Keyboard::Z:
                button.up = false;
                break;

            case Keyboard::Return:
                button.enter = false;
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}