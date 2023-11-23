#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H
#include <iostream>
#include <vector>
#include "carte.h"
#include "jetons.h"
#include "privilege.h"
#include "sac.h"
#include "plateau.h"


// tâches à réaliser : constructeur destructeur Joueur (jeu?)
// tester toutes les méthodes ?
// vérifier UML si toutes les méthodes sont implémentées.


using namespace std;

class Joueur {
    string nom;

    int nb_points;
    int nb_courones;
    int nb_cartes_j;
    int nb_cartes_r;
    int nb_privileges;
    int nb_jetons;
    static int const max_nb_jetons = 10;
    static int const max_nb_cartes_r = 2;
    static int const max_nb_privileges = 3;
    static int const max_nb_cartes_reservees = 3;

    vector<const Carte_joaillerie*> cartes_joaillerie_achetees;
    vector<const Carte_joaillerie*> cartes_joaiellerie_reservees; // 3 au max
    vector<const Carte_royale*> cartes_royale; // ok pour agrégation?

    vector<const Jeton*> jetons; // tableau de jetons ? or ?

    vector<const Privilege*> privileges; // ok pour agrégation?

    Joueur& operator=(const Joueur&) = delete;
    Joueur(const Joueur&) = delete;

public:

    // Getter et setter

    const int getNbCartesJoaillerie() const {
        return nb_cartes_j;
    }

    const int getNbJetons() const {
        return nb_jetons;
    }



    const int getNbPoints()const{return nb_points;}
    void setPoints(int nb){nb_points = nb;}
    const int getNbCouronnes()const{return nb_courones;}
    void setNbCouronnes(int nb){nb_courones = nb;}
    const int getNbPrivileges()const{return nb_privileges;}
    void setNbPrivileges(int nb){nb_privileges = nb;}
    const int getNbCartesRoyales() const {return nb_cartes_r;}

    void increment_carte_royale() {nb_cartes_r = nb_cartes_r + 1;} // suce mon zob ?

    int nb_jeton(const Couleur& c) const; // const ?
    void retirer_jeton(const Couleur& c, int val); // const ?

    // Constructeur et destructeur
    Joueur(const string &nom);

    ~Joueur();


    // utilisation du design pattern iterator pour get privilèges
    // ??

    int calculer_bonus(enum Bonus_couleur bonus);
    void acheter_carte(const Carte_joaillerie& carte);
    void reserver_carte(const Carte_joaillerie& carte, const Jeton* jet);
    void piocher_jeton( int i);
    void obtenir_carte_royale(unsigned int i);
    bool eligible_carte_royale();
    void obtenir_privilege();

};


inline std::ostream& operator<<(std::ostream& os, const Joueur& j){
    os<<"nombre de points : "<<j.getNbPoints() <<" nombre de couronnes : "<<j.getNbCouronnes();
    os<<" nombre cartes joaillerie : "<< j.getNbCartesJoaillerie()<<" nombre de cartes royales : "<<j.getNbCartesRoyales();
    os << " nombre de privilège : "<<j.getNbPrivileges()<<" nombre de jetons : "<< j.getNbJetons()<<endl;
    return os;
}

int positif_ou_nul(int x);

void testJoueurs();

#endif //LO21_SPLENDOR_DUEL_JOUEUR_H

