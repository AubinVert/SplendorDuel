//
// Created by Aubin VERT on 31/10/2023.
//

#include "carte.h"


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

        Bonus_couleur a =  c.get_bonus();
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




}


