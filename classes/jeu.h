#ifndef LO21_SPLENDOR_DUEL_JEU_H
#define LO21_SPLENDOR_DUEL_JEU_H
#include <iostream>
#include "joueur.h"
#include "sac_plateau.h"
#include "privilege.h"

using namespace std;





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
public:
    Joueur& get_tour() const;
    void tour_suivant();

};

#endif //LO21_SPLENDOR_DUEL_JEU_H
