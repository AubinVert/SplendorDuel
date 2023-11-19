#include "tirage.h"

int Tirage::nb_tirages = 0;

void Tirage::remplirTirage() {
    if (nb_tirages != nb_max_tirages) {throw SplendorException("les tirages ne sont pas toutes créés");}
    if (niveau != pioche->getNiveau()) {throw SplendorException("le tirage et la pioche ne sont pas de même niveau");}
    while ((nb_cartes < max_cartes) && !((pioche->getPioche()).empty())) {
        tirage.push_back((pioche->getPioche())[0]);
        (pioche->getPioche()).erase((pioche->getPioche()).begin());
        nb_cartes++;
    }
}

/*
void testTirage() {
    Pioche *p1 = new Pioche(1);
    Tirage *t1 = new Tirage(1, 5, p1);
    t1->remplirTirage();
    std::cout<<*t1<<endl;
}*/

