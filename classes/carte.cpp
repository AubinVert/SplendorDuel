//
// Created by Aubin VERT on 31/10/2023.
//

#include <fstream>
#include "carte.h"
int Carte::nb_cartes = 0;



std::string toString(Couleur c) {
    switch (c) {
        case Couleur::rouge: return "Rouge";
        case Couleur::bleu: return "Bleu";
        case Couleur::vert: return "Vert";
        case Couleur::blanc: return "Blanc";
        case Couleur::noir: return "Noir";
        default: throw SplendorException("Couleur inconnue");
    }
}
std::string toString(optional<Capacite> c) {
    if(c != nullopt){
        if(c == Capacite::rejouer){
            return "Rejouer";
        }else if(c == Capacite::voler_pion_adverse){
            return "Voler un pion adverse";
        }else if(c == Capacite::prendre_privilege){
            return "Prendre un privilege";
        }else if(c == Capacite::prendre_sur_plateau){
            return "Prendre un pion de la même couleur que le bonus de la carte sur le plateau";
        }else if(c == Capacite::joker){
            return "Joker";
        }else{
            throw SplendorException("Capacite inconnue");

        }
    }else{
        return "Null";
    }
}
std ::string toString(optional<enum Bonus_couleur> bonus){
    if(bonus != nullopt) {
        if (bonus == Bonus_couleur::bleu) {
            return "Bonus Bleu";
        } else if (bonus == Bonus_couleur::rouge) {
            return "Bonus Rouge";
        } else if (bonus == Bonus_couleur::vert) {
            return "Bonus Vert";
        } else if (bonus == Bonus_couleur::blanc) {
            return "Bonus Blanc";
        } else if (bonus == Bonus_couleur::noir) {
            return "Bonus Noir";
        } else if (bonus == Bonus_couleur::joker) {
            return "Bonus Joker";
        }
    }else{
        return "Null";}
}

std::ostream& operator<<(std::ostream& f, optional<Capacite> c) { return  f << toString(c) ;}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }

std::ostream& operator<<(ostream& f, optional<enum Bonus_couleur> b) { f << toString(b); return f; }

extern 	std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::bleu, Couleur::vert, Couleur::blanc, Couleur::noir };
extern 	std::initializer_list<Capacite> Capacites = { Capacite::rejouer, Capacite::voler_pion_adverse, Capacite::prendre_privilege, Capacite::prendre_sur_plateau, Capacite::joker };
extern std::initializer_list< enum Bonus_couleur> Bonus_couleurs ={ Bonus_couleur::bleu, Bonus_couleur::rouge, Bonus_couleur::vert, Bonus_couleur::blanc, Bonus_couleur::noir, Bonus_couleur::joker};

std::map<std::string,enum Bonus_couleur> bonusMap = {
        {"bleu", Bonus_couleur::bleu},
        {"rouge", Bonus_couleur::rouge},
        {"vert", Bonus_couleur::vert},
        {"blanc", Bonus_couleur::blanc},
        {"noir", Bonus_couleur::noir},
        {"joker", Bonus_couleur::joker}
};

optional<enum Bonus_couleur> getBonusFromString(const std::string& str) {
    auto it = bonusMap.find(str);
    if (it != bonusMap.end()) {
        return it->second;
    } else {
        return nullopt;
    }
}

std::map<std::string, Capacite> capaciteMap = {
        {"rejouer", Capacite::rejouer},
        {"voler_pion_adverse", Capacite::voler_pion_adverse},
        {"prendre_privilege", Capacite::prendre_privilege},
        {"prendre_sur_plateau", Capacite::prendre_sur_plateau},
        {"joker", Capacite::joker}
};

optional<Capacite> getCapaciteFromString(const std::string& str) {
    auto it = capaciteMap.find(str);
    if (it != capaciteMap.end()) {
        return it->second;
    } else {
        return nullopt;
    }
}






vector<const Carte_royale*> initCartesRoyales(){
    std::ifstream file("../src/cartes.json");

    if (!file.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        throw SplendorException("Fichier non ouvert");
    }

    json data;
    file >> data;
    file.close();

    std::vector<const Carte_royale*> cartes_royales_instances;

    for (const auto& carte_royale_data : data["cartes_royales"]) {


        if(!carte_royale_data["capacite"].is_null()){
            Carte_royale* instance = new Carte_royale(carte_royale_data["points_prestige"],getCapaciteFromString(carte_royale_data["capacite"]));
            cartes_royales_instances.push_back(instance);
        }else{
            Carte_royale* instance = new Carte_royale(carte_royale_data["points_prestige"], nullopt);
            cartes_royales_instances.push_back(instance);
        }

    }
    return cartes_royales_instances;
}

vector<const Carte_joaillerie*> initCartesJoaillerie(){
    std::ifstream file("../src/cartes.json");

    if (!file.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        throw SplendorException("Fichier non ouvert");
    }

    json data;
    file >> data;
    file.close();
    std::vector<const Carte_joaillerie*> cartes_joailleries_instances;
    for (const auto& carte_joaillerie_data : data["cartes_joailleries"]) {

        if(carte_joaillerie_data["capacite"].is_null() && carte_joaillerie_data["bonus_couleur"].is_null() ){

            Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronne"], carte_joaillerie_data["bonus_nombre"], nullopt,nullopt);
            cartes_joailleries_instances.push_back(instance);
        }else if (!carte_joaillerie_data["capacite"].is_null() && carte_joaillerie_data["bonus_couleur"].is_null())
        {

            Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronne"], carte_joaillerie_data["bonus_nombre"], nullopt,getCapaciteFromString(carte_joaillerie_data["capacite"]));
            cartes_joailleries_instances.push_back(instance);

        }else if(carte_joaillerie_data["capacite"].is_null() && !carte_joaillerie_data["bonus_couleur"].is_null()){

            Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronne"], carte_joaillerie_data["bonus_nombre"], getBonusFromString(carte_joaillerie_data["bonus_couleur"]),nullopt);
            cartes_joailleries_instances.push_back(instance);
        }else{

            Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronne"], carte_joaillerie_data["bonus_nombre"], getBonusFromString(carte_joaillerie_data["bonus_couleur"]),getCapaciteFromString(carte_joaillerie_data["capacite"]));
            cartes_joailleries_instances.push_back(instance);
        }
    }
    return cartes_joailleries_instances;
}

// Tests unitaires de la classe Carte :





void testInitCartes(){

    vector<const Carte_royale*> test = initCartesRoyales();
    vector<const Carte_joaillerie*> test2 = initCartesJoaillerie();

    for (int k = 0; k < test2.size(); k++) {
        cout << *test2[k]<<endl;
    }
    for (int k = 0; k < test.size(); k++) {
        cout << *test[k]<<endl;
    }

    cout<<"\n"<<Carte::getNbCartes()<<endl;

}

