#include "sac.h"
#include "jeu.h"

Sac::Handler_Sac Sac::handler_sac;

Sac &Sac::get_sac(){
    if(handler_sac.instance==nullptr){
        handler_sac.instance = new Sac();
    }
    return *handler_sac.instance;
}

void Sac::libere_sac() {
    // tu oublies de libérer les jetons ?


    delete handler_sac.instance;
    handler_sac.instance = nullptr;
}

void Sac::mettre_jeton_sac(const Jeton *jet) {
    jetons.push_back(jet);
    nb++;
}

void Sac::print_sac() {
    for(int i = 0; i< Jeton::getNbMaxJetons(); i++){
        cout<<*jetons[i]<<endl;
    }
}

