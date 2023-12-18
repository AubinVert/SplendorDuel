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
    vector<const Strategy_player*> tab =  h.getPlayers();
    f<<"Nombre de joueurs dans l'historique : "<<tab.size()<<" joueurs dans l'historique :"<<endl;
    for (int i = 0; i < tab.size(); ++i) {
        f<<tab[i]<<endl;
    }
}