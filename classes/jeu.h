#ifndef LO21_SPLENDOR_DUEL_JEU_H
#define LO21_SPLENDOR_DUEL_JEU_H
#include <iostream>
#include "sac.h"
#include "joueur.h"
#include "plateau.h"
#include "privilege.h"
#include "tirage.h"
#include "pioche.h"


using namespace std;


class Jeu {
private:
    bool est_termine;
    bool contre_IA;
    Joueur* qui_joue;
    Joueur* adversaire;

    Plateau* plateau;
    Carte_joaillerie* cartes_joiallerie[67]; // Contient toutes les cartes du jeu
    Jeton* jetons[15]; // Contient tous les jetons
    Carte_royale* cartes_royales[4];
    Privilege* privileges[3];
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
    const Joueur& get_tour() const;
    Tirage* get_tirage_1() const {return tirage_1;}
    Tirage* get_tirage_2() const {return tirage_2;}
    Tirage* get_tirage_3() const {return tirage_3;}
    void tour_suivant();
    static Jeu& getJeu();
    static void libereJeu();
    static void test();


};

#endif //LO21_SPLENDOR_DUEL_JEU_H

