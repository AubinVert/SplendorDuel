#include "jetons.h"
#include "carte.h"
#include <iostream>

using namespace std;

int Jeton::nb_blanc = 0;
int Jeton::nb_bleu = 0;
int Jeton::nb_rouge = 0;
int Jeton::nb_vert = 0;
int Jeton::nb_noir = 0;
int Jeton::nb_or = 0;
int Jeton::nb_perle = 0;

vector<const Jeton*> initJetons(){
    vector<const Jeton*> tab;
    int id = 1;

    for (int i = 0; i < 3; ++i) {
        Jeton* tmp = new Jeton(id, Color::gold);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 2; ++i) {
        Jeton* tmp = new Jeton(id, Color::perle);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id, Color::rouge);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id, Color::bleu);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id, Color::vert);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id, Color::noir);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id, Color::blanc);
        tab.push_back(tmp);
        id++;
    }

    return tab;
}
