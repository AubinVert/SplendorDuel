#ifndef LO21_SPLENDOR_DUEL_PIOCHE_H
#define LO21_SPLENDOR_DUEL_PIOCHE_H
#include <iostream>
#include <algorithm>
#include <random>
#include "carte.h"

using namespace std;

class Pioche{
protected:
    static const int max_pioches = 3;
    static int nb_pioches;
private:
    const int niveau;
    Pioche& operator=(Pioche& p) = delete;
    vector<const Carte_joaillerie*> pioche;
public:
    ~Pioche(){nb_pioches --;}
    Pioche(int niv) : niveau(niv){
        if (nb_pioches > max_pioches){
            throw SplendorException("Maximum de pioches atteint");
        }
        ++nb_pioches;
    }
    int getNiveau() const {return niveau;}
    bool est_vide(){
        return pioche.empty();
    }
    vector<const Carte_joaillerie*> getPioche() const {return pioche;}
    static int getNbPioches() {return nb_pioches;}
    static void InitPioches(Pioche* p1, Pioche* p2, Pioche* p3, vector<const Carte_joaillerie*>& cartes);
};


#endif //LO21_SPLENDOR_DUEL_MAIN_H