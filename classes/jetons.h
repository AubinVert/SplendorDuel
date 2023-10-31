#ifndef LO21_SPLENDOR_DUEL_JETONS_H
#define LO21_SPLENDOR_DUEL_JETONS_H
#include <iostream>
#include "carte.h"

using namespace std;

class Jeton{
    // il faut garantir l'unicité de chaque jeton
    int id;
public:
    const int get_id()const{return id;}
    bool get_dispo()const;
};

class Jeton_perle:public Jeton{

};

class Jeton_or:public Jeton{

};

class Jeton_gemme:public Jeton{
    Couleur couleur;
public:
    const Couleur& get_couleur() const{return couleur;}
    void set_couleur(const Couleur& coul){couleur = coul;}
};




#endif //LO21_SPLENDOR_DUEL_JETONS_H
