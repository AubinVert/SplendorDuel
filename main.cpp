//
// Created by leo on 10/1/23.
//

#include "main.h"


int main(){

    try{
        test_unitaires();

    }catch(SplendorException& e){
        cout<< e.getInfos()<<endl;
    }


    return 0;
}


void test_unitaires(){
    //tests_cartes();
    testInitCartes();

}


