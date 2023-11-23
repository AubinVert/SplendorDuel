#include "main.h"

int main(){

    try{

        cout<<"Bienvenu dans le jeu splendor duel ! "<<endl;

        Jeu::getJeu();

        cout<<"Veuillez renseigner le pseudo du premier joueur ! "<<endl;
        string pseudo1;
        cout<<"pseudo :";
        cin>>pseudo1;
        cout<<"Veuillez renseigner le pseudo du deuxième joueur  ! "<<endl;
        string pseudo2;
        cout<<"pseudo :";
        cin>>pseudo2;

         Joueur* joueur1 = new Joueur(pseudo1);
         Joueur* joueur2 = new Joueur(pseudo2);

        Jeu::getJeu().setPlayers(joueur1,joueur2);

        cout<<"Le jeu est sur le point de commencer !\nC'est au joueur1 d'engager la partie !"<<endl;


        for (int i = 0; i < 10; ++i) {
            Jeu::getJeu().get_tour();

            cout<<"c'est à "<<Jeu::getJeu().get_tour()<<" de jouer maintenant !"<<endl;

            if(Jeu::getJeu().get_tour().getNbPrivileges()>0 || Sac::get_sac().get_nb_sac()>0){
                cout<<"Actions optionelles : "<<endl;
                if(Jeu::getJeu().get_tour().getNbPrivileges()>0){
                    string tmp;
                    while(tmp != "Y" && tmp!= "N"){
                        cout<<"Voulez vous utiliser un privilège ? Y/N"<<endl;
                        cout<<"choix :";
                        cin>>tmp;
                    }
                    if(tmp == "Y"){
                        Jeu::getJeu().get_tour().retirerPrivilege();

                        unsigned int tmp;
                        cout<<"Quel jeton voulez-vous piocher ? "<<endl;
                        cout<<"indice : ";
                        cin>>tmp;
                        Jeu::getJeu().get_tour().piocher_jeton(tmp);
                    }

                }
                if(Sac::get_sac().get_nb_sac()>0){
                    cout<<"Voulez vous remplir le plateau ? "<<endl;
                    string tmp;
                    while(tmp != "Y" && tmp!= "N"){
                        cout<<"Voulez vous utiliser un privilège ? Y/N"<<endl;
                        cout<<"choix :";
                        cin>>tmp;
                    }
                    if(tmp == "Y"){
                        Jeu::getJeu().remplirPlateau();
                        Jeu::getJeu().getOpponent().obtenir_privilege();
                    }
                }

            }




            Jeu::getJeu().tour_suivant();


        }



        //while(!Jeu::getJeu().isFinished()){

            //cout<<Jeu::getJeu().get_tour()<<endl;

            //Jeu::getJeu().tour_suivant();
        //}


    }catch(SplendorException& e){
        cout<< e.getInfos()<<endl;
    }


    return 0;
}
