#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H
#include <iostream>

using namespace std;

class Joueur{
    string nom;
    int nb_points;
    int nb_courones;
    int nb_cartes_j;
    int nb_cartes_r;
    int nb_privileges;

    int max_nb_jetons;
    int max_nb_cartes_j;

    Carte_joaillerie** cartes_joaillerie;
    Carte_royale* cartes_royale[3]; // ok pour agrégation?
    Jeton ** jetons;
    Privilege* privileges[3]; // ok pour agrégation?

public:
    const int get_nb_points()const{return nb_points};
    void set_points(int nb){nb_points = nb;};
    const int get_nb_couronnes()const{return nb_courones};
    void set_nb_couronnes(int nb){nb_courones = nb;};
    const int get_nb_privileges()const{return nb_privileges};
    void set_nb_privileges(int nb){nb_privileges = nb;};

    // utilisation du design pattern iterator pour get cartes_j
    // utilisation du design pattern iterator pour get cartes_r
    // utilisation du design pattern iterator pour get jetons
    // utilisation du design pattern iterator pour get privilèges

    void acheter_carte();
    void mettre_jetons_dans_sac();
    void piocher_jetons();
    void obtenir_carte_royale();




};
#endif //LO21_SPLENDOR_DUEL_JOUEUR_H
