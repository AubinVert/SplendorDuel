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
    Jeton(int id):id(id){}
    ~Jeton()=default;
    Jeton& operator=(const Jeton& jet)=delete;
    Jeton(const Jeton& jet)=delete;

    const int get_id()const{return id;}
};

class Jeton_perle:public Jeton{
public:
    Jeton_perle(int id):Jeton(id){
        if((id<1)||(id>25)){
            throw SplendorException("Id de jeton négatif!");
        }
    }

};

class Jeton_or:public Jeton{
public:
    Jeton_or(int id):Jeton(id){
        if((id<1)||(id>25)){
            throw SplendorException("Id de jeton négatif!");
        }
    };
};

class Jeton_gemme:public Jeton{
    Couleur couleur;

public:
    Jeton_gemme(int id, Couleur coul):Jeton(id),couleur(coul){
        if((id<1)||(id>25)){
            throw SplendorException("Id de jeton négatif!");
        }
    }

    const Couleur& get_couleur() const{return couleur;}
    void set_couleur(const Couleur& coul){couleur = coul;}
};

ostream& operator<<(ostream& f, const Jeton_gemme& jet);

ostream& operator<<(std::ostream& f, const Jeton_perle& jet);

ostream& operator<<(ostream& f, const Jeton_or& jet);




#endif //LO21_SPLENDOR_DUEL_JETONS_H
