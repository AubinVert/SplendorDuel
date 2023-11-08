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
std::string toString(Capacite c) {
    switch (c) {
        case Capacite::rejouer: return "Rejouer";
        case Capacite::voler_pion_adverse: return "Voler un pion adverse";
        case Capacite::prendre_privilege: return "Prendre un privilege";
        case Capacite::prendre_sur_plateau: return "Prendre un pion de la même couleur que le bonus de la carte sur le plateau";
        case Capacite::joker: return "Joker";
        default: throw SplendorException("Capacite inconnue");
    }
}
std ::string toString(enum Bonus_couleur bonus){
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

std::ostream& operator<<(std::ostream& f, Capacite c) { f << toString(c); return f; }
std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
std::ostream& operator<<(ostream& f, enum Bonus_couleur b) { f << toString(b); return f; }

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

Capacite getCapaciteFromString(const std::string& str) {
    auto it = capaciteMap.find(str);
    if (it != capaciteMap.end()) {
        return it->second;
    } else {
        // Gérer le cas où la chaîne n'a pas de correspondance
        return Capacite::rejouer; // Ou une valeur par défaut appropriée
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

    std::vector<Carte_royale> cartes_royales_instances;
    std::vector<Carte_joaillerie> cartes_joailleries_instances;

    for (const auto& carte_royale_data : data["cartes_royales"]) {
        if(strcmp(carte_royale_data["capacite"],"null")!=0){
            Carte_royale* instance = new Carte_royale(getCapaciteFromString(carte_royale_data["capacite"]),carte_royale_data["points_prestige"]);

        }else{
            Carte_royale* instance = new Carte_royale(nullptr,carte_royale_data["points_prestige"]);

        }


        cout<<*instance<<endl;

    }

    for (const auto& carte_joaillerie_data : data["cartes_joailleries"]) {
        //cout<<
                //carte_joaillerie_data["capacite"]<<" "<< carte_joaillerie_data["points_prestige"]<<" "<<
                //carte_joaillerie_data["niveau"]<<" "<< carte_joaillerie_data["bonus_couleur"]<<" "<<
                //carte_joaillerie_data["bonus_nombre"]<<" "<< carte_joaillerie_data["nb_couronne"]<<" "<<
                //carte_joaillerie_data["cout_blanc"]<<" "<< carte_joaillerie_data["cout_bleu"]<<" "<<
                //carte_joaillerie_data["cout_vert"]<<" "<<carte_joaillerie_data["cout_rouge"]<<" "<<
                //carte_joaillerie_data["cout_noir"]<<" "<< carte_joaillerie_data["cout_perle"]<<endl;
    }





}



// Tests unitaires de la classe Carte :

void tests_cartes(){



    // Test création d'une carte ;

    try {
        Carte carte(Capacite::joker, 2);
        Carte c;
        cout << "Test 1 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 1 failed!";
        cerr << e;
    }


    // Test des getters
    try {
        Carte carte(Capacite::joker, 2);
        Capacite a = carte.getCapacite();
        int b = carte.getPrestige();
        cout << "Test 2 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 2 failed!";
        cerr << e;
    }

    // Test création cartes joallerie.
    try {
        Carte_joaillerie carte; // création sans arguments
        Carte_joaillerie c(Capacite::joker,2,1,2,3,1,2,3,2,2,Bonus_couleur::rouge,2);
        cout << "Test 3 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 3 failed!";
        cerr << e;
    }



    // Test des getters
    try {
        Carte_joaillerie c(Capacite::joker,2,1,2,3,1,2,3,2,2,Bonus_couleur::rouge,2);
        int n = c.getCoutBlanc();
        int n2 = c.getCoutBleu();
        int n3 = c.getCoutNoir();
        int n4 = c.getCoutPerle();

        enum Bonus_couleur a =  c.get_bonus();
        Capacite g =  c.getCapacite();



        cout << "Test 4 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 4 failed!";
        cerr << e;
    }


    // Test carte royale :
    try {
        Carte_royale carte(Capacite::joker, 1);
        Capacite a = carte.getCapacite();
        int b = carte.getPrestige();
        cout << "Test 5 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 5 failed!";
        cerr << e;
    }

    //
    try {
        Carte carte(Capacite::joker, 2);
        cout<<carte;
        cout << "Test 6 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 6 failed!";
        cerr << e;
    }

    try {
        Carte_joaillerie carte(Capacite::rejouer, 3, 2, 0, 0, 2, 0,0, 1,1, Bonus_couleur::rouge, 2);
        cout<<carte;
        cout << "Test 7 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 7 failed!";
        cerr << e;
    }

    try {
        Carte_royale carte(Capacite::prendre_privilege, 2);
        cout<<carte;
        cout << "Test 8 passed!" << endl;
    } catch (const string& e) {
        cout << "Test 8 failed!";
        cerr << e;
    }


    try {


        Carte carte(Capacite::joker, 2);
        Carte c1(Capacite::joker, 2);
        Carte c2(Capacite::joker, 2);
        Carte c3(Capacite::joker, 2);
        Carte c4(Capacite::joker, 2);


        if(Carte::getNbCartes() == 5){
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

