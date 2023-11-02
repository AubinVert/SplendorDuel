#ifndef LO21_SPLENDOR_DUEL_JETONS_H
#define LO21_SPLENDOR_DUEL_JETONS_H
#include <iostream>
#include "Exception.h"
#include "carte.h"

using namespace std;

string toString(Couleur c){
    switch (c) {
        case Couleur::rouge: return "Rouge";
        case Couleur::bleu: return "Bleu";
        case Couleur::vert: return "Vert";
        case Couleur::blanc: return "Blanc";
        case Couleur::noir: return "Noir";
        default: throw SplendorException("Couleur inconnue");
    }
}

class Jeton{
    // il faut garantir l'unicité de chaque jeton
    int id;

public:


    Jeton(int id):id(id){}
    ~Jeton()=default;
    Jeton& operator=(const Jeton& jet)=delete;
    Jeton(const Jeton& jet)=delete;

    const int get_id()const{return id;}
};

class Jeton_perle:public Jeton{

public:
    static int nb_perle;
    static int max_perle;
    Jeton_perle(int id):Jeton(id){
        if((id<1)||(id>25)){
            throw SplendorException("Id de jeton négatif!");
        }
        if(nb_perle<max_perle){
            nb_perle++;
        }else{
            throw SplendorException("Impossible de créer plus de jetons perle!");
        }
    }
};


class Jeton_or:public Jeton{

public:
    static int nb_or;
    static int max_or;
    Jeton_or(int id):Jeton(id){
        if((id<1)||(id>25)){
            throw SplendorException("Id de jeton négatif!");
        }
        if(nb_or<max_or){
            nb_or++;
        }else{
            throw SplendorException("Impossible de créer plus de jetons or!");
        }
    };

};

class Jeton_gemme:public Jeton{
    Couleur couleur;
public:
    static int nb_vert;
    static int max_vert;
    static int nb_rouge;
    static int max_rouge;
    static int nb_bleu;
    static int max_bleu;
    static int nb_blanc;
    static int max_blanc;
    static int nb_noir;
    static int max_noir;

    Jeton_gemme(int id, Couleur coul):Jeton(id),couleur(coul){
        if((id<1)||(id>25)){
            throw SplendorException("Id de jeton négatif!");
        }
        switch (coul){
            case Couleur::rouge:{
                if(nb_rouge<max_rouge){
                    nb_rouge++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons rouge!");
                }
            }
            case Couleur::bleu: {
                if(nb_bleu<max_bleu){
                    nb_bleu++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons bleu!");
                }
            }
            case Couleur::vert: {
                if(nb_vert<max_vert){
                    nb_vert++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons vert!");
                }
            }
            case Couleur::blanc:{
                if(nb_blanc<max_blanc){
                    nb_blanc++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons blanc!");
                }
            }
            case Couleur::noir:{
                if(nb_noir<max_noir){
                    nb_noir++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons noir!");
                }
            }
            default: throw SplendorException("Couleur inconnue");
        }
    }

    const Couleur& get_couleur() const{return couleur;}
    void set_couleur(const Couleur& coul){couleur = coul;}
};


int Jeton_gemme::Jeton_gemme::nb_blanc = 0;
int Jeton_gemme::Jeton_gemme::nb_bleu = 0;
int Jeton_gemme::Jeton_gemme::nb_rouge = 0;
int Jeton_gemme::Jeton_gemme::nb_vert = 0;
int Jeton_gemme::Jeton_gemme::nb_noir = 0;

int Jeton_gemme::Jeton_gemme::max_blanc = 4;
int Jeton_gemme::Jeton_gemme::max_bleu = 4;
int Jeton_gemme::Jeton_gemme::max_rouge = 4;
int Jeton_gemme::Jeton_gemme::max_vert = 4;
int Jeton_gemme::Jeton_gemme::max_noir = 4;

int Jeton_or::Jeton_or::nb_or = 0;
int Jeton_or::Jeton_or::max_or = 3;

int Jeton_perle::Jeton_perle::nb_perle = 0;
int Jeton_perle::Jeton_perle::max_perle = 2;




ostream& operator<<(ostream& f, Jeton_gemme& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: "<<toString(jet.get_couleur());
    return f;
}

ostream& operator<<(std::ostream& f, Jeton_perle& jet){
    f << "id: " << jet.get_id() << "; couleur: perle";
    return f;
}

ostream& operator<<(ostream& f, Jeton_or& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: or";
    return f;
}





#endif //LO21_SPLENDOR_DUEL_JETONS_H
