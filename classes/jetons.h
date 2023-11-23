#ifndef LO21_SPLENDOR_DUEL_JETONS_H
#define LO21_SPLENDOR_DUEL_JETONS_H
#include <iostream>
#include <vector>
#include "Exception.h"
#include "carte.h"

using namespace std;


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

    Jeton(int id,const Couleur& coul):id(id),couleur(coul){
        if((id<1)||(id>Jeton::get_nb_max_jetons())){
            throw SplendorException("Mauvais id de jetons!");
        }
        switch (coul){
            case Couleur::rouge:{
                if(nb_rouge<max_rouge){
                    nb_rouge++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons rouge!");
                }
                break;
            }
            case Couleur::bleu: {
                if(nb_bleu<max_bleu){
                    nb_bleu++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons bleu!");
                }
                break;
            }
            case Couleur::vert: {
                if(nb_vert<max_vert){
                    nb_vert++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons vert!");
                }
                break;
            }
            case Couleur::blanc:{
                if(nb_blanc<max_blanc){
                    nb_blanc++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons blanc!");
                }
                break;
            }
            case Couleur::noir:{
                if(nb_noir<max_noir){
                    nb_noir++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons noir!");
                }
                break;
            }
            case Couleur::perle:{
                if(nb_perle<max_perle){
                    nb_perle++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons perle!");
                }
                break;
            }
            case Couleur::gold:{
                if(nb_or<max_or){
                    nb_or++;
                }else{
                    throw SplendorException("Impossible de créer plus de jetons or!");
                }
                break;
            }
            default: {
                throw SplendorException("Couleur inconnue");
                break;
            }
        }
    }
    ~Jeton(){
        switch (couleur) {
            case Couleur::rouge: {
                if (nb_rouge > 0) {
                    nb_rouge--;
                } else {
                    throw SplendorException("Nombre de jetons rouge <= 0!");
                }
                break;
            }
            case Couleur::bleu: {
                if (nb_bleu > 0) {
                    nb_bleu--;
                } else {
                    throw SplendorException("Nombre de jetons bleu <= 0!");
                }
                break;
            }
            case Couleur::vert: {
                if (nb_vert > 0) {
                    nb_vert--;
                } else {
                    throw SplendorException("Nombre de jetons vert <= 0!");
                }
                break;
            }
            case Couleur::blanc: {
                if (nb_blanc > 0) {
                    nb_blanc--;
                } else {
                    throw SplendorException("Nombre de jetons blanc <= 0!");
                }
                break;
            }
            case Couleur::noir: {
                if (nb_noir > 0) {
                    nb_noir--;
                } else {
                    throw SplendorException("Nombre de jetons noir <= 0!");
                }
                break;
            }
            case Couleur::perle: {
                if (nb_perle > 0) {
                    nb_perle--;
                } else {
                    throw SplendorException("Nombre de jetons  <= 0!");
                }
                break;
            }
            case Couleur::gold: {
                if (nb_or > 0) {
                    nb_or--;
                } else {
                    throw SplendorException("Nombre de jetons vert <= 0!");
                }
                break;
            }
            default: {
                throw SplendorException("Couleur de jetons inconnue");
                break;
            }
        }
    }
    Jeton& operator=(const Jeton& jet)=delete;
    Jeton(const Jeton& jet)=delete;

    const Couleur& get_couleur() const {return couleur;}
    const int get_id()const{return id;}



    static int get_nb_max_jetons(){return max_bleu+max_blanc+max_or+max_noir+max_perle+max_rouge+max_vert;}


};


inline ostream& operator<<(ostream& f, const Jeton& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: "<<toString(jet.get_couleur());
    return f;
}

vector<const Jeton*> initJetons();


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







#endif //LO21_SPLENDOR_DUEL_JETONS_H

