//
// Created by leo on 10/1/23.
//

#include "main.h"

int main() {
    try{
        Jeton_perle j1(1);
        Jeton_perle j2(2);
        Jeton_perle j3(3);
    }catch(const SplendorException& e){
        cout<<e.getInfos()<<endl;
    }
    return 0;
}


void test_unitaires(){
    // permet de tester la validité de notre code







}


