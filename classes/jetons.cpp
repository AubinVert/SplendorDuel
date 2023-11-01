#include "jetons.h"
#include "carte.h"
#include <iostream>

using namespace std;

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


ostream& operator<<(ostream& f, const Jeton_gemme& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: "<<toString(jet.get_couleur());
    return f;
}

ostream& operator<<(std::ostream& f, const Jeton_perle& jet){
    f << "id: " << jet.get_id() << "; couleur: perle";
    return f;
}

ostream& operator<<(ostream& f, const Jeton_or& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: or";
    return f;
}