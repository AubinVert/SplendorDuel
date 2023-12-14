#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H

#include "Exception.h"
#include <string>
#include <iostream>
#include <vector>
#include "carte.h"
#include "jetons.h"
#include "privilege.h"
#include "sac.h"
#include "plateau.h"
#include "tirage.h"
#include "jeu.h"


// tâches à réaliser : constructeur destructeur Joueur (jeu?)
// tester toutes les méthodes ?
// vérifier UML si toutes les méthodes sont implémentées.


using namespace std;

class Strategy_player{ // Utilisation Design Pattern Strategy
protected:
    std::string nom;
    //int is_ia = 0;
    int nb_points;
    int nb_courones;
    int nb_cartes_j;
    int nb_cartes_j_reservees;
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

    vector<const Jeton*> jetons;// tableau de jetons ? or ?

    vector<const Privilege*> privileges;

    Strategy_player& operator=(const Strategy_player&) = delete;
    Strategy_player(const Strategy_player&) = delete;
public:
    //constructeur destructeur
    Strategy_player(const string &nom);
    virtual ~Strategy_player();

    //méthodes virtuelles pures
    virtual void choice()=0;
    virtual void utilisationPrivilege() = 0;
    virtual void selection_jetons()=0;
    virtual void achat_carte()=0;
    virtual void buyCard(Tirage *t, const int indice) = 0;
    virtual void buyCardFromReserve( const int indice) = 0;
    virtual void applicationCapacite(const JewelryCard& carte, Strategy_player& adversaire) = 0;
    virtual void reservation_carte()=0;
    virtual void selectionRoyalCard() = 0;

    //getters setters
    const int getNbCartesJoaillerie() const {return nb_cartes_j;}
    const int getNbJetons() const {return nb_jetons;}
    const string getName() const {return nom;}
    void setName(string& s) {nom = s;}
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
    void increment_carte_royale() {nb_cartes_r = nb_cartes_r + 1;}
    vector<const Jeton*>& getJeton() {return jetons;}


    //méthode utilitaires aux classes filles

    int calculateBonus(enum colorBonus bonus);
    int nbJeton(const Color& couleur) const;
    void withdrawJetons(const Color& c, int val);
    void reserver_carte(Tirage *t, const int indice);
    void reserver_carte(Pioche *p);
    void piocher_jeton( int i);
    void obtainRoyaleCard(unsigned int i);
    bool royaleCardEligibility();
    void obtainPrivilege();
    void retirerPrivilege();
    void remplissagePlateau();

    // méthode utilitaire pour le main
    void print_player();
    int getOptionalChoices();
    void retirerJetonBlanc();
    void retirerJetonPerle();
};


class Joueur : public Strategy_player {

public:
    // Constructeur et destructeur
    Joueur(const string &nom);
    ~Joueur();

    // Méthodes polymorphiques adaptées pour un joueur
    void choice();
    void utilisationPrivilege();
    void selection_jetons();
    void applicationCapacite(const JewelryCard& carte, Strategy_player& adversaire);
    void applicationCapacite(const int indice, const Joueur& adversaire);
    void achat_carte();
    void buyCard(Tirage *t, const int indice);
    void buyCardFromReserve( const int indice);
    void reservation_carte();
    void selectionRoyalCard();

};


class IA: public Strategy_player {
public:
    IA(const string & nom = "IA");
    ~IA();

    // Méthodes polymorphiques adaptées pour une IA
    void choice();
    void utilisationPrivilege();
    void selection_jetons();
    void achat_carte();
    void buyCard(Tirage *t, const int indice);
    void buyCardFromReserve( const int indice);
    void reservation_carte();
    void selectionRoyalCard();
    void applicationCapacite(const JewelryCard& carte, Strategy_player& adversaire);


};



/**************** Fonctions utilitaires ****************/
inline std::ostream& operator<<(std::ostream& os, const Strategy_player& j){
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

