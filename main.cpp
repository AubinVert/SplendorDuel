#include "main.h"

int main(){
    srand(static_cast<unsigned>(std::time(nullptr)));

    cout<<"Bienvenue dans le jeu splendor duel ! "<<endl;

    Jeu::getJeu();
    Jeu::getJeu().setPlayers();

    cout<<"Le jeu est sur le point de commencer !\nC'est au joueur1 d'engager la partie !"<<endl;

    unsigned int from_error =0;

    while (!Jeu::getJeu().isFinished()) {


        if(from_error == 0){
            Jeu::getJeu().get_tour();

            cout<<"Etat des joueurs : "<<endl;
            Jeu::getJeu().getCurrentPlayer().print_player();
            cout<<"Bonus blanc"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::blanc)<<endl;
            cout<<"Bonus vert"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::vert)<<endl;
            cout<<"Bonus bleu"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::bleu)<<endl;
            cout<<"Bonus rouge"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::red)<<endl;
            cout<<"Bonus noir"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::noir)<<endl;
            cout<<"Bonus joker"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::joker)<<endl;
            cout<<endl;

            cout<<"Il y a "<<Sac::get_sac().get_nb_sac()<<" jetons dans le sac."<<endl;

            cout<<"\n\nPlateau :"<<endl;
            Plateau::get_plateau().printTab();

            cout<<"\n\nTirage1 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_1()<<endl;
            cout<<"\nTirage2 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_2()<<endl;
            cout<<"\nTirage3 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_3()<<endl;



            cout<<"c'est à "<<Jeu::getJeu().get_tour().getName()<<" de jouer ! "<<endl;
        }
        try{

            Jeu::getJeu().getCurrentPlayer().choice();
            Jeu::getJeu().getCurrentPlayer().verifJetons();
            if(Jeu::getJeu().getCurrentPlayer().royaleCardEligibility()==1){
                Jeu::getJeu().getCurrentPlayer().selectionRoyalCard();
            }
            Jeu::getJeu().tour_suivant();
            from_error = 0;

        }catch(SplendorException& e){
            from_error = 1;
            cout<<"============= ACTION NON AUTORISÉE ================="<<endl;
            cout<< e.getInfos()<<endl;
        }

    }
    //Jeu::libereJeu();
    cout<<"=================== Partie temrinée ==================="<<endl;
    cout<<"Stats du gagnant:"<<endl;
    Jeu::getJeu().getCurrentPlayer().print_player();

    return 0;
}
