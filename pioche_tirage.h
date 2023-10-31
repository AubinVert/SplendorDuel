#ifndef LO21_SPLENDOR_DUEL_PIOCHE_TIRAGE_H
#define LO21_SPLENDOR_DUEL_PIOCHE_TIRAGE_H
#include <iostream>

using namespace std;

class Pioche{
    int niveau;
    int nb;
    int max;
    Carte_joaillerie ** cartes; // vérifier si on peut pas mettre déjà une taille
};

class Tirage{
    Pioche* pioche; // ajout de la pioche pour la méthode piocher?
    int niveau;
    int nb;
    int max;
    Carte_joaillerie ** cartes;
    Pioche * pioche;
};

#endif //LO21_SPLENDOR_DUEL_PIOCHE_TIRAGE_H
