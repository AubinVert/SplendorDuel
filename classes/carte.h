#ifndef LO21_SPLENDOR_DUEL_CARTE_H
#define LO21_SPLENDOR_DUEL_CARTE_H
#include <iostream>
#include <string>
#include "Exception.h"
#include <initializer_list>
#include <array>
#include <cstdlib>

using namespace std;


enum class Capacite {rejouer, voler_pion_adverse, prendre_privilege, prendre_sur_plateau, joker};  // joker dans capacité et bonus?
enum class Couleur {bleu, rouge, vert, blanc, noir};
enum class Bonus_couleur {bleu, rouge, vert, blanc, noir, joker};

string toString(Couleur c) {
    switch (c) {
        case Couleur::rouge: return "Rouge";
        case Couleur::bleu: return "Bleu";
        case Couleur::vert: return "Vert";
        case Couleur::blanc: return "Blanc";
        case Couleur::noir: return "Noir";
        default: throw SplendorException("Couleur inconnue");
    }
}
std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
extern 	std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::bleu, Couleur::vert, Couleur::blanc, Couleur::noir };

string toString(Capacite c) {
    switch (c) {
        case Capacite::rejouer: return "Rejouer";
        case Capacite::voler_pion_adverse: return "Voler un pion adverse";
        case Capacite::prendre_privilege: return "Prendre un privilege";
        case Capacite::prendre_sur_plateau: return "Prendre un pion de la même couleur que le bonus de la carte sur le plateau";
        case Capacite::joker: return "Joker";
        default: throw SplendorException("Capacite inconnue");
    }
}
std::ostream& operator<<(std::ostream& f, Capacite c) { f << toString(c); return f; }
extern 	std::initializer_list<Capacite> Capacites = { Capacite::rejouer, Capacite::voler_pion_adverse, Capacite::prendre_privilege, Capacite::prendre_sur_plateau, Capacite::joker };


string toString(Bonus_couleur bonus){
    switch (bonus) {
        case Bonus_couleur::bleu: return "Bonus Bleu";
        case Bonus_couleur::rouge: return "Bonus Rouge";
        case Bonus_couleur::vert: return "Bonus Vert";
        case Bonus_couleur::blanc: return "Bonus Blanc";
        case Bonus_couleur::noir: return "Bonus Noir";
        case Bonus_couleur::joker: return "Bonus Joker";
        default: throw SplendorException("Bonus couleur inconnu");
    }
}

ostream& operator<<(ostream& f, Bonus_couleur b) { f << toString(b); return f; }
extern std::initializer_list<Bonus_couleur> Bonus_couleurs ={ Bonus_couleur::bleu, Bonus_couleur::rouge, Bonus_couleur::vert, Bonus_couleur::blanc, Bonus_couleur::noir, Bonus_couleur::joker};


class Carte{
private:

    Carte& operator=(Carte& c) =delete;

    const Capacite capacite;
    const int points_prestige;


public:

    ~Carte() = default;

    Carte(Capacite capacite = Capacite::rejouer, int points_prestige=0) : capacite(capacite), points_prestige(points_prestige){
        if(points_prestige<0 || points_prestige>10){
            throw SplendorException("Valeur non autorisée");
        }
    }
    const Capacite& getCapacite() const{return capacite;}
    const int getPrestige() const {return points_prestige;}

    // pas besoin de setters

//    void setCapacite(Capacite capacite){
//        capacite = capacite;
//        // vérif ?
//    }
//
//
//    void setPointsPrestige(int points_prestige) {
//            if(points_prestige<0 || points_prestige>10){
//                throw SplendorException("Valeur non autorisée");
//            }else{
//                points_prestige = points_prestige;
//            }
//    }






};



class Carte_royale:public Carte{


public:

    Carte_royale(Capacite capacite = Capacite::rejouer, int points_prestige=0)
    : Carte(capacite, points_prestige){
        if(points_prestige<0 || points_prestige>10){
            throw SplendorException("Valeur non autorisée");
        }
    }

};


class Carte_joaillerie:public Carte{
    const int cout_blanc;
    const int cout_bleu;
    const int cout_rouge;
    const int cout_vert;
    const int cout_noir;
    const int cout_perle;
    const int niveau;
    const int nb_couronnes;
    const Bonus_couleur bonus;
    const int bonus_nombre;

    // bool est_reservee;


public:

    // pas besoin de setters car attributs const d'une carte

//    void setNiveau(int niveau=1)
//    {
//        if(niveau<1 || niveau >3){
//            throw SplendorException("Valeur non autorisée");
//        }else{
//            niveau = niveau;
//        }
//
//
//    }

//    void setNb_couronnes(int nb)
//    {
//        if(nb_couronnes <0 || nb_couronnes >3 ){
//            throw SplendorException("Valeur non autorisée");
//        }else{
//            nb_couronnes=nb;
//        }
//
//
//    }
//
//    void setBonusNombre(int nb) {
//            if(bonus_nombre<0 || bonus_nombre>2){
//                throw SplendorException("Valeur non autorisée");
//            }else{
//                bonus_nombre=nb;
//            }
//    }

//    void setBonus(Bonus_couleur bonus)
//    {
//        //vérification ?
//        bonus=bonus;
//    }


    const int getCoutBlanc()const{return cout_blanc;}
    const int getCoutBleu()const{return cout_bleu;}
    const int getCoutRouge()const{return cout_rouge;}
    const int getCoutVert()const{return cout_vert;}
    const int getCoutNoir()const{return cout_noir;}
    const int getCoutPerle()const{return cout_perle;}


    ~Carte_joaillerie() = default;

    Carte_joaillerie(Capacite capacite = Capacite::joker,int points_prestiges =0, int cout_blanc = 0, int cout_bleu = 0, int cout_rouge = 0, int cout_vert = 0, int cout_noir = 0, int cout_perle = 0, int niveau = 1, int nb_couronnes = 0, Bonus_couleur bonus = Bonus_couleur::bleu, int bonus_nombre = 0)
            : Carte(capacite, points_prestiges), cout_blanc(cout_blanc), cout_bleu(cout_bleu), cout_rouge(cout_rouge), cout_vert(cout_vert), cout_noir(cout_noir), cout_perle(cout_perle), niveau(niveau), nb_couronnes(nb_couronnes), bonus(bonus), bonus_nombre(bonus_nombre)
    {
        if (cout_blanc < 0 || cout_blanc > 10 || cout_bleu < 0 || cout_bleu > 10 || cout_rouge < 0 || cout_rouge > 10 || cout_vert < 0 || cout_vert > 10 || cout_noir < 0 || cout_noir > 10 || cout_perle < 0 || cout_perle > 10 || niveau < 1 || niveau > 3 || nb_couronnes < 0 || nb_couronnes > 3 || bonus_nombre < 0 || bonus_nombre > 2)
        {
            throw SplendorException("Valeur non autorisée");
        }
    }


    // pas besoin de setters car attributs const

//    void setCouts(int cout_blanc = 0, int cout_bleu=0,int cout_rouge=0,int cout_vert=0,int cout_noir=0,int cout_perle=0)
//    {
//        if(cout_blanc<0 || cout_blanc>10 || cout_bleu<0 || cout_bleu>10 || cout_rouge<0 || cout_rouge>10 || cout_vert<0 || cout_vert>10 || cout_noir<0 || cout_noir>10 || cout_perle <0 || cout_perle > 10 ){
//            throw SplendorException("Valeur non autorisée");
//        }else{
//            this->cout_blanc = cout_blanc;
//            this->cout_bleu = cout_bleu;
//            this->cout_rouge = cout_rouge;
//            this->cout_vert = cout_vert;
//            this->cout_noir = cout_noir;
//            this->cout_perle =cout_perle;
//        }
//
//    }


    const int getNiveau()const{return niveau;}
    const int get_nb_couronnes()const {return nb_couronnes;}
    const Bonus_couleur& get_bonus()const{return bonus;}
    const int get_nb_bonus() const {return bonus_nombre;}


};


inline std::ostream& operator<<(std::ostream& os, const Carte& c){
    os<<"Capacite : "<<c.getCapacite()<<"points prestiges : "<<c.getPrestige()<<endl;
    return os;
}

//std::ostream& operator<<(std::ostream& os, const Carte_royale& c){
//    os<<"Capacite : "<<c.getCapacite()<<"points prestiges : "<<c.getPrestige()<<endl;
//    return os;
//}
//
//std::ostream& operator<<(std::ostream& os, const Carte_joaillerie& c){
//    os<<"Capacite : "<<c.getCapacite()<<"points prestiges : "<<c.getPrestige()<<" Cout Perle :"<<
//    c.getCoutPerle()<<" Cout Bleu :"<<c.getCoutBleu()<<" Cout Blanc :"<<c.getCoutBlanc()<<" Cout Rouge :"<<c.getCoutRouge()
//    <<" Cout Vert :"<<c.getCoutVert()<<" Cout Noir :"<<c.getCoutNoir()<<" Bonus : "<<c.get_bonus()<<" nombre de bonus : "<<c.get_nb_bonus()
//    <<" Niveau : "<<c.getNiveau()<<endl;
//    return os;
//}


void tests_cartes();

#endif //LO21_SPLENDOR_DUEL_CARTE_H
