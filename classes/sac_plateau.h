#ifndef LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
#define LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
#include <iostream>
#include "jetons.h"



using namespace std;

class Sac{
    int nb;
    int max;
    Jeton** jetons;
public:
    Sac(int max):nb(0),max(max){
        jetons = new Jeton*[max];
        for(size_t i = 0; i<max; i++){
            jetons[i] = nullptr;
        }
    }
    ~Sac()=default; // car agrégation !
    operator=(const Sac& s)=delete;
    Sac(const Sac& s)=delete;
};

class Plateau{
    int nb;
    int max; // permet une future évolution de la taille du plateau
    Jeton ** jetons; // vérifier
public:
    Plateau(int max):nb(0),max(max){
        jetons = new Jeton*[max];
        for(size_t i = 0; i<max; i++){
            jetons[i] = nullptr;
        }
    }
    ~Plateau()=default; // car agrégation !
    operator=(const Plateau& p)=delete;
    Plateau(const Plateau& p)=delete;

};


#endif //LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
