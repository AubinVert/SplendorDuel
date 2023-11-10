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
        Pioche::remplirPioche(p1, p2, p3, ref);
    } catch (const SplendorException& e) {
        std::cerr << "Exception: " <<e.getInfos()<< std::endl;
    }
}
