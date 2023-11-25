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
    unsigned int manche = 0;
    Joueur* adversaire;
    // Plateau* plateau; // Plateau singleton ?
    vector<const JewelryCard*>  cartes_joiallerie; // Contient toutes les cartes du jeu
    vector<const Jeton*> jetons; // Contient tous les jetons
    vector<const RoyalCard*>  cartes_royales;
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
    // Initialiser les noms des joueurs
    void setPlayers(const string& celui_qui_joue, const string& qui_est_adversaire);

    const int choice();

    void remplirPlateau(){
        Plateau::get_plateau().remplir_plateau(Sac::get_sac());
    }

    Joueur& getCurrentPlayer() const {return *qui_joue;}
    Joueur& getOpponent() const {return *adversaire;}


     vector<const RoyalCard*> getCartesRoyales () const {
        return cartes_royales;
    }

    vector<const JewelryCard*> getCartesJoaillerie () const {
        return cartes_joiallerie;
    }

    const RoyalCard& pullCarteRoyale (unsigned int i) {
         if(i>cartes_royales.size() || i< 0) throw SplendorException("Indice non valide ! ");
         const RoyalCard* tmp = cartes_royales[i];
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

    void setPrivilege(const Privilege& p){
         if(privileges.size()==3){
             throw SplendorException("Nombre de privilège max dans le jeu déjà atteint");
         }
         privileges.push_back(&p);
     }

     const bool isFinished();

     Joueur& get_tour() ;
     Tirage* get_tirage_1()  {return tirage_1;}
     Tirage* get_tirage_2()  {return tirage_2;}
     Tirage* get_tirage_3()  {return tirage_3;}
    void tour_suivant();
    static Jeu& getJeu();
    static void libereJeu();
    static void test();
    const Jeton* getJeton(int i) { return jetons[i];}
    void setJoueurNames(const string& s1, const string& s2);

};

#endif //LO21_SPLENDOR_DUEL_JEU_H

