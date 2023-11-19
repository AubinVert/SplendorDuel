#ifndef LO21_SPLENDOR_DUEL_PIOCHE_TIRAGE_H
#define LO21_SPLENDOR_DUEL_PIOCHE_TIRAGE_H
#include "pioche.h"

using namespace std;

class Tirage{
    static const int nb_max_tirages = 3;
    static int nb_tirages;
    Pioche* pioche;
    const int niveau;
    int nb_cartes;
    const int max_cartes;
    vector<const Carte_joaillerie*> tirage;
public:
    Tirage(int niv, int max, Pioche* p) : niveau(niv), max_cartes(max){
        if (p->getNiveau() != niv) {
            throw SplendorException("La pioche n'est pas du même niveau que le tirage !");
        }
        else if (nb_tirages > nb_max_tirages) {
            throw SplendorException("Nombre maximum de tirages dépassé !");
        }
        nb_cartes = 0;
        pioche = p;
        ++nb_tirages;
    }
    ~Tirage();
    Tirage& operator=(const Tirage& t)=delete;
    Tirage(const Tirage& t)=delete;

    Pioche* getPioche() { return pioche; }

    int GetNiv_tirage() const {return niveau;}

    vector<const Carte_joaillerie*> getTirage() const { return tirage; }

    void remplirTirage();

};


/*inline std::ostream& operator<<(std::ostream& f, Tirage& t) {
    for(int i = 0; i < t.nb ; i++) {
        f<<t.getTirage()[i] ;
    }
    return f;
}*/

void testTirage()

#endif //LO21_SPLENDOR_DUEL_PIOCHE_TIRAGE_H