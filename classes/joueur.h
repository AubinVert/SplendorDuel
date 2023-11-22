#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H
#include <iostream>
#include <vector>
#include "carte.h"
#include "jetons.h"
#include "privilege.h"
#include "sac.h"
#include "plateau.h"

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

    vector<const Carte_joaillerie*> cartes_joaillerie_achetees;
    vector<const Carte_joaillerie*> cartes_joaiellerie_reservees; // 3 au max
    vector<const Carte_royale*> cartes_royale; // ok pour agrégation?
    vector<const Jeton*> jetons;
    vector<const Privilege*> privileges; // ok pour agrégation?

    Joueur& operator=(const Joueur&) = delete;
    Joueur(const Joueur&) = delete;

public:

    // Getter et setter

    const int get_nb_points()const{return nb_points;};
    void set_points(int nb){nb_points = nb;};
    const int get_nb_couronnes()const{return nb_courones;};
    void set_nb_couronnes(int nb){nb_courones = nb;};
    const int get_nb_privileges()const{return nb_privileges;};
    void set_nb_privileges(int nb){nb_privileges = nb;};
    const int get_nb_r() const {return nb_cartes_r;};
    void increment_carte_royale() {nb_cartes_r = nb_cartes_r + 1;};

    int nb_jeton(const Couleur& c) const; // const ?
    void retirer_jeton(const Couleur& c, int val); // const ?

    // Constructeur et destructeur
    Joueur(string &nom);
    ~Joueur();


    // utilisation du design pattern iterator pour get privilèges
    // ??

    int calculer_bonus(enum Bonus_couleur bonus);
    void acheter_carte(const Carte_joaillerie& carte);
    void reserver_carte(const Carte_joaillerie& carte, const Jeton* jet);
    void piocher_jeton(const Jeton& jeton);
    void obtenir_carte_royale(const Carte_royale& carte);
    bool eligible_carte_royale();

};

int positif_ou_nul(int x);

#endif //LO21_SPLENDOR_DUEL_JOUEUR_H

