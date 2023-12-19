//
// Created by leo on 18/12/2023.
//

#include "history.h"
History::Handler History::handler;

Match::Match(json data){



    if(data["gagnant"]["is_ia"]==1){

    string tmp = data["gagnant"]["nom"];
        if(!History::getHistory().inHistory(tmp, 1)){
            gagnant = new IA(tmp);
            gagnant->setWins(data["gagnant"]["games_won"]);
            gagnant->setPlayed(data["gagnant"]["games"]);
            gagnant->setIa(1);
        }else{
            gagnant = History::getHistory().pullPlayer(tmp,1);
        }

    }else{
    string tmp = data["gagnant"]["nom"];
        if(!History::getHistory().inHistory(tmp, 0)){
            gagnant = new Joueur(tmp);
            gagnant->setWins(data["gagnant"]["games_won"]);
            gagnant->setPlayed(data["gagnant"]["games"]);
            gagnant->setIa(0);}
        else{
            gagnant = History::getHistory().pullPlayer(tmp,0);
        }

    }
    if(data["adversaire"]["is_ia"]==1){
    string tmp = data["adversaire"]["nom"];
        if(!History::getHistory().inHistory(tmp, 1)){
            adversaire = new IA(tmp);
            adversaire->setWins(data["adversaire"]["games_won"]);
            adversaire->setPlayed(data["adversaire"]["games"]);
            adversaire->setIa(1);
        }
        else{
            adversaire = History::getHistory().pullPlayer(tmp,1);
        }


    }else{
    string tmp = data["adversaire"]["nom"];
        if(!History::getHistory().inHistory(tmp, 0)){
            adversaire = new Joueur(tmp);
            adversaire->setWins(data["adversaire"]["games_won"]);
            adversaire->setPlayed(data["adversaire"]["games"]);
            adversaire->setIa(0);}
        else{
            adversaire = History::getHistory().pullPlayer(tmp,0);
        }
    }
    score_gagnant = data["score_gagnant"];
    score_adversaire = data["score_adversaire"];

}

void Hist(){

    json j1; //on récup l'ancien historique
    int tmp = 0;

    // on ajoute le nouveau
    json jtmp = History::getHistory().toHistory();
    cout<<History::getHistory().getSize()<<endl;

    for (int i = 0; i < History::getHistory().getSize(); ++i) {
        j1["matches"].push_back(jtmp[i]);
    }

    json j2 = {};
    j2["gagnant"] = Jeu::getJeu().getCurrentPlayer().toHistory();
    j2["adversaire"] = Jeu::getJeu().getOpponent().toHistory();
    j2["score_gagnant"] = Jeu::getJeu().getCurrentPlayer().getNbPoints();
    j2["score_adversaire"] = Jeu::getJeu().getOpponent().getNbPoints();
    j1["matches"].push_back(j2);

    tmp += History::getHistory().getSize();
    tmp+=1;

    j1["nb_matches"] = tmp;
    std::string history = j1.dump(2);
    cout <<history<<endl;
    std::ofstream file("../src/history.json");
    file << history;

}


void Jeu::setPlayers(){

    string choix1;
    cout<<"Le premier joueur est un joueur ou une IA [J/I]? \nChoix: "<<endl;
    cin>>choix1;

    string name1;
    cout << "Veuillez entrer son nom : ";
    cin >> name1;


    string choix2;
    cout<<"Le second joueur est un joueur ou une IA [J/I]? \nChoix: "<<endl;
    cin>>choix2;

    string name2;
    cout << "Veuillez entrer son nom : ";
    cin >> name2;



    srand(static_cast<unsigned>(std::time(nullptr)));
    if(rand()%2==0) { // joueur qui débute la partie est tiré aléatoirement
        if (choix1 == "J") {
            if(History::getHistory().inHistory(name1,0)){
                qui_joue = History::getHistory().pullPlayer(name1,0);
            }else{
                qui_joue = new Joueur(name1);
                qui_joue->setIa(0);
            }
        } else {

            if(History::getHistory().inHistory(name1,1)){
                qui_joue = History::getHistory().pullPlayer(name1,1);
            }else{
                qui_joue = new IA(name1);
                qui_joue->setIa(1);
            }
        }

        if (choix2 == "J") {

            if(History::getHistory().inHistory(name2,0)){
                adversaire = History::getHistory().pullPlayer(name2,0);
            }else{
                adversaire = new Joueur(name2);
                adversaire->setIa(0);
            }

        } else {
            if(History::getHistory().inHistory(name2,1)){
                adversaire = History::getHistory().pullPlayer(name2,1);
            }else{
                adversaire = new IA(name2);
                adversaire->setIa(1);
            }

        }
    }else{
        if (choix1 == "J") {
            if(History::getHistory().inHistory(name1,0)){
                adversaire = History::getHistory().pullPlayer(name1,0);
            }else{
                adversaire = new Joueur(name1);
                adversaire->setIa(0);
            }

        } else {
            if(History::getHistory().inHistory(name1,1)){
                adversaire = History::getHistory().pullPlayer(name1,1);
            }else{
                adversaire = new IA(name1);
                adversaire->setIa(1);
            }

        }
        if (choix2 == "J") {

            if(History::getHistory().inHistory(name2,0)){
                qui_joue = History::getHistory().pullPlayer(name2,0);
            }else{
                qui_joue = new Joueur(name2);
                qui_joue->setIa(0);
            }
        } else {
            if(History::getHistory().inHistory(name2,1)){
                qui_joue = History::getHistory().pullPlayer(name2,1);
            }else{
                qui_joue = new IA(name2);
                qui_joue->setIa(1);
            }

        }
    }
    adversaire->obtainPrivilege(); // Le joueur qui ne commence pas démarre avec un privilège


}