#include "main.h"
#include "classes/plateau.h"
#include "classes/jetons.h"
#include "classes/sac.h"

int main(){

    try{
        test_unitaires();

    }catch(SplendorException& e){
        cout<< e.getInfos()<<endl;
    }


    return 0;
}


void test_unitaires(){
    try {
        vector<const Carte_joaillerie*> test = initCartesJoaillerie();
        vector<const Carte_joaillerie*>& ref = test;
        Pioche* p1 = new Pioche(1);
        Pioche* p2 = new Pioche(2);
        Pioche* p3 = new Pioche(3);
        //Pioche* p4 = new Pioche(3); //lève une exception
        cout<<Pioche::getNbPioches;

        Pioche::remplirPioche(p1, p2, p3, ref);

        if (not (p1->est_vide())){cout<<"pioche p1 pas vide";}

        //affichage des cartes de la pioche 1
        int compteur = 0;
        for (int k = 0; k < (p1->getPioche()).size(); k++){
            cout << *(p1->getPioche())[k]<<endl;
            compteur++;
        }
        cout<<compteur; //on a bien 30 cartes de nv1
    } catch (const SplendorException& e) {
        std::cerr << "Exception: " <<e.getInfos()<< std::endl;
    }
}
