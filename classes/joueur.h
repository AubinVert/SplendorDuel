#ifndef LO21_SPLENDOR_DUEL_JOUEUR_H
#define LO21_SPLENDOR_DUEL_JOUEUR_H
#include <iostream>
#include "carte.h"
#include "jetons.h"
#include "privilege.h"

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
    Carte_royale* cartes_royale[4]; // ok pour agrégation?
    Jeton ** jetons;
    Privilege* privileges[3]; // ok pour agrégation?

public:
    const int get_nb_points()const{return nb_points;};
    void set_points(int nb){nb_points = nb;};
    const int get_nb_couronnes()const{return nb_courones;};
    void set_nb_couronnes(int nb){nb_courones = nb;};
    const int get_nb_privileges()const{return nb_privileges;};
    void set_nb_privileges(int nb){nb_privileges = nb;};


    // utilisation du design pattern iterator pour get cartes_j

    class IteratorJ {
        Carte_joaillerie* start;
        Carte_joaillerie* end;
        size_t nb;
        IteratorJ(Carte_joaillerie* start, size_t nb) : start(start), nb(nb){}
        friend class Joueur;
    public:
        void operator++(){if(nb==0) throw "Le nombre de cartes doit être strictement supérieur à 0";start++;nb--;}
        Carte_joaillerie& operator*(){if(nb==0) throw "Attention, le nombre de cartes est égal à 0"; return *start;}
        bool operator!=(IteratorJ i){return start!=i.start;}
    };

    IteratorJ beginJ(){return IteratorJ(cartes_joaillerie[0],nb_cartes_r);}
    IteratorJ endJ(){return IteratorJ(cartes_joaillerie[nb_cartes_r],0);}



    // utilisation du design pattern iterator pour get cartes_r

    // pas besoin d'iterator car pas tableau de pointeurs ?


    // utilisation du design pattern iterator pour get jetons

    class IteratorJetons {
        Jeton* start;
        Jeton* end;
        size_t nb;
        IteratorJetons(Jeton* start, size_t nb) : start(start), nb(nb){}
        friend class Joueur;
    public:
        void operator++(){if(nb==0) throw "Le nombre de cartes doit être strictement supérieur à 0";start++;nb--;}
        Jeton& operator*(){if(nb==0) throw "Attention, le nombre de cartes est égal à 0"; return *start;}
        bool operator!=(IteratorJetons i){return start!=i.start;}
    };

    IteratorJetons beginJetons(){return IteratorJetons(jetons[0],nb_cartes_r);}
    IteratorJetons endJetons(){return IteratorJetons(jetons[nb_cartes_r],0);}

    // utilisation du design pattern iterator pour get privilèges
    // ??



    void acheter_carte();
    void reserver_carte();
    void remplir_plateau();
    void mettre_jetons_dans_sac();
    void piocher_jetons();
    void obtenir_carte_royale();




};
#endif //LO21_SPLENDOR_DUEL_JOUEUR_H
