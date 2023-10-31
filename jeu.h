#ifndef LO21_SPLENDOR_DUEL_JEU_H
#define LO21_SPLENDOR_DUEL_JEU_H
#include <iostream>

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

class Jeu{
    bool est_termine;
    bool contre_IA;
    Joueur* qui_joue;
    Joueur* adversaire;

    // tableaux contenants tous les objets à la création du jeu
    Sac* sac;
    Plateau* plateau;
    Carte* cartes[67]; // contient toutes les cartes du jeu
    Jeton* jetons[15]; // contient tous les jetons
    Privilege* privileges[3];


};

#endif //LO21_SPLENDOR_DUEL_JEU_H
