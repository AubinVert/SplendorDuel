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
    // constructeur jetons
    // construceur cartes
    // constructeur privileges
    // constructeur sac
    // constructeur plateau
}

Jeu::Handler Jeu::handler;

Jeu::~Jeu(){
    // destructeur jetons
    // destructeur cartes
    // destructeur privileges
    // destructeur sac
    // destructeur plateau
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