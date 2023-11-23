#include "sac.h"

Sac::Handler_Sac Sac::handler_sac;

Sac &Sac::get_sac(){
    if(handler_sac.instance==nullptr){
        handler_sac.instance = new Sac();
        handler_sac.instance->init_sac();
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


void Sac::init_sac(){
    int j = 1;
    for (int i = 0; i<4; i++) {
        mettre_jeton_sac(new Jeton(j++, Color::bleu));
    }
    for (int i = 0; i<4; i++){
        mettre_jeton_sac(new Jeton(j++, Color::rouge));
    }
    for (int i = 0; i<4; i++){
        mettre_jeton_sac(new Jeton(j++, Color::vert));
    }
    for (int i = 0; i<4; i++){
        mettre_jeton_sac(new Jeton(j++, Color::blanc));
    }
    for (int i = 0; i<4; i++){
        mettre_jeton_sac(new Jeton(j++, Color::noir));
    }
    for (int i = 0; i<2; i++){
        mettre_jeton_sac(new Jeton(j++, Color::perle));
    }
    for (int i = 0; i<3; i++){
        mettre_jeton_sac(new Jeton(j++, Color::gold));
    }
}

void Sac::print_sac() {
    for(int i = 0; i< Jeton::getNbMaxJetons(); i++){
        cout<<*jetons[i]<<endl;
    }
}

