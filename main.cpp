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
        Privilege* instance1 = Privilege::GetInstance();
        Privilege* instance2 = Privilege::GetInstance();
        Privilege* instance3 = Privilege::GetInstance();
        Privilege* instance4 = Privilege::GetInstance(); //Lève une exception car la limite est atteinte
        std::cout<<"id de la premiere instance : "<<instance1->get_id()<<"\n";
        std::cout<<"id de la seconde instance : "<<instance2->get_id()<<"\n";
        std::cout<<"id de la troisieme instance : "<<instance3->get_id()<<"\n";
    } catch (const SplendorException& e) {
        std::cerr << "Exception: " <<e.getInfos()<< std::endl;
    }
}
