#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H
#include <iostream>

using namespace std;

class Joueur{
    string nom;
    int nb_points;
    int nb_courones;
    int nb_cartes_j;
    int nb_cartes_r;
    int nb_privileges;

    int max_nb_jetons;
    int max_nb_cartes_j;

    Carte_joaillerie** cartes_joaillerie;
    Carte_royale* cartes_royale[3]; // ok pour agrégation?
    Jeton ** jetons;
    Privilege* privileges[3]; // ok pour agrégation?


};
#endif //LO21_SPLENDOR_DUEL_JOUEUR_H
