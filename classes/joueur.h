#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H
#include <iostream>
#include <vector>
#include "carte.h"
#include "jetons.h"
#include "privilege.h"
#include "sac.h"
#include "plateau.h"
#include "tirage.h"


// tâches à réaliser : constructeur destructeur Joueur (jeu?)
// tester toutes les méthodes ?
// vérifier UML si toutes les méthodes sont implémentées.


using namespace std;

class Joueur {
    string nom;
    int is_ia = 0;
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

    vector<const JewelryCard*> cartes_joaillerie_achetees;
    vector<const JewelryCard*> cartes_joaiellerie_reservees; // 3 au max
    vector<const RoyalCard*> cartes_royale; // ok pour agrégation?

    vector<const Jeton*> jetons; // tableau de jetons ? or ?

    vector<const Privilege*> privileges;

    Joueur& operator=(const Joueur&) = delete;
    Joueur(const Joueur&) = delete;

public:

    void setIa(){
        is_ia = 1;
    }
    const int getIa() const {
        return is_ia;
    }
    // Getter et setter

    const int getNbCartesJoaillerie() const {
        return nb_cartes_j;
    }

    const int getNbJetons() const {
        return nb_jetons;
    }

    const string getName() const { return nom;}
    const int getNbCartesAchetees() const { return cartes_joaillerie_achetees.size();}
    const int getNbCartesReservees()const {return cartes_joaiellerie_reservees.size();}

    const int getNbPoints()const{return nb_points;}
    void setPoints(int nb){nb_points = nb;}
    const int getNbCouronnes()const{return nb_courones;}
    void setNbCouronnes(int nb){nb_courones = nb;}
    const int getNbPrivileges()const{return nb_privileges;}
    void setNbPrivileges(int nb){nb_privileges = nb;}
    const int getNbCartesRoyales() const {return nb_cartes_r;}
    vector<const JewelryCard*> getCartesReserved(){return cartes_joaiellerie_reservees;}
    void increment_carte_royale() {nb_cartes_r = nb_cartes_r + 1;} // suce mon zob ?

    void buyCardFromReserve( const int indice);


    int nbJeton(const Color& couleur) const; // const ?
    void withdrawJetons(const Color& c, int val); // const ?

    // Constructeur et destructeur
    Joueur(const string &nom);

    ~Joueur();


    // utilisation du design pattern iterator pour get privilèges
    // ??

    int calculateBonus(enum colorBonus bonus);
    void buyCard(Tirage *t, const int indice);
    void reserver_carte(Tirage *t, const int indice); // pourquoi un pointeur de jetons ? il faut juste que le jeton soit stockée dedans
    void piocher_jeton( int i);
    void obtainRoyaleCard(unsigned int i);
    bool royaleCardEligibility();
    void obtainPrivilege();
    void retirerPrivilege();




};


inline std::ostream& operator<<(std::ostream& os, const Joueur& j){
    os<<"Pseudo : "<<j.getName();
    if(j.getNbPoints()!=0){
        os<<"nombre de points : "<<j.getNbPoints();
    }
    if(j.getNbCouronnes() != 0){
        os<<" nombre de couronnes : "<<j.getNbCouronnes();
    }
    if(j.getNbCartesReservees()!=0){
        os<<" nombre de cartes réservées : "<<j.getNbCartesReservees();

    }
    if(j.getNbPrivileges() != 0){
        os << " nombre de privilège : "<<j.getNbPrivileges();
    }
    if( j.getNbJetons()!=0){
        os << " nombre de jetons : "<< j.getNbJetons();

    }
    os<<endl;
    return os;
}

int positiveOrNull(int x);

void testJoueurs();

#endif //LO21_SPLENDOR_DUEL_JOUEUR_H

