#ifndef LO21_SPLENDOR_DUEL_MAIN_H
#define LO21_SPLENDOR_DUEL_MAIN_H


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


#endif //LO21_SPLENDOR_DUEL_MAIN_H
