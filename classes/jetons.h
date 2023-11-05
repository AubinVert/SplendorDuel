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
        case Couleur::gold: return "Or";
        case Couleur::perle: return "Perle";
        default: throw SplendorException("Couleur inconnue");
    }
}

class Jeton{
    // il faut garantir l'unicité de chaque jeton
    const int id;
    const Couleur couleur;

    static int nb_perle;
    static const int max_perle = 2;
    static int nb_or;
    static const int max_or = 3;
    static int nb_vert;
    static const int max_vert = 4;
    static int nb_rouge;
    static const int max_rouge = 4;
    static int nb_bleu;
    static const int max_bleu = 4;
    static int nb_blanc;
    static const int max_blanc = 4;
    static int nb_noir;
    static const int max_noir = 4;


public:



    Jeton(int id, Couleur& coul):id(id),couleur(coul){
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
            case Couleur::perle:{
                if(nb_perle<max_perle){
                    nb_perle++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons perle!");
                }
            }
            case Couleur::gold:{
                if(nb_or<max_or){
                    nb_or++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons or!");
                }
            }
            default: throw SplendorException("Couleur inconnue");
        }
    }
    ~Jeton()=default;
    Jeton& operator=(const Jeton& jet)=delete;
    Jeton(const Jeton& jet)=delete;

    const Couleur& get_couleur(){return couleur;}
    const int get_id()const{return id;}



    static int get_nb_max_jetons(){return max_bleu+max_blanc+max_or+max_noir+max_perle+max_rouge+max_vert}


};
/*
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
};*/


int Jeton::nb_blanc = 0;
int Jeton::nb_bleu = 0;
int Jeton::nb_rouge = 0;
int Jeton::nb_vert = 0;
int Jeton::nb_noir = 0;
int Jeton::nb_or = 0;
int Jeton::nb_perle = 0;











ostream& operator<<(ostream& f, Jeton& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: "<<toString(jet.get_couleur());
    return f;
}






#endif //LO21_SPLENDOR_DUEL_JETONS_H
