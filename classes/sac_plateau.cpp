#include "sac_plateau.h"
#include "jetons.h"
#include <iostream>


using namespace std;

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