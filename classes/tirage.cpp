#include "tirage.h"

int Tirage::nb_tirages = 0; // initialisation du compteur à 0


void Tirage::remplirTirage() {




    vector<const Carte_joaillerie*> p = this->pioche.getPioche();
        int max_p = p.size();
        while(this->nb_cartes < this->max_cartes && !this->pioche.est_vide() && this->nb_cartes < max_p){
            const Carte_joaillerie* c = p.front();
            this->cartes.push_back(c);
            this->nb_cartes++;
            p.erase(p.begin());
        }

    if(this->pioche.est_vide()) {
            throw SplendorException("La pioche est vide !");
        }

        else if(this->nb_cartes < this->max_cartes) {
            throw SplendorException("La pioche fournie ne remplit pas complètement la capacité maximum du tirage !");
        }
    }




void testTirage() {

    Pioche p1 = Pioche(1);
    Pioche p2 = Pioche(2);
    Pioche p3 = Pioche(3);

    vector<const Carte_joaillerie*> liste_cartes = initCartesJoaillerie();

    p1.remplirPioche(&p1, &p2, &p3, liste_cartes);
    Tirage t1 = Tirage(1, 31, p1);
    t1.remplirTirage();

    Tirage t2 = Tirage(2, 24, p2);
    t2.remplirTirage();

    Tirage t3 = Tirage(3, 13, p3);
    t3.remplirTirage();

    std::cout<<t1<<endl;



}
