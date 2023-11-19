#include "tirage.h"

int Tirage::nb_tirages = 0;

void Tirage::remplirTirage() {
    vector<const Carte_joaillerie*> p = pioche.getPioche();
    while(nb_cartes < max_cartes && !pioche.est_vide()) {
        const Carte_joaillerie* c = p.front();
        cartes.push_back(c);
        nb_cartes++;
        p.erase(p.begin());
    }
    if(pioche.est_vide()) {
        throw SplendorException("La pioche est vide !");
    }
    else if(nb_cartes > max_cartes) {
        throw SplendorException("Trop de cartes dans le tirage !");
    }
}

void testTirage() {
    Pioche p1 = Pioche(1);
    Pioche p2 = Pioche(2);
    Pioche p3 = Pioche(3);
    vector<const Carte_joaillerie*> liste_cartes = initCartesJoaillerie();
    p1.remplirPioche(&p1, &p2, &p3, liste_cartes);
    Tirage t1 = Tirage(1, 5, p1);
    t1.remplirTirage();
    std::cout<<t1<<endl;
}
