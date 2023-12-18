//
// Created by leo on 18/12/2023.
//

#ifndef LO21_SPLENDOR_DUEL_HISTORY_H
#define LO21_SPLENDOR_DUEL_HISTORY_H

#include "jeu.h"


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
    vector<Strategy_player*> players;
    unsigned int nb_players = 0;

    //méthodes


    History()  = default;

    ~History() = default;
    History (const History&) = delete;
    History& operator=(const History&) = delete;

public:

    vector<Strategy_player*> getPlayers() const {
        return players;
    }

     Strategy_player* pullPlayer(const string nom, unsigned int is_ia) {
        for (int i = 0; i < players.size(); ++i) {
            if(players[i]->getName() == nom && players[i]->getIa()){
                 Strategy_player* tmp = players[i];
                players.erase(players.begin()+i);
                return tmp;
            }
        }
    }

    const bool inHistory(const string nom, const int is_ia) const {
        for (int i = 0; i < players.size(); ++i) {
            if(players[i]->getName()== nom && players[i]->getIa() == is_ia){
                return true;
            }
        }
        return false;
    }


     unsigned int getSize() const{
        return nb_players;
    }

    void initHistory(json data){
        cout<<data["nb_players"]<<endl;
        for (int i = 0; i < data["nb_players"]; ++i) {
            if(data["players"][i]["is_ia"] == 1){
                players.push_back(new IA(data["players"][i]));
                nb_players++;
            }
            else{
                players.push_back(new Joueur(data["players"][i]));
                nb_players++;
            }
        }
    }

    json toHistory(){
        json j;
        j["players"] = {};
        for (int i = 0; i < nb_players; ++i) {
            j["players"].push_back(players[i]->toHistory());
        }
        return j;
    }

    static History& getHistory(){
        if (handler.instance == nullptr)  handler.instance = new History;
        return *handler.instance;
    }


};

void Hist();

std::ostream& operator<<(std::ostream& f, History h);


#endif //LO21_SPLENDOR_DUEL_HISTORY_H
