//
// Created by leo on 18/12/2023.
//

#include "history.h"
History::Handler History::handler;

void Hist(){

    json j1 = History::getHistory().toHistory();
    int tmp = 0;

    j1["players"].push_back(Jeu::getJeu().getCurrentPlayer().toHistory());
    j1["players"].push_back(Jeu::getJeu().getOpponent().toHistory());
    tmp += History::getHistory().getSize();
    tmp+=2;
    j1["nb_players"] = tmp;
    std::string history = j1.dump(2);
    std::ofstream file("../src/history.json");
    file << history;

}

std::ostream& operator<<(std::ostream& f, History h){
    vector< Strategy_player*> tab =  h.getPlayers();
    f<<"Nombre de joueurs dans l'historique : "<<tab.size()<<" joueurs dans l'historique :"<<endl;
    for (int i = 0; i < tab.size(); ++i) {
        tab[i]->print_player();
    }
    return f;
}


void Jeu::setPlayers() {

    string choix1;
    cout << "Le premier joueur est un joueur ou une IA [J/I]? \nChoix: " << endl;
    cin >> choix1;


    string name1;
    cout << "Veuillez entrer son nom : ";
    cin >> name1;


    string choix2;
    cout << "Le second joueur est un joueur ou une IA [J/I]? \nChoix: " << endl;
    cin >> choix2;

    string name2;
    cout << "Veuillez entrer son nom : ";
    cin >> name2;


    srand(static_cast<unsigned>(std::time(nullptr)));
    if(rand()%2==0) { // joueur qui débute la partie est tiré aléatoirement
        if (choix1 == "J") {

            if(History::getHistory().inHistory(name1,0)) {
                qui_joue = History::getHistory().pullPlayer(name1,0);
                qui_joue->print_player();
            }else {
                qui_joue = new Joueur(name1);
                qui_joue->setIa(0);
            }

        } else {

            if(History::getHistory().inHistory(name1,1)) {
                qui_joue = History::getHistory().pullPlayer(name1,1);
            }else {
                qui_joue = new IA(name1);
                qui_joue->setIa(1);
            }

        }

        if (choix2 == "J") {

            if(History::getHistory().inHistory(name2,0)) {
                adversaire = History::getHistory().pullPlayer(name2,0);
            }else {
                adversaire = new Joueur(name2);
                adversaire->setIa(0);
            }

        } else {

            if(History::getHistory().inHistory(name2,1)) {
                adversaire = History::getHistory().pullPlayer(name2,1);
            }else {
                adversaire = new IA(name2);
                adversaire->setIa(1);
            }

        }
    }else{
        if (choix1 == "J") {
            if(History::getHistory().inHistory(name1,0)) {
                adversaire = History::getHistory().pullPlayer(name1,0);
            }else {
                adversaire = new Joueur(name1);
                adversaire->setIa(0);
            }

        } else {

            if(History::getHistory().inHistory(name1,1)) {
                adversaire = History::getHistory().pullPlayer(name1,1);
            }else {
                adversaire = new IA(name1);
                adversaire->setIa(1);
            }

        }

        if (choix2 == "J") {

            if(History::getHistory().inHistory(name2,0)) {
                qui_joue = History::getHistory().pullPlayer(name2,0);
            }else {
                qui_joue = new Joueur(name2);
                qui_joue->setIa(0);
            }

        } else {

            if(History::getHistory().inHistory(name2,1)) {
                qui_joue = History::getHistory().pullPlayer(name2,1);
            }else {
                qui_joue = new IA(name2);
                qui_joue->setIa(1);
            }

        }
    }
    json j = History::getHistory().toHistory();
    cout<<j.dump(2)<<endl;


    adversaire->obtainPrivilege(); // Le joueur qui ne commence pas démarre avec un privilège
    }
