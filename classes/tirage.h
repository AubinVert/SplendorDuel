#ifndef LO21_SPLENDOR_DUEL_TIRAGE_H
#define LO21_SPLENDOR_DUEL_TIRAGE_H
#include <iostream>
#include <vector>
#include <cstring>
#include "carte.h"
#include "pioche.h"
#include "Exception.h"
using namespace std;

class Tirage{

    static const int nb_max_tirages = 3; // limite de tirage
    static int nb_tirages; // compteur
    Pioche& pioche;
    const int niveau;
    int nb_cartes;
    const int max_cartes;
    vector<const Carte_joaillerie*> cartes;

public:

    //constructeur du tirage
    Tirage(int niv, int max, Pioche& p) : niveau(niv), max_cartes(max), pioche(p){
        if (p.getNiveau() != niveau) {
            throw SplendorException("La pioche n'est pas du même niveau que le tirage !");
        }
        else if (nb_tirages == nb_max_tirages) {
            throw SplendorException("Nombre maximum de tirages dépassé !");
        }

        nb_cartes = 0; // on initialise le nombre de cartes à 0
        nb_tirages++;
    }

    ~Tirage() { nb_tirages--; }

    // définition des getters
    const int getNiveau() const { return niveau; }
    const int getNbCartes() const { return nb_cartes; }
    Pioche& getPioche() const { return pioche; }
    vector<const Carte_joaillerie*>& getTirage() { return cartes; }

    // déclaration de la méthode qui permet de remplir le Tirage avec les cartes (voir tirage.cpp)
    void remplirTirage();

private:
    Tirage& operator=(const Tirage& t)=delete;
    Tirage(const Tirage& t)=delete;

};

// surchage de l'opérateur pour print sur la sortie standard le tirage
inline std::ostream& operator<<(std::ostream& f, Tirage& t) {
    for(const Carte_joaillerie* c : t.getTirage()) {
        f << "\nniveau : " << c->getNiveau() << "\nprestige : " << c->getPrestige() << "\nnb couronnes : " << c->get_nb_couronnes() << "\nnb bonus : " << c->get_nb_bonus() << "\ncapacite : " << c->getCapacite() << "\ncout blanc : " << c->getCoutBlanc() << "\ncout bleu : " << c->getCoutBleu() << "\ncout noir : " << c->getCoutNoir() << "\ncout perle " << c->getCoutPerle() << "\ncout rouge : " << c->getCoutRouge() << "\ncout vert : " << c->getCoutVert() << "\n";
    }
    return f;
}

void testTirage();

#endif //LO21_SPLENDOR_DUEL_TIRAGE_H