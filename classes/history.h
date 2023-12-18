//
// Created by leo on 18/12/2023.
//

#ifndef LO21_SPLENDOR_DUEL_HISTORY_H
#define LO21_SPLENDOR_DUEL_HISTORY_H

#include "jeu.h"

 json toHistoryCurrent()  {
    json j;
    j.push_back(Jeu::getJeu().getCurrentPlayer().toHistory());
    j.push_back(Jeu::getJeu().getOpponent().toHistory());
    return j;
}

class History{

private:

    //singleton
    struct Handler {
        History * instance = nullptr;
        ~Handler() {
            delete instance;
            instance = nullptr;
        }
    };
    static Handler handler;

    //attributs
    vector<const Strategy_player*> players;
    unsigned int nb_players = 0;

    //méthodes

    History(json data){

        for (int i = 0; i < data["nb_players"]; ++i) {
            if(data["players"][i]["is_ia"]){
                players.push_back(new IA(data["players"][i]));
                nb_players++;
            }
            else{
                players.push_back(new Joueur(data["players"][i]));
                nb_players++;
            }
        }
    }

    ~History() = default;
    History (const History&) = delete;
    History& operator=(const History&) = delete;

public:


    void toHistory(){
        json j;
        j["players"] = {};
        for (int i = 0; i < nb_players; ++i) {
            j["players"].push_back(players[i]->toHistory());
        }
        // on ajoute les deux derniers joueurs à la fin.
        j["players"].push_back(toHistoryCurrent()[0]);
        j["players"].push_back(toHistoryCurrent()[1]);

    }

    History& getHistory(json data){
        if (handler.instance == nullptr)  handler.instance = new History(data);
        return *handler.instance;
    }


};




#endif //LO21_SPLENDOR_DUEL_HISTORY_H
