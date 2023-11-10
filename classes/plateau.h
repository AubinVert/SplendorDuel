#ifndef LO21_SPLENDOR_DUEL_PLATEAU_H
#define LO21_SPLENDOR_DUEL_PLATEAU_H
#include <iostream>
#include <vector>
#include "Exception.h"
#include "jetons.h"
#include "joueur.h"
#include "sac.h"

const int ordre[25] = {12,7,8,13,18,17,16,11,6,1,2,3,4,9,14,19,24,23,22,21,20,15,10,5,0};

using namespace std;


class Plateau{
    /*
     * On prend la disposition de plateau suivante, selon l'ordre des jetons dans le tableau:
     *     0   |  1   |   2  |   3  |  4
     *   --------------------------------
     *     5   |  6   |  7   |   8  |  9
     *   --------------------------------
     *     10  |  11  |  12  |  13  |  14
     *   --------------------------------
     *     15  |  16  |  17  |  18  |  19
     *   --------------------------------
     *     20  |  21  |  22  |  23  |  24
     */


    int nb = 0;
    vector<const Jeton*> jetons;
    struct Handler_Plateau{
        Plateau * instance = nullptr;
        ~Handler_Plateau(){
            delete instance;
            instance = nullptr;
        }
    };
    static Handler_Plateau handler_plateau;
    Plateau():nb(0),jetons(){
        for (size_t i = 0; i<Jeton::get_nb_max_jetons();i++){
            jetons.push_back(nullptr);
        }
    };
    ~Plateau()=default; // car agrégation !
    Plateau& operator=(const Plateau& p)=delete;
    Plateau(const Plateau& p)=delete;
public:

    static Plateau& get_plateau();
    static void libere_plateau();


    const Jeton* get_plateau_i(int i) const{return jetons[i];}
    void set_plateau_i(int i,const Jeton* jet){jetons[i] = jet;}
    const Jeton* get_droite_i(int i) const{
        if((i+1)%5 != 0){
            return jetons[++i];
        }else{
            return nullptr;
        }
    }
    const Jeton* get_gauche_i(int i) const{
        if(i%5 != 0){
            return jetons[--i];
        }else{
            return nullptr;
        }
    }
    const Jeton* get_dessus_i(int i) const{
        if(i>4){
            return jetons[i-5];
        }else{
            return nullptr;
        }
    }
    const Jeton* get_dessous_i(int i) const{
        if(i<20){
            return jetons[i+5];
        }else{
            return nullptr;
        }
    }



    void remplir_plateau(Sac& sac);
    void print_tab() const;

};

Plateau::Handler_Plateau Plateau::handler_plateau;
Plateau &Plateau::get_plateau() {
    if(handler_plateau.instance==nullptr){
        handler_plateau.instance = new Plateau();
    }
    return *handler_plateau.instance;
}

void Plateau::libere_plateau() {
    delete handler_plateau.instance;
    handler_plateau.instance = nullptr;
}

void Plateau::print_tab() const{
    for (size_t i = 0; i<Jeton::get_nb_max_jetons();i++){
        if(jetons[i]!=nullptr){
            if((i+1)%5 == 0){
                cout<<*jetons[i]<<"\n";
            }else{
                cout<<*jetons[i]<<" | ";
            }
        }else{
            if((i+1)%5 == 0){
                cout<<"id: null; couleur: null\n";
            }else{
                cout<<"id: null; couleur: null | ";
            }
        }
    }
}



void Plateau::remplir_plateau(Sac &sac) {
    srand(static_cast<unsigned>(std::time(nullptr)));
    for(int i = 0;i<Jeton::get_nb_max_jetons();i++){
        if(jetons[ordre[i]]==nullptr){
            int nb_sac = sac.get_nb_sac();
            int rdm = rand()%nb_sac;
            //cout<<"ordre[i] : "<<ordre[i]<<"; jeton : "<<rdm<<"\n";
            set_plateau_i(ordre[i],sac.get_jeton_i(rdm));
            sac.retirer_jeton_i(rdm);
        }
    }
}


#endif //LO21_SPLENDOR_DUEL_PLATEAU_H
