#ifndef LO21_SPLENDOR_DUEL_CARTE_H
#define LO21_SPLENDOR_DUEL_CARTE_H
#include <iostream>
#include <string>
#include <cstring>
#include "Exception.h"
#include <initializer_list>
#include <array>
#include <cstdlib>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <optional>

using json = nlohmann::json;

using namespace std;



enum  class  Capacite {rejouer, voler_pion_adverse, prendre_privilege, prendre_sur_plateau, joker};
enum  class Couleur {bleu, rouge, vert, blanc, noir, perle, gold};
enum class Bonus_couleur {bleu, rouge, vert, blanc, noir, joker};





optional<Capacite> getCapaciteFromString(const std::string& str);
optional<Bonus_couleur> getBonusFromString(const std::string& str);


std::string toString(Couleur c);
std::string toString(Capacite c);
std ::string toString(optional<enum Bonus_couleur> bonus);

std::ostream& operator<<(std::ostream& f, Couleur c);
std::ostream& operator<<(std::ostream& f, optional<Capacite> c);
std::ostream& operator<<(ostream& f, optional<Bonus_couleur> b);

extern 	std::initializer_list<Couleur> Couleurs;
extern 	std::initializer_list<Capacite> Capacites;
extern std::initializer_list<Bonus_couleur> Bonus_couleur;

class Carte{

protected:

    static const int MAX=71;
    static int nb_cartes;

private:


    Carte& operator=(Carte& c) =delete;

    const optional<Capacite> capacite;
    const int points_prestige;


public:


    static int getNbCartes(){
        return nb_cartes;
    }

    ~Carte(){
        nb_cartes--;
    }

    explicit Carte(int points_prestige=0, std::optional<Capacite> capacite = std::nullopt) : capacite(capacite), points_prestige(points_prestige){
        if(nb_cartes > MAX){
            throw SplendorException("Maximum de cartes atteint");
        }

        if(points_prestige<0 || points_prestige>10){
            throw SplendorException("Valeur non autorisée");
        }
        ++nb_cartes;
    }

    const optional<Capacite>& getCapacite() const{return capacite;}



    const int getPrestige() const {return points_prestige;}



};
class Carte_royale:public Carte{

public:


    Carte_royale(int points_prestige=0,std::optional<Capacite> capacite = nullopt)
            : Carte(points_prestige, capacite){
        if(points_prestige<0 || points_prestige>10){
            throw SplendorException("Valeur non autorisée");
        }
        if(nb_cartes > MAX){
            throw SplendorException("Maximum de cartes atteint");

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
    const optional<enum Bonus_couleur> bonus;
    const int bonus_nombre;



public:



    const int getCoutBlanc()const{return cout_blanc;}
    const int getCoutBleu()const{return cout_bleu;}
    const int getCoutRouge()const{return cout_rouge;}
    const int getCoutVert()const{return cout_vert;}
    const int getCoutNoir()const{return cout_noir;}
    const int getCoutPerle()const{return cout_perle;}




    Carte_joaillerie(int points_prestiges =0, int cout_blanc = 0, int cout_bleu = 0, int cout_rouge = 0, int cout_vert = 0, int cout_noir = 0, int cout_perle = 0, int niveau = 1, int nb_couronnes = 0,int bonus_nombre = 0, optional<enum Bonus_couleur> bonus = nullopt,optional<Capacite> capacite = nullopt)
            : Carte(points_prestiges, capacite), cout_blanc(cout_blanc), cout_bleu(cout_bleu), cout_rouge(cout_rouge), cout_vert(cout_vert), cout_noir(cout_noir), cout_perle(cout_perle), niveau(niveau), nb_couronnes(nb_couronnes), bonus(bonus), bonus_nombre(bonus_nombre)
    {
        if(nb_cartes > MAX){

            throw SplendorException("Maximum de cartes atteint");

        }
        if (cout_blanc < 0 || cout_blanc > 10 || cout_bleu < 0 || cout_bleu > 10 || cout_rouge < 0 || cout_rouge > 10 || cout_vert < 0 || cout_vert > 10 || cout_noir < 0 || cout_noir > 10 || cout_perle < 0 || cout_perle > 10 || niveau < 1 || niveau > 3 || nb_couronnes < 0 || nb_couronnes > 5 || bonus_nombre < 0 || bonus_nombre > 5)
        {
            throw SplendorException("Valeur non autorisée");
        }


    }



    const int getNiveau()const{return niveau;}
    const int get_nb_couronnes()const {return nb_couronnes;}
    const optional<enum Bonus_couleur>& get_bonus()const{return bonus;}
    const int getNbBonus() const {return bonus_nombre;}


};

inline std::ostream& operator<<(std::ostream& os, const Carte& c){
    os<<"Capacite : "<< c.getCapacite() <<" points prestiges : "<<c.getPrestige()<<endl;
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const Carte_royale& c){
    os<<"Capacite : "<< c.getCapacite()<<", points prestiges : "<<c.getPrestige()<<endl;
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const Carte_joaillerie& c){
    
    os<<"Capacite : "<< c.getCapacite();
    if(c.getPrestige() != 0){
        os<<", points prestiges : "<<c.getPrestige();
    }
    if(c.getCoutPerle()!=0 ){
        os<<", Cout Perle :"<<
          c.getCoutPerle();
    }
    if(c.getCoutBlanc()!=0 ){
        os<<", Cout Blanc :"<<
          c.getCoutBlanc();
    }
    if(c.getCoutBleu()!=0 ){
        os<<", Cout Bleu :"<<
          c.getCoutBleu();
    }
    if(c.getCoutRouge()!=0 ){
        os<<", Cout Rouge :"<<
          c.getCoutRouge();
    }
    if(c.getCoutNoir()!=0 ){
        os<<", Cout Noir :"<<
          c.getCoutNoir();
    }
    if(c.getNbBonus() != 0){
        os<<", Bonus : "<<c.get_bonus()<<", nombre de bonus : "<< c.getNbBonus();
    }
    os<<", Niveau : "<<c.getNiveau()<<endl;

    return os;
}



vector<const Carte_royale*> initCartesRoyales();
vector<const Carte_joaillerie*> initCartesJoaillerie();







void testInitCartes();
#endif //LO21_SPLENDOR_DUEL_CARTE_H

