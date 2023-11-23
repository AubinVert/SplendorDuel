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
        Jeton* tmp = new Jeton(id,Couleur::gold);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 2; ++i) {
        Jeton* tmp = new Jeton(id,Couleur::perle);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id,Couleur::rouge);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id,Couleur::bleu);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id,Couleur::vert);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id,Couleur::noir);
        tab.push_back(tmp);
        id++;
    }
    for (int i = 0; i < 4; ++i) {
        Jeton* tmp = new Jeton(id,Couleur::blanc);
        tab.push_back(tmp);
        id++;
    }

    return tab;
}
