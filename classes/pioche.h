#define LO21_SPLENDOR_DUEL_PIOCHE_H
#include <iostream>
#include "carte.h"
using namespace std;

class Pioche{
private:
    static const int max_pioches = 3;
    static int nb_pioches;
    const int niveau;
    Pioche& operator=(Pioche& p) = delete;
    vector<const Carte_joaillerie*> pioche;


public:
    bool est_vide(){
        return pioche.empty();
    }

    static int getNbPioches(){return nb_pioches;}

    ~Pioche(){nb_pioches --;}

    explicit Pioche(int niv) : niveau(niv){
        if (nb_pioches > max_pioches){
            throw SplendorException("Maximum de pioches atteint");
        }
        nb_pioches++;
    }

    static void remplirPioche(Pioche* p1, Pioche* p2, Pioche* p3, vector<Carte_joaillerie*>& cartes){
        if (nb_pioches != max_pioches){throw SplendorException("les pioches ne sont pas toutes créées");}

        for (const Carte_joaillerie* carte : cartes) { //pour chaque carte (ptr constant vers une carte) du vecteur cartes
            switch(carte->getNiveau()){
                case 1:
                    (p1->pioche).push_back(carte);
                    break;
                case 2:
                    (p2->pioche).push_back(carte);
                    break;
                case 3:
                    (p3->pioche).push_back(carte);
                    break;
            }
        }
    }

};
