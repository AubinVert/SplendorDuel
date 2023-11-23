#include "jeu.h"

void Jeu::tour_suivant() {
    Joueur* temp = qui_joue;
    qui_joue = adversaire;
    adversaire = qui_joue;
}

const Joueur& Jeu::get_tour() const {
    return *qui_joue;
}

Jeu::Jeu() {

    // constructeur jetons (avec le sac)
    Sac::get_sac();
    Plateau::get_plateau();
    // construceur cartes
    cartes_joiallerie = initCartesJoaillerie();
    cartes_royales = initCartesRoyales();

    // constructeur privileges
    privileges = initPrivileges();

    // pioches :
    p1 = new Pioche(1);
    p2 = new Pioche(2);
    p3 = new Pioche(3);
    p1->InitPioches(p1, p2, p3, cartes_joiallerie);

    //std::cout<<p1->getPioche().size()<<endl;

    // tirages ?

    tirage_1 = new Tirage(1, 5, *p1);
    tirage_2 = new Tirage(2, 4, *p2);
    tirage_3 = new Tirage(3, 3, *p3);
    tirage_1->remplirTirage();
    tirage_2->remplirTirage();
    tirage_3->remplirTirage();


}

Jeu::Handler Jeu::handler;

Jeu::~Jeu(){
    Sac::libere_sac(); // détruit aussi jetons ?


    for (int i = 0; i < cartes_royales.size(); ++i) {
        delete cartes_royales[i];
    }
    for (int i = 0; i < cartes_joiallerie.size(); ++i) {
        delete cartes_joiallerie[i];
    }

    // libère les tirages :

    delete tirage_1;
    delete tirage_2;
    delete tirage_3;

    // reste à détruire privilèges, plateau ?

};

Jeu& Jeu::getJeu(){
    if (handler.instance == nullptr)  handler.instance = new Jeu;
    return *handler.instance;
}

void Jeu::libereJeu(){
    delete handler.instance;
    handler.instance = nullptr;
}

void Jeu::test() {
    if (handler.instance == nullptr) std::cout << "Test";
}