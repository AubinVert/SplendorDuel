#ifndef LO21_SPLENDOR_DUEL_JETONS_H
#define LO21_SPLENDOR_DUEL_JETONS_H
#include <iostream>
#include "Exception.h"
#include "carte.h"

using namespace std;

class Jeton{
    // il faut garantir l'unicité de chaque jeton
    int id;

public:
    Jeton(int id)=default;
    ~Jeton()=default;
    operator=(const Jeton& jet){}=delete;
    Jeton(const Jeton& jet){}=delete;

    const int get_id()const{return id;}
};

class Jeton_perle:public Jeton{
public:
    Jeton_perle(int id):Jeton(id){
        if(id<1)||(id>25){
            throw SplendorException("Id de jeton négatif!");
        }
    }
    operator=(const Jeton_perle& jet){}=delete;
    Jeton_perle(const Jeton_perle& jet){}=delete;
};

class Jeton_or:public Jeton{
public:
    Jeton_or(int id):Jeton(id){
        if(id<1)||(id>25){
            throw SplendorException("Id de jeton négatif!");
        }
    };
    operator=(const Jeton_or& jet){}=delete;
    Jeton_or(const Jeton_or& jet){}=delete;
};

class Jeton_gemme:public Jeton{
    Couleur couleur;

public:
    Jeton_gemme(int id, Couleur coul):Jeton(id),couleur(coul){
        if(id<1)||(id>25){
            throw SplendorException("Id de jeton négatif!");
        }
    }
    operator=(const Jeton_gemme& jet){}=delete;
    Jeton_gemme(const Jeton_gemme& jet){}=delete;

    const Couleur& get_couleur() const{return couleur;}
    void set_couleur(const Couleur& coul){couleur = coul;}
};




#endif //LO21_SPLENDOR_DUEL_JETONS_H
