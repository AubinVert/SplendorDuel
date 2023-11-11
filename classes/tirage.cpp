#include "tirage.h"

int Tirage::nb_tirages = 0;

void Tirage::remplirTirage() {
    while(nb_cartes < max_cartes && !pioche->est_vide()) {
            pioche-> [0].push_pack();
    }
}

void testTirage() {
    Pioche *p1 = new Pioche(1);
    Tirage *t1 = new Tirage(1, 5, p1);
    t1->remplirTirage();
    std::cout<<*t1<<endl;
}
