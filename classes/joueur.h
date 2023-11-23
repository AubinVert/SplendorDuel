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

    vector<const Carte_joaillerie*> cartes_joaillerie_achetees;
    vector<const Carte_joaillerie*> cartes_joaiellerie_reservees; // 3 au max
    vector<const Carte_royale*> cartes_royale; // ok pour agrégation?

    vector<const Jeton*> jetons; // tableau de jetons ? or ?

    vector<const Privilege*> privileges; // ok pour agrégation?

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
    void reserver_carte(Tirage *t, const int indice); // pourquoi un pointeur de jetons ? il faut juste que le jeton soit stockée dedans
    void piocher_jeton( int i);
    void obtenir_carte_royale(unsigned int i);
    bool eligible_carte_royale();
    void obtenir_privilege();
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

int positif_ou_nul(int x);

void testJoueurs();

#endif //LO21_SPLENDOR_DUEL_JOUEUR_H

