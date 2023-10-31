#ifndef LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
#define LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
#include <iostream>
#include "jetons.h"



using namespace std;

class Sac{
    int nb;
    int max;
    Jeton** jetons;//vérifier
};

class Plateau{
    int nb;
    int max;
    Jeton * jetons[][]; // vérifier
};
#endif //LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
