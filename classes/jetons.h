#ifndef LO21_SPLENDOR_DUEL_JETONS_H
#define LO21_SPLENDOR_DUEL_JETONS_H
#include <iostream>
#include "carte.h"

using namespace std;

class Jeton{
    // il faut garantir l'unicité de chaque jeton
    int id;
public:
    Jeton()=delete;
    ~Jeton()=default;
    const int get_id()const{return id;}
    bool get_dispo()const;
};

class Jeton_perle:public Jeton{
public:
    Jeton_perle(int id):id(id){
        if(id<1)||(id>15){
            throw "id non-autorisé";
        }
    };
};

class Jeton_or:public Jeton{
public:
    Jeton_or(int id):id(id){
        if(id<1)||(id>15){
            throw "id non-autorisé";
        }
    };
};

class Jeton_gemme:public Jeton{
    Couleur couleur;

public:
    Jeton_gemme(int id, Couleur coul):id(id),couleur(coul){
        if(id<1)||(id>15){
            throw "id non-autorisé";
        }
    }

    const Couleur& get_couleur() const{return couleur;}
    void set_couleur(const Couleur& coul){couleur = coul;}
};




#endif //LO21_SPLENDOR_DUEL_JETONS_H
