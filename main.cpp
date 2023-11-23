#include "main.h"

int main(){

    try{
        //cout<<"Vous vounez de lancer le jeu Splendor Duel"<<endl;

        // création du jeu :
        //Jeu::getJeu();

        // création des joueurs.

        testJoueurs();


    }catch(SplendorException& e){
        cout<< e.getInfos()<<endl;
    }


    return 0;
}
