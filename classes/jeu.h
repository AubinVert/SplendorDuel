#ifndef LO21_SPLENDOR_DUEL_JEU_H
#define LO21_SPLENDOR_DUEL_JEU_H
#include <iostream>
#include "sac.h"
#include "joueur.h"
#include "plateau.h"
#include "privilege.h"
#include "tirage.h"
#include "pioche.h"
#include "jetons.h"


class Jeu {
private:

    bool est_termine = false;
    bool contre_IA = false;
    Joueur* qui_joue;
    Joueur* adversaire;
    Plateau* plateau;
    vector<const Carte_joaillerie*>  cartes_joiallerie; // Contient toutes les cartes du jeu
    vector<const Jeton*> jetons; // Contient tous les jetons
    vector<const Carte_royale*>  cartes_royales;
    vector<const Privilege*> privileges;
    Pioche* p1;
    Pioche* p2;
    Pioche* p3;

    Tirage* tirage_1;
    Tirage* tirage_2;
    Tirage* tirage_3;


    struct Handler {
        Jeu *instance = nullptr;
        ~Handler() {
            delete instance;
            instance = nullptr;
        }
    };

    static Handler handler;
    Jeu();
    ~Jeu();

    Jeu (const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;

public:

     vector<const Carte_royale*> getCartesRoyales () const {
        return cartes_royales;
    }

    vector<const Carte_joaillerie*> getCartesJoaillerie () const {
        return cartes_joiallerie;
    }

    const Carte_royale& pullCarteRoyale (unsigned int i) {
         if(i>cartes_royales.size() || i< 0) throw SplendorException("Indice non valide ! ");
         const Carte_royale* tmp = cartes_royales[i];
         cartes_royales.erase(cartes_royales.begin()+i);
        return *tmp;
     }

     const unsigned int getNbPrivilege() const {
         return privileges.size();
     }

    const Privilege& getPrivilege() {
        if(privileges.size() <= 0){
            throw SplendorException("Plus de privilège disponible");
        }
        const Privilege* tmp = privileges[0];
        privileges.erase(privileges.begin());
        return *tmp;
    }

    const Joueur& get_tour() const;
    const Tirage* get_tirage_1()  {return tirage_1;}
    const Tirage* get_tirage_2()  {return tirage_2;}
    const Tirage* get_tirage_3()  {return tirage_3;}
    void tour_suivant();
    static Jeu& getJeu();
    static void libereJeu();
    static void test();

};

#endif //LO21_SPLENDOR_DUEL_JEU_H

