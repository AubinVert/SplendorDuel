#include "pioche.h"

int Pioche::nb_pioches = 0;

void Pioche::remplirPioche(Pioche* p1, Pioche* p2, Pioche* p3, vector<const Carte_joaillerie*>& cartes){
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



