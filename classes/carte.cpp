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



void readJson(){

    std::ifstream file("../src/cartes.json");

    if (!file.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        return;
    }

    json data;
    file >> data;
    file.close();

    std::vector<Carte_royale*> cartes_royales_instances;
    std::vector<Carte_joaillerie*> cartes_joailleries_instances;

    for (const auto& carte_royale_data : data["cartes_royales"]) {


        if(!carte_royale_data["capacite"].is_null()){
            Carte_royale* instance = new Carte_royale(carte_royale_data["points_prestige"],getCapaciteFromString(carte_royale_data["capacite"]));
            cartes_royales_instances.push_back(instance);
        }else{
            Carte_royale* instance = new Carte_royale(carte_royale_data["points_prestige"], nullopt);
            cartes_royales_instances.push_back(instance);
        }

    }

    for (int k = 0; k < cartes_royales_instances.size(); k++) {
        cout << *cartes_royales_instances[k]<<endl;
    }

    for (const auto& carte_joaillerie_data : data["cartes_joailleries"]) {
        if(carte_joaillerie_data["capacite"].is_null() && carte_joaillerie_data["bonus_couleur"].is_null() ){
            cout<<carte_joaillerie_data["points_prestige"]<<" "<< carte_joaillerie_data["cout_blanc"]<<" "<<carte_joaillerie_data["cout_bleu"]<<" "<<carte_joaillerie_data["cout_rouge"]<<" "<<carte_joaillerie_data["cout_vert"]<<" "<<carte_joaillerie_data["cout_noir"]<<" "<< carte_joaillerie_data["cout_perle"]<<" "<< carte_joaillerie_data["niveau"]<<" "<< carte_joaillerie_data["nb_couronnes"]<< " "<< carte_joaillerie_data["bonus_nombre"]<<" "<< carte_joaillerie_data["bonus_nombre"]<<" "<<carte_joaillerie_data["capacite"];

            //Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronnes"], carte_joaillerie_data["bonus_nombre"], nullopt,nullopt);
            //cartes_joailleries_instances.push_back(instance);
        }else if (carte_joaillerie_data["capacite"].is_null() && !carte_joaillerie_data["bonus_couleur"].is_null())
        {
            cout<<carte_joaillerie_data["points_prestige"]<<" "<< carte_joaillerie_data["cout_blanc"]<<" "<<carte_joaillerie_data["cout_bleu"]<<" "<<carte_joaillerie_data["cout_rouge"]<<" "<<carte_joaillerie_data["cout_vert"]<<" "<<carte_joaillerie_data["cout_noir"]<<" "<< carte_joaillerie_data["cout_perle"]<<" "<< carte_joaillerie_data["niveau"]<<" "<< carte_joaillerie_data["nb_couronnes"]<< " "<< carte_joaillerie_data["bonus_nombre"]<<" "<< carte_joaillerie_data["bonus_nombre"]<<" "<<carte_joaillerie_data["capacite"];

            //Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronnes"], carte_joaillerie_data["bonus_nombre"], nullopt,carte_joaillerie_data["capacite"]);
            //cartes_joailleries_instances.push_back(instance);

        }else if(!carte_joaillerie_data["capacite"].is_null() && carte_joaillerie_data["bonus_couleur"].is_null()){
            cout<<carte_joaillerie_data["points_prestige"]<<" "<< carte_joaillerie_data["cout_blanc"]<<" "<<carte_joaillerie_data["cout_bleu"]<<" "<<carte_joaillerie_data["cout_rouge"]<<" "<<carte_joaillerie_data["cout_vert"]<<" "<<carte_joaillerie_data["cout_noir"]<<" "<< carte_joaillerie_data["cout_perle"]<<" "<< carte_joaillerie_data["niveau"]<<" "<< carte_joaillerie_data["nb_couronnes"]<< " "<< carte_joaillerie_data["bonus_nombre"]<<" "<< carte_joaillerie_data["bonus_nombre"]<<" "<<carte_joaillerie_data["capacite"];

            //Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronnes"], carte_joaillerie_data["bonus_nombre"], carte_joaillerie_data["bonus_couleur"],nullopt);
            //cartes_joailleries_instances.push_back(instance);
        }else{
            cout<<carte_joaillerie_data["points_prestige"]<<" "<< carte_joaillerie_data["cout_blanc"]<<" "<<carte_joaillerie_data["cout_bleu"]<<" "<<carte_joaillerie_data["cout_rouge"]<<" "<<carte_joaillerie_data["cout_vert"]<<" "<<carte_joaillerie_data["cout_noir"]<<" "<< carte_joaillerie_data["cout_perle"]<<" "<< carte_joaillerie_data["niveau"]<<" "<< carte_joaillerie_data["nb_couronnes"]<< " "<< carte_joaillerie_data["bonus_nombre"]<<" "<< carte_joaillerie_data["bonus_nombre"]<<" "<<carte_joaillerie_data["capacite"];

            //Carte_joaillerie* instance = new Carte_joaillerie(carte_joaillerie_data["points_prestige"], carte_joaillerie_data["cout_blanc"],carte_joaillerie_data["cout_bleu"],carte_joaillerie_data["cout_rouge"],carte_joaillerie_data["cout_vert"], carte_joaillerie_data["cout_noir"], carte_joaillerie_data["cout_perle"], carte_joaillerie_data["niveau"], carte_joaillerie_data["nb_couronnes"], carte_joaillerie_data["bonus_nombre"], carte_joaillerie_data["bonus_couleur"],carte_joaillerie_data["capacite"]);
            //cartes_joailleries_instances.push_back(instance);
        }
    }





}



// Tests unitaires de la classe Carte :

void tests_cartes(){



    // Test création d'une carte ;

    try {
        Carte carte(2,Capacite::joker);
        Carte c;
        cout << "Test 1 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 1 failed!";
        cerr << e;
    }


    // Test des getters
    try {
        Carte carte( 2,Capacite::joker);
        optional<Capacite> a = carte.getCapacite();
        int b = carte.getPrestige();
        cout << "Test 2 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 2 failed!";
        cerr << e;
    }

    // Test création cartes joallerie.
    try {
        Carte_joaillerie carte; // création sans arguments
        Carte_joaillerie c(2,1,2,3,1,2,3,2,2,2,Bonus_couleur::rouge,Capacite::joker);
        cout << "Test 3 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 3 failed!";
        cerr << e;
    }



    // Test des getters
    try {
        Carte_joaillerie c(2,1,2,3,1,2,3,2,2,2,Bonus_couleur::rouge,Capacite::joker);
        int n = c.getCoutBlanc();
        int n2 = c.getCoutBleu();
        int n3 = c.getCoutNoir();
        int n4 = c.getCoutPerle();

        optional<enum Bonus_couleur> a =  c.get_bonus();
        optional<Capacite> g =  c.getCapacite();



        cout << "Test 4 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 4 failed!";
        cerr << e;
    }


    // Test carte royale :
    try {
        Carte_royale carte(1, Capacite::joker);
        optional<Capacite> a = carte.getCapacite();
        int b = carte.getPrestige();
        cout << "Test 5 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 5 failed!";
        cerr << e;
    }

    //
    try {
        Carte carte(2,Capacite::joker);
        cout<<carte;
        cout << "Test 6 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 6 failed!";
        cerr << e;
    }

    try {
        Carte_joaillerie carte(2,1,2,3,1,2,3,2,2,2,Bonus_couleur::rouge,Capacite::joker);
        cout<<carte;
        cout << "Test 7 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 7 failed!";
        cerr << e;
    }

    try {
        Carte_royale carte( 2, Capacite::prendre_privilege);
        cout<<carte;
        cout << "Test 8 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 8 failed!";
        cerr << e;
    }


    try {


        Carte carte( 2, Capacite::prendre_privilege);
        Carte c1( 2, Capacite::prendre_privilege);



        if(Carte::getNbCartes() == 2){
            cout << "\nTest 9 passed!" << endl;

        }else{
            throw SplendorException("Test 9 failed ! ");
        }
    } catch (const string& e) {
        cout << "Test 9 failed!";
        cerr << e;
    }


}

void testInitCartes(){

    readJson();
}

