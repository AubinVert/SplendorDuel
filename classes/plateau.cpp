#include "plateau.h"
#include "jetons.h"
#include "joueur.h"
#include <iostream>


using namespace std;

Plateau::Handler_Plateau Plateau::handler_plateau;
Plateau &Plateau::get_plateau() {
    if(handler_plateau.instance==nullptr){
        handler_plateau.instance = new Plateau();
        // au départ le plateau est rempli
        handler_plateau.instance->remplir_plateau(Sac::get_sac());
    }
    return *handler_plateau.instance;
}


void Plateau::libere_plateau() {
    delete handler_plateau.instance;
    handler_plateau.instance = nullptr;
}

void Plateau::printTab() const{
    for (size_t i = 0; i< Jeton::getNbMaxJetons(); i++){
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




void Plateau::remplir_plateau(Sac& sac) {
    srand(static_cast<unsigned>(std::time(nullptr)));
    for(int i = 0;i< Jeton::getNbMaxJetons(); i++){
        if(jetons[ordre[i]]==nullptr){
            int nb_sac = sac.get_nb_sac();
            int rdm = rand()%nb_sac;
            //cout<<"ordre[i] : "<<ordre[i]<<"; jeton : "<<rdm<<"\n";
            set_plateau_i(ordre[i],sac.get_jeton_i(rdm));
            sac.retirer_jeton_i(rdm);
        }
    current_nb++;
    }
}