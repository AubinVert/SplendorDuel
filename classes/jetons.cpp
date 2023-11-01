#include "jetons.h"

using namespace std;

ostream& operator<<(ostream& f, const Jeton_gemme& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: "<<jet.get_couleur();
}

ostream& operator<<(ostream& f, const Jeton_perle& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: perle";
}

ostream& operator<<(ostream& f, const Jeton_or& jet){
    f<<"id: "<<jet.get_id()<<"; couleur: or";
}