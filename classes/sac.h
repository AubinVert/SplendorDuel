#ifndef LO21_SPLENDOR_DUEL_SAC_H
#define LO21_SPLENDOR_DUEL_SAC_H
#include <iostream>
#include <vector>
#include "jetons.h"

using namespace std;


class Sac{
    int nb;
    vector<const Jeton*> jetons;
    struct Handler_Sac{
        Sac * instance = nullptr;
        ~Handler_Sac(){
            delete instance;
            instance = nullptr;
        }
    };
    static Handler_Sac handler_sac;
    Sac()=default;
    ~Sac()=default; // car agrégation !

    Sac& operator=(const Sac& s)=delete;
    Sac(const Sac& s)=delete;
public:


    static Sac& get_sac();
    static void libere_sac();

    void init_sac();

    //Joueur::IteratorJetons begin_jetons(){return Joueur::IteratorJetons(*jetons,nb);}
    //Joueur::IteratorJetons end_jetons(){return Joueur::IteratorJetons(jetons[nb],0);}
    const int get_nb_sac()const{return nb;}
    void set_nb_sac(int nbr){
        if(nb<0){
            throw SplendorException("Il n'y a déjà plus de jetons dans le sac!");
        }
        nb = nbr;
    }
    const Jeton* get_jeton_i(int i) const{return jetons[i];}
    void set_sac_i(int i, Jeton* jet){jetons[i] = jet;}
    void mettre_jeton_sac(const Jeton* jet);
    void retirer_jeton_i(int i){
        if((i<0)||(i>=Sac::get_nb_sac())){
            throw SplendorException("L'indice du jeton ne peut pas être négatif, ou supérieur au nombre total de jetons autorisés");
        }
        jetons.erase(jetons.begin()+i);
        --nb;
    }

};




#endif //LO21_SPLENDOR_DUEL_SAC_H

