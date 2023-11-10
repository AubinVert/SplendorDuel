#ifndef LO21_SPLENDOR_DUEL_PIOCHE_H
#define LO21_SPLENDOR_DUEL_PIOCHE_H
#include <iostream>
#include "carte.h"
using namespace std;

class Pioche{
    int niveau;
    int nb;
    int max;
    Carte_joaillerie ** cartes; // vérifier si on peut pas mettre déjà une taille
public:
    bool est_vide(){return nb==0;}
};
