#ifndef LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
#define LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
#include <iostream>
#include "Exception.h"
#include "jetons.h"
#include "joueur.h"

const int ordre[25] = {13,7,8,14,19,18,17,12,7,2,3,4,5,10,15,20,25,25,23,22,21,16,11,6,1};

using namespace std;

class Sac{
    int nb;
    int max;
    Jeton** jetons;
    struct Handler_Sac{
        Sac * instance = nullptr;
        ~Handler_Sac(){
            delete instance;
            instance = nullptr;
        }
    };
    static Handler_Sac handler_sac;
public:
    Sac(int max):nb(0),max(max){
        if (max<0){
            throw SplendorException("Nombre max de jetons dans le sac négatif!");
        }
        jetons = new Jeton*[max];
        for(size_t i = 0; i<max; i++){
            jetons[i] = nullptr;
        }
    }
    ~Sac()=default; // car agrégation !

    Sac& operator=(const Sac& s)=delete;
    Sac(const Sac& s)=delete;


    static Sac& get_sac();
    static void libere_sac();

    //Joueur::IteratorJetons begin_jetons(){return Joueur::IteratorJetons(*jetons,nb);}
    //Joueur::IteratorJetons end_jetons(){return Joueur::IteratorJetons(jetons[nb],0);}
    int get_nb_sac(){return nb;}
    const Jeton* get_jeton_i(int i) const{return jetons[i];}
    void set_sac_i(int i, const Jeton* jet){jetons[i] = jet;}
    void init_sac();

};

class Plateau{
    /*
     * On prend la disposition de plateau suivante, selon l'ordre des jetons dans le tableau:
     *     1   |  2   |   3  |   4  |  5
     *   --------------------------------
     *     5   |  6   |  7   |   8  |  9
     *   --------------------------------
     *     11  |  12  |  13  |  14  |  15
     *   --------------------------------
     *     15  |  16  |  17  |  18  |  19
     *   --------------------------------
     *     21  |  22  |  23  |  24  |  25
     */


    int nb;
    int max; // permet une future évolution de la taille du plateau
    Jeton** jetons;
    struct Handler_Plateau{
        Plateau * instance = nullptr;
        ~Handler_Plateau(){
            delete instance;
            instance = nullptr;
        }
    };
    static Handler_Plateau handler_plateau;
public:
    Plateau(int max):nb(0),max(max){
        if (max<0){
            throw SplendorException("Nombre max de jetons sur le plateau négatif!");
        }
        jetons = new Jeton*[max];
        for(size_t i = 0; i<max; i++){
            jetons[i] = nullptr;
        }
    }
    ~Plateau()=default; // car agrégation !
    Plateau& operator=(const Plateau& p)=delete;
    Plateau(const Plateau& p)=delete;

    static Plateau& get_plateau();
    static void libere_plateau();


    const Jeton* get_plateau_i(int i) const{return jetons[i];}
    void set_plateau_i(int i, const Jeton* jet){jetons[i] = jet;}
    const Jeton* get_droite_i(int i) const{
        if(i%5 != 0){
            return jetons[++i];
        }else{
            return nullptr;
        }
    }
    const Jeton* get_gauche_i(int i) const{
        if(i%5 != 1){
            return jetons[--i];
        }else{
            return nullptr;
        }
    }
    const Jeton* get_dessus_i(int i) const{
        if(i>5){
            return jetons[i-5];
        }else{
            return nullptr;
        }
    }
    const Jeton* get_dessous_i(int i) const{
        if(i<21){
            return jetons[i+5];
        }else{
            return nullptr;
        }
    }



    void remplir_plateau(Sac& sac);
    void print_tab() const;

};


#endif //LO21_SPLENDOR_DUEL_SAC_PLATEAU_H
