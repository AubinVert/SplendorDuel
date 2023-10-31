#ifndef LO21_SPLENDOR_DUEL_JETONS_H
#define LO21_SPLENDOR_DUEL_JETONS_H
#include <iostream>

using namespace std;

class Jeton{
    int id;
};

class Jeton_perle:public Jeton{

};

class Jeton_or:public Jeton{

};

class Jeton_gemme:public Jeton{
    Couleur couleur;
};


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

#endif //LO21_SPLENDOR_DUEL_JETONS_H
