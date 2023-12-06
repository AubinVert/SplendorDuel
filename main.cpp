#include "main.h"

int main(){



        cout<<"Bienvenue dans le jeu splendor duel ! "<<endl;

        Jeu::getJeu();

        Jeu::getJeu().setPlayers();

        cout<<"Le jeu est sur le point de commencer !\nC'est au joueur1 d'engager la partie !"<<endl;

        unsigned int from_error =0;

        while (!Jeu::getJeu().isFinished()) {


            if(from_error == 0){
                Jeu::getJeu().get_tour();

                cout<<"\n\nPlateau :"<<endl;
                Plateau::get_plateau().printTab();

                cout<<"\n\nTirage1 :"<<endl;
                cout<<*Jeu::getJeu().get_tirage_1()<<endl;
                cout<<"\nTirage2 :"<<endl;
                cout<<*Jeu::getJeu().get_tirage_2()<<endl;
                cout<<"\nTirage3 :"<<endl;
                cout<<*Jeu::getJeu().get_tirage_3()<<endl;

                cout<<"Etat des joueurs : "<<endl;
                cout<<Jeu::getJeu().getCurrentPlayer()<<endl;
                cout<<Jeu::getJeu().getOpponent()<<endl;
                cout<<"c'est à "<<Jeu::getJeu().get_tour().getName()<<" de jouer ! "<<endl;
            }
            try{

                Jeu::getJeu().getCurrentPlayer().choice();
                Jeu::getJeu().tour_suivant();
                from_error = 0;

            }catch(SplendorException& e){
                from_error = 1;
                cout<<"=============ACTION NON AUTORISÉE ================="<<endl;
                cout<< e.getInfos()<<endl;
            }

        }
    Jeu::libereJeu();

    return 0;
}
