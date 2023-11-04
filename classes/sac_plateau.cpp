#include "sac_plateau.h"
#include "jetons.h"
#include <iostream>


using namespace std;

//Sac

/*
void Sac::init_sac() {
    int j = 1;
    for (int i = 0; i<4; i++){
        jetons[j++] = new Jeton_gemme(j,Couleur::bleu);
    }
    for (int i = 0; i<4; i++){
        jetons[j++] = new Jeton_gemme(j,Couleur::rouge);
    }
    for (int i = 0; i<4; i++){
        jetons[j++] = new Jeton_gemme(j,Couleur::noir);
    }
    for (int i = 0; i<4; i++){
        jetons[j++] = new Jeton_gemme(j,Couleur::blanc);
    }
    for (int i = 0; i<4; i++){
        jetons[j++] = new Jeton_gemme(j,Couleur::vert);
    }
    for (int i = 0; i<2; i++){
        jetons[j++] = new Jeton_perle(j);
    }
    for (int i = 0; i<4; i++){
        jetons[j++] = new Jeton_or(j);
    }
}
*/


void Plateau::print_tab() const{
    for (size_t i = 0; i<max;i++){
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

Sac &Sac::get_sac() {
    if(handler_sac.instance==nullptr){
        handler_sac.instance = new Sac(Jeton::get_nb_max_jetons());
    }
    return *handler_sac.instance;
}

void Sac::libere_sac() {
    delete handler_sac.instance;
    handler_sac.instance = nullptr;
}



// Plateau

Plateau &Plateau::get_plateau() {
    if(handler_plateau.instance==nullptr){
        handler_plateau.instance = new Plateau(Jeton::get_nb_max_jetons());
    }
    return *handler_plateau.instance;
}

void Plateau::libere_plateau() {
    delete handler_plateau.instance;
    handler_plateau.instance = nullptr;
}
