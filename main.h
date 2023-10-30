#ifndef LO21_SPLENDOR_DUEL_MAIN_H
#define LO21_SPLENDOR_DUEL_MAIN_H
#include <iostream>

using namespace std;
// classe par énumération à créer: capacité, bonus_couleur, couleur (pour les jetons)

enum class Capacite {rejouer, voler_pion_adverse, prendre_privilege, prendre_sur_plateau, joker};// joker dans capacité et bonus?
enum class Couleur {bleu, rouge, vert, blanc, noir};
enum class Bonus_couleur {bleu, rouge, vert, blanc, noir, joker};

class Carte{
    Capacite capacite;
    int points_prestige;
};

class Carte_royale:public Carte{

};

class Carte_joaillerie:public Carte{
    int cout_blanc;
    int cout_bleu;
    int cout_rouge;
    int cout_vert;
    int cout_noir;
    int cout_perle;
    int niveau;
    int nb_couronnes;
    Bonus_couleur bonus;
    int bonus_nombre;
    // bool est_reservee;
};


class Pioche{
    int niveau;
    int nb;
    int max;
    Carte_joaillerie ** cartes; // vérifier si on peut pas mettre déjà une taille
};

class Tirage{
    int niveau;
    int nb;
    int max;
    Carte_joaillerie ** cartes;
    Pioche * pioche;
};

class Jeton{
    int id;
};

class Jeton_perle:public Jeton{

};

class Jeton_or:public Jeton{

};

class Jeton_gemme:public Jeton{
    Couleur couleur;
};

class Privilege{
    int id;
};

class Sac{
    int nb;
    int max;
    Jeton** jetons;//vérifier
};

class Plateau{
    int nb;
    int max;
    Jeton * jetons[][]; // vérifier
};

class Joueur{
    string nom;
    int nb_points;
    int nb_courones;
    int nb_cartes_j;
    int nb_cartes_r;
    int nb_privileges;

    int max_nb_jetons;
    int max_nb_cartes_j;

    Carte_joaillerie** cartes_joaillerie;
    Carte_royale* cartes_royale[3]; // ok pour agrégation?
    Jeton ** jetons;
    Privilege* privileges[3]; // ok pour agrégation?


};

class Jeu{
    bool est_termine;
    bool contre_IA;
    Joueur* qui_joue;
    Joueur* adversaire;

    // tableaux contenants tous les objets à la création du jeu
    Sac* sac;
    Plateau* plateau;
    Carte* cartes[67]; // contient toutes les cartes du jeu
    Jeton* jetons[15]; // contient tous les jetons
    Privilege* privileges[3];


};


#endif //LO21_SPLENDOR_DUEL_MAIN_H
