#ifndef LO21_SPLENDOR_DUEL_CARTE_H
#define LO21_SPLENDOR_DUEL_CARTE_H
#include <iostream>

using namespace std;


enum class Capacite {rejouer, voler_pion_adverse, prendre_privilege, prendre_sur_plateau, joker};// joker dans capacité et bonus?
enum class Couleur {bleu, rouge, vert, blanc, noir};
enum class Bonus_couleur {bleu, rouge, vert, blanc, noir, joker};

class Carte{
    Capacite capacite;
    int points_prestige;
public:
    const Capacite& get_capacite() const{return capacite;}
    const int get_prestige() const {return points_prestige;}
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
public:
    const int getCoutBlanc()const{return cout_blanc;}
    const int getCoutBleu()const{return cout_bleu;}
    const int getCoutRouge()const{return cout_rouge;}
    const int getCoutVert()const{return cout_vert;}
    const int getCoutNoir()const{return cout_noir;}
    const int getCoutPerle()const{return cout_perle;}
    void setCouts();
    const int getNiveau()const{return niveau;}
    const int get_nb_couronnes()const {return nb_couronnes;}
    const Bonus_couleur& get_bonus()const{return bonus;}
    const int get_nb_bonus() const {return bonus_nombre;}
};





#endif //LO21_SPLENDOR_DUEL_CARTE_H
